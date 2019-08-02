#ifndef _SCENE_H_
#define _SCENE_H_

#include <SDL2/SDL.h>
#include <vector>
#include "Body.h"
#include "Matrix4.h"
#include "Camera.h"
#include "Renderer.h"

namespace gr {

//
// A collection of bodies viewed through a camera.
//
class Scene {
public:
    Scene(gr::Camera* pCam);
    void setCamera(gr::Camera* pCamera);
    void addBody(gr::Body* pBody);
    void removeBody(gr::Body* pBody);
    void handleInput(SDL_Event& event, float dt);
    void drawScene(gr::Renderer& renderer);

private:
    //
    // Groups bodies with their scene data.
    //
    struct SceneBody {
        gr::Body* pBody;
        gr::Matrix4 WVP;
    };

private:
    void recomputeWVPs();

private:
    gr::Camera* pCam; 
    std::vector<SceneBody> bodies;

    float fov;       // current FOV of the camera.
    float fovVel;    // rate of change of FOV with user input (unit: change per second).
    float angVel;    // rate at which camera rotates on track (unit: radians per second).
    float radialVel; // rate at which camera moves radially (unit: spatial units per second).
};

}

#endif