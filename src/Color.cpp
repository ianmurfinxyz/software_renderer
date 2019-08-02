#include <SDL2/SDL.h>
#include "Color.h"

using namespace gr;

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->rgba[0] = r;
    this->rgba[1] = g;
    this->rgba[2] = b;
    this->rgba[3] = a;
}

void Color::setR(Uint8 r){
    this->rgba[0] = r;
}

void Color::setG(Uint8 g){
    this->rgba[1] = g;
}

void Color::setB(Uint8 b){
    this->rgba[2] = b;
}

void Color::setA(Uint8 a){
    this->rgba[3] = a;
}

Uint8 Color::getR() const{
    return this->rgba[0];
}

Uint8 Color::getG() const{
    return this->rgba[1];
}

Uint8 Color::getB() const{
    return this->rgba[2];
}

Uint8 Color::getA() const{
    return this->rgba[3];
}

Uint32 Color::getPacked(SDL_PixelFormat* pFmt) const{
    return SDL_MapRGBA(pFmt, 
                       this->rgba[0], 
                       this->rgba[1], 
                       this->rgba[2], 
                       this->rgba[3]);
}