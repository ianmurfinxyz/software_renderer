
/* BACKUP OF ORIGINAL MAIN

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "looptime.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Matrix4.h"
#include "grutil.h"

using namespace gr;

int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Unable to initialise SDL: %s", SDL_GetError());
        return 1;
    }

    if(TTF_Init() == -1){
        printf("error: Failed to initialise SDL_ttf: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* p_window = NULL;
    p_window = SDL_CreateWindow(
        "Software-Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        0
    );
    
    if(p_window == NULL){
        SDL_Log("Failed to create window: %s", SDL_GetError());
    }

    SDL_Surface* p_canvas = SDL_GetWindowSurface(p_window);

    TTF_Font* font = TTF_OpenFont("SourceCodePro-Regular.ttf", 16);
    SDL_Color fontColor = {255, 41, 80};
    if(!font){
        printf("error: Failed to load font file: %s\n", TTF_GetError());
    }

    gr::Renderer renderer(p_window, 800, 600);

    // build the meshes...
    gr::Mesh cubeSolid;
    gr::Mesh cubeGraded;
    gr::Mesh pyramidSolid;
    gr::constructCubeSolid(cubeSolid);
    gr::constructCubeGraded(cubeGraded);
    gr::constructPyramidSolid(pyramidSolid);

    int activeShape = 0; // 0=cubeSolid, 1=cubeGraded, 2=pyramidSolid

    // object properties...
    float yaw = 0.f; // unit: radians
    float roll = 0.f;
    float pitch = 0.f;
    float distance = 5.f;
    float posXWorld = 0.f;
    float posYWorld = 0.f;

    float angVel = (1.5f * 3.141592654f); // unit: radians per second (for all rotations).
    float disVel = 8.0f; // unit: spatial units per second.

    bool hasPropsChanged = false;

    // construct a WVP projection matrix for the mesh...
    Matrix4 W;
    Matrix4 V;
    Matrix4 P;
    Matrix4 WVP;
    Vector3H pos(posXWorld, posYWorld, distance);
    Vector3H eye(0.f,0.f,0.f);
    Vector3H at(0.f, 0.f, 5.f);
    Vector3H scale(1.f, 1.f, 1.f);
    Vector3H up(0.f, 1.f, 0.f);
    MatrixWorld(&pos, yaw, pitch, roll, &scale, &W);
    MatrixView(&eye, &at, &up, &V);
    MatrixProjectionFOV(40.f, ((float)800/(float)600), 1.f, 1000.f, &P);
    WVP = W.mul(V).mul(P);

    // main application loop...

    LTData ltdata;
    init_loop_data(&ltdata);
    float dt = 0.f;
    //enable_governing(&ltdata, 16000000);

    bool is_running = true;
    while(is_running){
        start_frame(&ltdata);

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            is_running = false;
                            break;
                        case SDLK_y:
                            yaw += angVel * dt;
                            if(yaw > 6.283185307f){
                                yaw = 0;
                            }
                            hasPropsChanged = true;
                            break;
                        case SDLK_p:
                            pitch += angVel * dt;
                            if(pitch > 6.283185307f){
                                pitch = 0;
                            }
                            hasPropsChanged = true;
                            break;
                        case SDLK_r:
                            roll += angVel * dt;
                            if(roll > 6.283185307f){
                                roll = 0;
                            }
                            hasPropsChanged = true;
                            break;
                        case SDLK_UP:
                            posYWorld -= disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_DOWN:
                            posYWorld += disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_LEFT:
                            posXWorld -= disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_RIGHT:
                            posXWorld += disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_f:
                            distance += disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_b:
                            distance -= disVel * dt;
                            hasPropsChanged = true;
                            break;
                        case SDLK_s:
                            activeShape += 1;
                            if(activeShape > 2){
                                activeShape = 0;
                            }
                            break;
                    }
                break;
            }
        }

        // update the WVP matrix if properties change...
        if(hasPropsChanged){
            pos.x = posXWorld;
            pos.y = posYWorld;
            pos.z = distance;
            MatrixWorld(&pos, yaw, pitch, roll, &scale, &W);
            WVP = W.mul(V).mul(P);
        }

        renderer.clear();

        switch(activeShape){
            case 0:
                renderer.draw(cubeSolid, WVP);
                break;
            case 1:
                renderer.draw(cubeGraded, WVP);
                break;
            case 2:
                renderer.draw(pyramidSolid, WVP);
                break;
        }
        
        // output FPS...
        char buffer[50] = {0};
        float fps = get_fps(&ltdata);
        dt = get_integration_period_s(&ltdata);
        sprintf(buffer, "fps:%f, dt:%f", fps, dt);
        SDL_Surface* fpssurf = TTF_RenderText_Solid(font, buffer, fontColor);
        if(fpssurf == NULL){
            printf("error: Failed to create fpssurf %s\n", TTF_GetError());
        }
        SDL_BlitSurface(fpssurf, NULL, p_canvas, NULL);

        renderer.show();

        end_frame(&ltdata);
    }

    SDL_DestroyWindow(p_window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

*/