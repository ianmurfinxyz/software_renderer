#include <math.h>
#include "Camera.h"
#include "grutil.h"

using namespace gr;

Camera::Camera(int width, int height, const gr::Vector3H& at, float distance){
    this->fov = 45; // unit: degrees
    this->aspect = (float)width / (float)height;
    this->near = 1.f;
    this->far = 10000.f;

    this->lookAt = at;

    this->theta = 0.f;
    this->phi = 0.f;
    this->radius = distance;

    updateEye();
    updateVP();
}

void Camera::matrixVP(gr::Matrix4* pVP){
    *pVP = this->VP;
}   

void Camera::matrixWVP(const gr::Matrix4& W, gr::Matrix4* pWVP){
    *pWVP = W.mul(this->VP);
}

void Camera::setFOV(float fov){
    this->fov = fov;
    updateVP();
}

void Camera::setAspect(float aspect){
    this->aspect = aspect;
    updateVP();
}

void Camera::setNearPlane(float nearZ){
    this->near = nearZ;
    updateVP();
}

void Camera::setFarPlane(float farZ){
    this->far = farZ;
    updateVP();
}

void Camera::setDistance(float distance){
    this->radius = distance;
    updateEye();
    updateVP();
}

void Camera::setIncline(float theta){
    this->theta = theta;
    updateEye();
    updateVP();
}

void Camera::setAzimuth(float phi){
    this->phi = phi;
    updateEye();
    updateVP();
}   

void Camera::setLookAt(gr::Vector3H& at){
    this->lookAt = at;
    updateVP();
}

void Camera::moveIncline(float delta_theta){
    this->theta += delta_theta;
    if(this->theta > 6.283185307f){
        this->theta = 0.f;
    }
    updateEye();
    updateVP();
}

void Camera::moveAzimuth(float delta_phi){
    this->phi += delta_phi;
    if(this->phi > 6.283185307f){
        this->phi = 0.f;
    }
    updateEye();
    updateVP();
}

void Camera::moveDistance(float delta_distance){
    this->radius += delta_distance;
    updateEye();
    updateVP();
}

void Camera::updateEye(){
    this->eye.x = this->radius *sin(this->theta) * cos(this->phi);
    this->eye.y = this->radius * cos(this->theta);
    this->eye.z = this->radius * sin(this->theta) * sin(this->phi);
}

void Camera::updateVP(){
    Matrix4 V;
    Matrix4 P;
    Vector3H up(0.f, 1.f, 0.f);
    MatrixView(&this->eye, &this->lookAt, &up, &V);
    MatrixProjectionFOV(this->fov, this->aspect, this->near, this->far, &P);
    this->VP = V.mul(P);
}

