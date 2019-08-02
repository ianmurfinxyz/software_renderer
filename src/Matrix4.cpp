#include "Matrix4.h"

using namespace gr;

Matrix4::Matrix4(){
    this->e[0][0] = 0.f;
    this->e[0][1] = 0.f;
    this->e[0][2] = 0.f;
    this->e[0][3] = 0.f;

    this->e[1][0] = 0.f;
    this->e[1][1] = 0.f;
    this->e[1][2] = 0.f;
    this->e[1][3] = 0.f;

    this->e[2][0] = 0.f;
    this->e[2][1] = 0.f;
    this->e[2][2] = 0.f;
    this->e[2][3] = 0.f;

    this->e[3][0] = 0.f;
    this->e[3][1] = 0.f;
    this->e[3][2] = 0.f;
    this->e[3][3] = 0.f;
}

Matrix4::Matrix4(float e00, float e01, float e02, float e03,
                 float e10, float e11, float e12, float e13,
                 float e20, float e21, float e22, float e23,
                 float e30, float e31, float e32, float e33){
    this->e[0][0] = e00;
    this->e[0][1] = e01;
    this->e[0][2] = e02;
    this->e[0][3] = e03;

    this->e[1][0] = e10;
    this->e[1][1] = e11;
    this->e[1][2] = e12;
    this->e[1][3] = e13;

    this->e[2][0] = e20;
    this->e[2][1] = e21;
    this->e[2][2] = e22;
    this->e[2][3] = e23;

    this->e[3][0] = e30;
    this->e[3][1] = e31;
    this->e[3][2] = e32;
    this->e[3][3] = e33;
}

Matrix4 Matrix4::mul(const Matrix4& m) const{
    Matrix4 tmp;
    for(int k = 0; k <= 3; k++){
        for(int j = 0; j <= 3; j++){
            for(int i = 0; i <= 3; i++){
                tmp.e[k][j] += this->e[k][i] * m.e[i][j];
            }
        }
    }
    return tmp;
}