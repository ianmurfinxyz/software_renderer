#include "Scene.h"

using namespace gr;

Scene::Scene(gr::Camera* pCam) : pCam(pCam), angVel(1.5f * 3.141592654), 
    radialVel(8.f), fov(45.f), fovVel(10.f){
}

void Scene::setCamera(gr::Camera* pCamera){
    this->pCam = pCam;
}

void Scene::addBody(gr::Body* pBody){
    SceneBody sb;
    sb.pBody = pBody;
    
    pBody->buildWorld(&sb.WVP);
    this->pCam->matrixWVP(sb.WVP, &sb.WVP);

    this->bodies.push_back(sb);
}

void Scene::removeBody(gr::Body* pBody){
    std::vector<SceneBody>::iterator iter = this->bodies.begin();
    for(; iter != this->bodies.end(); ++iter){
        if((*iter).pBody == pBody){
            this->bodies.erase(iter);
            break;
        }
    }
}

void Scene::handleInput(SDL_Event& event, float dt){
    bool camChanged = false;
    switch(event.type){
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                    pCam->moveAzimuth(angVel * dt);
                    camChanged = true;
                    break;
                case SDLK_LEFT:
                    pCam->moveAzimuth(-angVel * dt);
                    camChanged = true;
                    break;
                case SDLK_UP:
                    pCam->moveIncline(angVel * dt);
                    camChanged = true;
                    break;
                case SDLK_DOWN:
                    pCam->moveIncline(-angVel * dt);
                    camChanged = true;
                    break;
                case SDLK_f:
                    pCam->moveDistance(-radialVel * dt);
                    camChanged = true;
                    break;
                case SDLK_b:
                    pCam->moveDistance(radialVel * dt);
                    camChanged = true;
                    break;
                case SDLK_o:
                    this->fov -= fovVel * dt; // more orthographic.
                    if(this->fov < 0.f){
                        this->fov = 0.f;
                    }
                    pCam->setFOV(this->fov);
                    camChanged = true;
                    break;
                case SDLK_p:
                    this->fov += fovVel * dt; // more perspective.
                    if(this->fov > 60.f){
                        this->fov = 60.f;
                    }
                    pCam->setFOV(this->fov);
                    camChanged = true;
                    break;
            }
            break;
    }

    if(camChanged){
        recomputeWVPs();
    }
}

void Scene::drawScene(gr::Renderer& renderer){
    std::vector<SceneBody>::iterator iter = this->bodies.begin();
    for(; iter != this->bodies.end(); ++iter){
        renderer.draw(*(*iter).pBody->getMesh(), (*iter).WVP);
    }
}

void Scene::recomputeWVPs(){
    std::vector<SceneBody>::iterator iter = this->bodies.begin();
    for(; iter != this->bodies.end(); ++iter){
        (*iter).pBody->buildWorld(&(*iter).WVP);
        this->pCam->matrixWVP((*iter).WVP, &(*iter).WVP);
    }
}