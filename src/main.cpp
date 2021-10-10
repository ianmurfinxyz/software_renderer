#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "looptime.h"
#include "Renderer.h"
#include "Mesh.h"
#include "grutil.h"
#include "Body.h"
#include "Camera.h"
#include "Scene.h"

using namespace gr;

int main(int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("Unable to initialise SDL: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() == -1){
        printf("error: Failed to initialise SDL_ttf: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
    }

    SDL_Surface* p_canvas = SDL_GetWindowSurface(p_window);

    TTF_Font* font = TTF_OpenFont("assets/SourceCodePro-Regular.ttf", 16);
    SDL_Color fontColor = {255, 41, 80};
    if(!font){
        printf("error: Failed to load font file: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    gr::Renderer renderer(p_window, 800, 600);

    // build the meshes...
    gr::Mesh cubeSolid;
    gr::Mesh cubeGraded;
    gr::Mesh pyramidSolid;
    gr::constructCubeSolid(cubeSolid);
    gr::constructCubeGraded(cubeGraded);
    gr::constructPyramidSolid(pyramidSolid);

    // construct the scene...
    gr::Body cubeA(&cubeSolid, -3.f, 0.f, 3.f, 0.f, 0.f, 0.f);
    gr::Body cubeB(&cubeGraded, 3.f, 0.f, -3.f, 0.f, 0.f, 0.f);
    gr::Body pyramidA(&pyramidSolid, -3.f, 0.f, -3.f, 2.f, 3.141592654f, 0.f);
    gr::Body pyramidB(&pyramidSolid, 3.f, 0.f, 3.f, 0.f, 3.141592654f, 0.f);
    cubeA.setScale(2.f);
    pyramidB.setScale(3.f);

    gr::Vector3H at(0.f, 0.f, 0.f);
    gr::Camera cam(800, 600, at, 10.f);
    cam.setIncline(1.570796327f);

    gr::Scene scene(&cam);
    scene.addBody(&cubeA);
    scene.addBody(&cubeB);
    scene.addBody(&pyramidA);
    scene.addBody(&pyramidB);

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
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        is_running = false;
                        break;
                    case SDLK_1:
                        renderer.setModeDrawSceneBuffer();
                        break;
                    case SDLK_2:
                        renderer.setModeDrawDepthBuffer();
                        break;
                }
            }
            scene.handleInput(event, dt);
        }

        renderer.clear();
        scene.drawScene(renderer);
        
        // output FPS...
        char buffer[50] = {0};
        float fps = get_fps(&ltdata);
        dt = get_integration_period_s(&ltdata);
        sprintf(buffer, "fps:%f, dt:%f", fps, dt);
        SDL_Surface* fpssurf = TTF_RenderText_Solid(font, buffer, fontColor);
        if(fpssurf == NULL){
            printf("error: Failed to create fpssurf %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
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
