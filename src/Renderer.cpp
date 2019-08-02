#include <SDL2/SDL.h>
#include <vector>
#include <stdio.h>
#include "Renderer.h"
#include "Vector3.h"
#include "DepthBuffer.h"
#include "Color.h"

using namespace gr;

gr::Renderer::Renderer(SDL_Window* wnd, int width, int height){
    this->p_wnd = wnd;
    this->p_canvas = SDL_GetWindowSurface(wnd);
    this->p_pxfmt = this->p_canvas->format;
    this->fillColor = SDL_MapRGB(this->p_pxfmt, 0x00, 0x00, 0x00); // black
    this->canvas_hw = width / 2;
    this->canvas_hh = height / 2;
    this->dbuffer = new DepthBuffer(width, height);
    this->isDrawDepthBuffer = false;
}

Renderer::~Renderer(){
    delete this->dbuffer;
}

void gr::Renderer::clear(){
    SDL_FillRect(this->p_canvas, 0, this->fillColor);
    this->dbuffer->clear();
}

void Renderer::draw(const Mesh& mesh, const Matrix4& WVP){
    doVertexShader(mesh, WVP);
    doClipping();
    doPerspectiveDivide();
    doRasterisation();
    wrapup();
}

void Renderer::show(){
    SDL_UpdateWindowSurface(this->p_wnd);
}

void Renderer::setModeDrawDepthBuffer(){
    this->isDrawDepthBuffer = true;
}

void Renderer::setModeDrawSceneBuffer(){
    this->isDrawDepthBuffer = false;
}

inline float minf(float a, float b, float c){
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

inline float maxf(float a, float b, float c){
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

void Renderer::doVertexShader(const Mesh& mesh, const Matrix4& WVP){
    unsigned int vcount = 0;
    std::vector<Vertex>::const_iterator iter1 = mesh.vertices.begin();
    for(; iter1 != mesh.vertices.end(); ++iter1){
        Vertex& v = this->vsOut.vertices[vcount];
        v.posL = (*iter1).posL.mul(WVP);
        v.color = (*iter1).color;
        vcount += 1;
        if(vcount >= MAX_VERTICES){
            // throw exception...
        }
    }
    vsOut.vcount = vcount;

    unsigned int icount = 0;
    std::vector<unsigned int>::const_iterator iter2 = mesh.indices.begin();
    for(; iter2 != mesh.indices.end(); ++iter2){
        this->vsOut.indices[icount] = (*iter2);
        icount += 1; 
        if(icount > MAX_INDICES){
            // throw exception...
        }
    }
    vsOut.icount = icount;
}

bool Renderer::pointVisible(const Vertex& v, int planeID){
    bool result = false;
    switch(planeID){
        case 0: // w+x=0 plane
            (v.posL.w + v.posL.x > 0) ? result=true : result=false;
            break;
        case 1: // w-x=0 plane.
            (v.posL.w - v.posL.x > 0) ? result=true : result=false;
            break;
        case 2: // w+y=0 plane.
            (v.posL.w + v.posL.y > 0) ? result=true : result=false;
            break;
        case 3: // w-y=0 plane.
            (v.posL.w - v.posL.y > 0) ? result=true : result=false;
            break;
        case 4: // z=0 plane.
            v.posL.z > 0 ? result=true : result=false;
            break;
        case 5: // w-z=0 plane.

            // should this be greater than or less than 0?

            (v.posL.w - v.posL.z > 0) ? result=true : result=false;
            break;
    }
    return result;
}

void Renderer::findIntersection(const Vertex& V1, const Vertex& V2, Vertex* pVout, int planeID){
    // calculate alpha (the interpolation constant)...
    const Vector3H& P1 = V1.posL;
    const Vector3H& P2 = V2.posL;
    float alpha = 0.f;
    switch(planeID){
        case 0: // w+x=0 plane
            alpha = (P1.w + P1.x) / ((P1.w + P1.x) - (P2.w + P2.x));
            break;
        case 1: // w-x=0 plane.
            alpha = (P1.w - P1.x) / ((P1.w - P1.x) - (P2.w - P2.x));
            break;
        case 2: // w+y=0 plane.
            alpha = (P1.w + P1.y) / ((P1.w + P1.y) - (P2.w + P2.y));
            break;
        case 3: // w-y=0 plane.
            alpha = (P1.w - P1.y) / ((P1.w - P1.y) - (P2.w - P2.y));
            break;
        case 4: // z=0 plane.
            alpha = P1.z / (P1.z - P2.z);
            break;
        case 5: // w-z=0 plane.
            alpha = (P1.w - P1.z) / ((P1.w - P1.z) - (P2.w - P2.z));
            break;
    }

    float inalpha = 1.f - alpha;

    // interpolate between P1 and P2 position vectors...
    Vector3H* pPout = &pVout->posL;
    pPout->x = inalpha*P1.x + alpha*P2.x;
    pPout->y = inalpha*P1.y + alpha*P2.y;
    pPout->z = inalpha*P1.z + alpha*P2.z;
    pPout->w = inalpha*P1.w + alpha*P2.w;

    // interpolate between color value...
    const Color& C1 = V1.color;
    const Color& C2 = V2.color;
    Color* pCout = &pVout->color;
    pCout->setR(inalpha*C1.getR() + alpha*C2.getR());
    pCout->setG(inalpha*C1.getG() + alpha*C2.getG());
    pCout->setB(inalpha*C1.getB() + alpha*C2.getB());
    pCout->setA(inalpha*C1.getA() + alpha*C2.getA());
}

// Using the shoelace algorithm to find the area of the triangle and determine
// its sign.
bool Renderer::isBackFacing(const Triangle& t){
    const Vector3H& P0 = t.P[0].posL;
    const Vector3H& P1 = t.P[1].posL;
    const Vector3H& P2 = t.P[2].posL;

    // note: this is actually twice the area (only need sign).
    float A = P0.x*P1.y + P1.x*P2.y + P2.x*P0.y - P1.x*P0.y - P2.x*P1.y - P0.x*P2.y;

    bool result;
    (A < 0) ? result = false : result = true;
    return result;

    //Vector3H e0 = t.P[1].posL.sub(t.P[0].posL);
    //Vector3H e1 = t.P[2].posL.sub(t.P[0].posL);
    //Vector3H r = e0.cross(e1);
    //bool result;
    //(r.z <= 0) ? result = false : result = true;
    //return result;
}

void Renderer::clip(const Triangle& tIn, Triangle* ptOuts, int* tOutCount){
    Vertex input[8];
    Vertex output[8];

    Vertex NullV;
    
    input[0] = tIn.P[0];
    input[1] = tIn.P[1];
    input[2] = tIn.P[2];

    unsigned int insize = 3;
    unsigned int outsize = 0;

    // clip against the fixed set of view frustrum planes. The loop index i
    // sets which plane we are clipping against. When:
    // i=0: clip against w+x=0 plane.
    // i=1: clip against w-x=0 plane.
    // i=2: clip against w+y=0 plane.
    // i=3: clip against w-y=0 plane.
    // i=4: clip against z=0.
    // i=5: clip against w-z=0 plane.
    // note: named loop index (i.e i) planeID for increased clarity.
    for(int planeID = 0; planeID <= 5; planeID++){
        // BUG FIX: seg fault if clip away all geometry: (insize-1) results in 
        // negative index.
        int k = insize - 1;
        if(k < 0){
            k = 0;
        }
        Vertex S = input[k];
        for(int i = 0; i < insize; i++){
            Vertex& P = input[i];
            bool isSVisible = pointVisible(S, planeID);
            bool isPVisible = pointVisible(P, planeID);

            // calculate output points...
            if(isSVisible && isPVisible){
                output[outsize] = P;
                outsize += 1;
            }
            else if(isSVisible && !isPVisible){
                Vertex I;
                findIntersection(S, P, &I, planeID);
                output[outsize] = I;
                outsize += 1;
            }
            else if(!isSVisible && isPVisible){
                Vertex I;
                findIntersection(S, P, &I, planeID);
                output[outsize] = I;
                outsize += 1;
                output[outsize] = P;
                outsize += 1;
            }
            S = P;
        }

        // output of clip against current plane is input to clip against next 
        // plane.
        for(int j = 0; j < outsize; j++){
            input[j] = output[j];
            output[j] = NullV;
        }
        insize = outsize;
        outsize = 0;
    }

    // triangulate the clipping output if neccessary and output result...
    // note: using fan triangulation.
    // note: can output up to 5 triangles.
    // note: output was copied to input at end of clipping.
    for(int n = 1; n <= ((int)insize - 2); n++){
        ptOuts[n-1].P[0] = input[0];
        ptOuts[n-1].P[1] = input[n];
        ptOuts[n-1].P[2] = input[n+1];
    }
    *tOutCount = insize - 2;
}

void Renderer::doClipping(){
    // extract the triangles and clip them one at a time...
    Triangle t;
    Triangle tOut[5];
    int tOutCount = 0;
    for(int i = 0; i < this->vsOut.icount; i+=3){
        // extract the next triangle...
        for(int j = 0; j < 3; j++){
            unsigned int index = this->vsOut.indices[i+j];
            t.P[j].posL = vsOut.vertices[index].posL;
            t.P[j].color = vsOut.vertices[index].color;
        }

        // clip front-facing triangles against view frustrum...
        clip(t, tOut, &tOutCount);

        // add output triangles to clipping output...
        for(int k = 0; k < tOutCount; k++){
            this->clipOut.t[this->clipOut.tcount] = tOut[k];
            this->clipOut.tcount++;
        }
    }
}

void Renderer::doPerspectiveDivide(){
    for(int i = 0; i < this->clipOut.tcount; i++){
        Triangle& t = this->clipOut.t[i];
        for(int j = 0; j < 3; j++){
            Vector3H& p = t.P[j].posL;
            float s = 1.f / p.w;
            p.x *= s;
            p.y *= s;
            p.z *= s;
            p.w *= s;
        }
    }
}

void gr::Renderer::doViewportTransform(Triangle& t){
    for(int i = 0; i < 3; i++){
        // translate all values to range 0-2 so they map to raster space...
        t.P[i].posL.x += 1.f;
        t.P[i].posL.y += 1.f;

        // scale all values up to the screen size...
        t.P[i].posL.x *= (float)this->canvas_hw;
        t.P[i].posL.y *= (float)this->canvas_hh;
    }
}

// source: http://sdl.beuc.net/sdl.wiki/Pixel_Access
//
// note: MUST lock the surface (call SDL_LockSurface) before calling this 
// function. 
void gr::Renderer::putPixel(int x, int y, Uint32 color){
    // get address of pixel on the canvas for the pixel we are to draw...
    int bpp = this->p_pxfmt->BytesPerPixel;
    Uint8* p = (Uint8*)this->p_canvas->pixels + (y * this->p_canvas->pitch) + (x * bpp);

    switch(bpp){
        case 1:
            *p = color;
            break;
        case 2:
            *(Uint16*)p = color;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (color >> 16) & 0xff;
                p[1] = (color >> 8) & 0xff;
                p[2] = color & 0xff;
            } else {
                p[0] = color & 0xff;
                p[1] = (color >> 8) & 0xff;
                p[2] = (color >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32*)p = color;
            break;
    }
}

void gr::Renderer::rasteriseTriangle(Triangle& t){
    // extract triangle data...
    Vertex& Va = t.P[0];
    Vertex& Vb = t.P[1];
    Vertex& Vc = t.P[2];

    float ax = Va.posL.x;
    float ay = Va.posL.y;
    float bx = Vb.posL.x;
    float by = Vb.posL.y;
    float cx = Vc.posL.x;
    float cy = Vc.posL.y;
    
    float az = Va.posL.z;
    float bz = Vb.posL.z;
    float cz = Vc.posL.z;

    Uint8 colorA[3] = {Va.color.getR(), Va.color.getG(), Va.color.getB()};
    Uint8 colorB[3] = {Vb.color.getR(), Vb.color.getG(), Vb.color.getB()};
    Uint8 colorC[3] = {Vc.color.getR(), Vc.color.getG(), Vc.color.getB()};

    // calculate the inverse area of the triangle a,b,c...
    float inarea = 1.f / (0.5f * (((cx-ax)*(by-ay))-((cy-ay)*(bx-ax))));

    // calculate the triangle bounding box...
    // note: the AABB defines the range of pixels which need to be processed.
    int AABB_TL[2] = {0,0}; 
    int AABB_BR[2] = {0,0};maxf(ax,bx,cx), maxf(ay,by,cy);

    AABB_TL[0] = (int)minf(ax,bx,cx); 
    AABB_TL[1] = (int)minf(ay,by,cy);

    AABB_BR[0] = (int)maxf(ax,bx,cx); 
    AABB_BR[1] = (int)maxf(ay,by,cy);

    // clip to rendering target (window surface) bounds...
    // Should not need to be done as prior clipping should of ensured this.

    // calculate constants...
    float IC1 = ay - cy;
    float JC1 = cx - ax;
    float KC1 = ax*cy - ay*cx;

    float IC2 = by - ay;
    float JC2 = ax - bx;
    float KC2 = bx*ay - by*ax;

    float IC3 = cy - by;
    float JC3 = bx - cx;
    float KC3 = cx*by - cy*bx; 

    // calculate values of FC1(p), FC2(p), FC3(p) for p = center point of 
    // top-left pixel of AABB.

    float px = (float)AABB_TL[0] + 0.5f;
    float py = (float)AABB_TL[1] + 0.5f;

    float FC1 = IC1*px + JC1*py + KC1;
    float FC2 = IC2*px + JC2*py + KC2;
    float FC3 = IC3*px + JC3*py + KC3;

    // rasterize...
    float Cy1 = FC1; float Cy2 = FC2; float Cy3 = FC3;
    for(int j = AABB_TL[1]; j < AABB_BR[1]; j++){
        float Cx1 = Cy1; float Cx2 = Cy2; float Cx3 = Cy3;
        for(int i = AABB_TL[0]; i < AABB_BR[0]; i++){
            if(Cx1 >= 0.f && Cx2 >= 0.f && Cx3 >= 0.f){

                // calculate the barycentric coordinates for the current pixel...
                float sf = 0.5f * inarea;
                float Wa = sf*Cx3;
                float Wb = sf*Cx1;
                float Wc = sf*Cx2; 

                // compute interpolated depth value for the current pixel...
                float d = Wa*az + Wb*bz + Wc*cz;

                // perform depth test; skip drawing the pixel if a closer pixel
                // has already been drawn.
                if(this->dbuffer->isCloser(i, j, d)){
                    // write the closer value in the depth buffer...
                    this->dbuffer->putPixel(i, j, d);

                    if(isDrawDepthBuffer){
                        // computer the depth color value...
                        float r, g, b;
                        this->dbuffer->depthToColor(d, &r, &g, &b);
                        Uint32 color = SDL_MapRGB(this->p_pxfmt, r, g, b);

                        // render the pixel at i,j position...
                        this->putPixel(i, j, color);
                    }
                    else {
                        // compute the interpolated color value for the pixel...
                        float r = Wa*colorA[0]+Wb*colorB[0]+Wc*colorC[0];
                        float g = Wa*colorA[1]+Wb*colorB[1]+Wc*colorC[1];
                        float b = Wa*colorA[2]+Wb*colorB[2]+Wc*colorC[2];
                        Uint32 color = SDL_MapRGB(this->p_pxfmt, r, g, b);

                        // render pixel at i,j position in AABB on the window surface...
                        this->putPixel(i, j, color);
                    }
                }
            }
            Cx1 += IC1; Cx2 += IC2; Cx3 += IC3;
        }
        Cy1 += JC1; Cy2 += JC2; Cy3 += JC3;
    }
}

void gr::Renderer::doRasterisation(){
    // lock the window surface...
    if(SDL_LockSurface(this->p_canvas)){
        printf("error: Failed to lock the window surface");
    }

    // rasterise all triangles...
    for(int i = 0; i < this->clipOut.tcount; i++){
        Triangle& t = this->clipOut.t[i];
        if(isBackFacing(t)){
            continue;
        }
        doViewportTransform(t);
        rasteriseTriangle(t);
    }

    // unlock the window surface...
    SDL_UnlockSurface(this->p_canvas);
}

void gr::Renderer::wrapup(){
    this->vsOut.icount = 0;
    this->vsOut.vcount = 0;
    this->clipOut.tcount = 0;
}