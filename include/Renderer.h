#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Vector3.h"
#include "Matrix4.h"
#include "Mesh.h"
#include "DepthBuffer.h"

#define MAX_VERTICES 1000 // renderer can draw objects with up to this number of vertices.
#define MAX_INDICES 4000 // renderer can draw objects with up to this index count.
#define MAX_TRIANGLES 1400 // should be approx MAX_INDICES / 3

namespace gr {

// 
// note: clockwise ordered polygons are front facing since I am using a 
// left-handed coordinate system. Must be this way to ensure cross products 
// come out with the correct signs when performing backface culling.
//
class Renderer {
public:
    Renderer(SDL_Window* wnd, int width, int height);
    
    ~Renderer();

    //
    // Clear the back buffer and depth buffer.
    //
    void clear();

    // 
    // Draw a mesh to the back buffers.
    //
    void draw(const Mesh& mesh, const Matrix4& WVP);

    //
    // Ouput the back buffer to the screen.
    //
    void show();

    //
    // Will set the renderer to the draw the depth buffer to the window instead
    // of the scene buffer.
    //
    void setModeDrawDepthBuffer();

    //
    // Will set the renderer to the scene buffer. This is default.
    //
    void setModeDrawSceneBuffer();

private:
    //
    // Output of the vertex shader stage.
    //
    struct VSOut {
        unsigned int vcount;
        unsigned int icount;
        Vertex vertices[MAX_VERTICES];
        unsigned int indices[MAX_INDICES];
    };

    //
    // Used in the clipping stage.
    //
    struct Triangle {
        Vertex P[3];
    };

    struct ClipOut {
        unsigned int tcount;
        Triangle t[MAX_TRIANGLES];
    };

private:
    //
    // Hard-coded vertex shader stage.
    //
    void doVertexShader(const Mesh& mesh, const Matrix4& WVP);

    //
    // Tests if a point is on the visible side of a view frustrum plane.
    //
    bool pointVisible(const Vertex& v, int planeID);

    //
    // Computes the intersection between a line and a view frustrum plane.
    //
    void findIntersection(const Vertex& V1, const Vertex& V2, Vertex* pVout, int planeID);

    //
    // Tests if a triangle is facing away from the camera.
    //
    bool isBackFacing(const Triangle& t);

    // 
    // Clips a triangle against the view frustrum.
    //
    void clip(const Triangle& tIn, Triangle* ptOuts, int* pTOutCount);

    //
    // Performs clipping (Sutherland-Hodgman algorithm) on triangles against the
    // view volume.
    //
    void doClipping();

    //
    // Performs the perspective divide on all remaining vertices. This will
    //
    void doPerspectiveDivide();

    //
    // Rasterises a single triangle to the window surface.
    //
    void rasteriseTriangle(Triangle& t);

    //
    // Transforms points in NDC to raster space.
    //
    void doViewportTransform(Triangle& t);

    //
    // Draws a pixel to the window surface.
    //
    void putPixel(int x, int y, Uint32 color);

    //
    // Performs rasterisation of on all remaining (non-clipped or culled) 
    // triangles.
    //
    void doRasterisation();

    //
    // Cleanup the pipeline temporary data ready for the next draw...
    //
    void wrapup();

private:
    SDL_Window* p_wnd;        // the window to draw into.
    SDL_Surface* p_canvas;    // the windows surface.
    SDL_PixelFormat* p_pxfmt; // the pixel format of the window surface.
    unsigned int canvas_hw;   // half-width of canvas.
    unsigned int canvas_hh;   // half-height of canvas.
    Uint32 fillColor;         // fillcolor to use when clearing the screen.
    DepthBuffer* dbuffer;     
    VSOut vsOut;              // output of vertex shader stage.
    ClipOut clipOut;          // output of clipping stage.
    bool isDrawDepthBuffer;   // if true will draw the depth buffer to the screen instead.
};

}

#endif