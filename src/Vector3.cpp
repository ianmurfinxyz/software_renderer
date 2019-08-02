#include <math.h>
#include "Vector3.h"

using namespace gr;

Vector3H::Vector3H() : x(0.f), y(0.f), z(0.f), w(1.f) {
}

Vector3H::Vector3H(float x, float y, float z) : x(x), y(y), z(z), w(1.f) {
}

Vector3H Vector3H::add(const Vector3H& v) const{
    Vector3H tmp;
    tmp.x = this->x + v.x;
    tmp.y = this->y + v.y;
    tmp.z = this->z + v.z;
    return tmp;
}

void Vector3H::addIP(const Vector3H& v){
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;
}

Vector3H Vector3H::sub(const Vector3H& v) const{
    Vector3H tmp;
    tmp.x = this->x - v.x;
    tmp.y = this->y - v.y;
    tmp.z = this->z - v.z;
    return tmp;
}

void Vector3H::subIP(const Vector3H& v){
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;
}

Vector3H Vector3H::scale(float factor) const{
    Vector3H tmp;
    tmp.x = this->x * factor;
    tmp.y = this->y * factor;
    tmp.z = this->z * factor;
    return tmp;
}

void Vector3H::scaleIP(float factor){
    this->x *= factor;
    this->y *= factor;
    this->z *= factor;
}

float Vector3H::dot(const Vector3H& v) const{
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

Vector3H Vector3H::cross(const Vector3H& v) const{
    Vector3H tmp;
    tmp.x = (this->y * v.z) - (this->z * v.y);
    tmp.y = -((this->x * v.z) - (this->z * v.x));
    tmp.z = (this->x * v.y) - (this->y * v.x);
    return tmp;
}

Vector3H Vector3H::mul(const Matrix4& m) const{
    Vector3H tmp;
    float in[4] ={this->x, this->y, this->z, this->w};
    float rs[4] = {0.f, 0.f, 0.f, 0.f};
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){
            rs[i] += in[j] * m.e[j][i];
        }
    }
    tmp.x = rs[0];
    tmp.y = rs[1];
    tmp.z = rs[2];
    tmp.w = rs[3];
    return tmp;
}

void Vector3H::mulIP(const Matrix4& m){
    float in[4] ={this->x, this->y, this->z, this->w};
    float rs[4] = {0.f, 0.f, 0.f, 0.f};
    for(int i = 0; i <= 3; i++){
        for(int j = 0; j <= 3; j++){
            rs[i] += in[j] * m.e[j][i];
        }
    }
    this->x = rs[0];
    this->y = rs[1];
    this->z = rs[2];
    this->w = rs[3];
}

Vector3H Vector3H::normalise() const{
    Vector3H tmp(*this);
    float factor = 1 / sqrt(this->dot(*this));
    tmp.scaleIP(factor);
    return tmp;
}

void Vector3H::normaliseIP(){
    float factor = 1 / sqrt(this->dot(*this));
    this->scaleIP(factor);
}

float Vector3H::length() const{
    return sqrt(this->dot(*this));
}