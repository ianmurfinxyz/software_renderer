#include "Body.h"
#include "grutil.h"

using namespace gr;

Body::Body(gr::Mesh* pMesh) : pMesh(pMesh), posW(0.f, 0.f, 0.f), yaw(0.f), 
    roll(0.f), pitch(0.f), scale(1.f) {
}

Body::Body(gr::Mesh* pMesh, 
           float x, 
           float y, 
           float z, 
           float yaw, 
           float pitch, 
           float roll) : 
    pMesh(pMesh),
    posW(x, y, z),
    yaw(yaw),
    pitch(pitch),
    roll(roll),
    scale(1.f) {
}

void Body::setPosX(float x){
    this->posW.x = x;
}

void Body::setPosY(float y){
    this->posW.y = y;
}

void Body::setPosZ(float z){
    this->posW.z = z;
}

void Body::setYaw(float yaw){
    this->yaw = yaw;
}

void Body::setPitch(float pitch){
    this->pitch = pitch;
}

void Body::setRoll(float roll){
    this->roll = roll;
}

void Body::setScale(float scale){
    this->scale = scale;
}

float Body::getPosX() const{
    return this->posW.x;
}

float Body::getPosY() const{
    return this->posW.y;
}
float Body::getPosZ() const{
    return this->posW.z;
}

float Body::getYaw() const{
    return this->yaw;
}

float Body::getPitch() const{
    return this->pitch;
}

float Body::getRoll() const{
    return this->roll;
}

float Body::getScale() const{
    return this->scale;
}

Mesh* Body::getMesh() const{
    return this->pMesh;
}

void Body::buildWorld(gr::Matrix4* pOut){
    Vector3H scale(this->scale, this->scale, this->scale);
    MatrixWorld(&this->posW, this->yaw, this->pitch, this->roll, &scale, pOut);
}