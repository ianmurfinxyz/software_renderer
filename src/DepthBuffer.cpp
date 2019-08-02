#include <limits>
#include "DepthBuffer.h"

using namespace gr;

DepthBuffer::DepthBuffer(int width, int height){
    this->size = width * height;
    this->pitch = width;
    this->buffer = new double[this->size];
    this->max = std::numeric_limits<double>::max();
    this->colorSF = 255.f / this->max;

    for(int i = 0; i < this->size; i++){
        this->buffer[i] = this->max;
    }
}

DepthBuffer::~DepthBuffer(){
    delete[] this->buffer;
}

void DepthBuffer::clear(){
    for(int i = 0; i < this->size; i++){
        this->buffer[i] = this->max;
    }
}

void DepthBuffer::putPixel(int x, int y, double depth){
    int element = (y * this->pitch) + x;
    if(element > this->size){
        return;
    }
    this->buffer[element] = depth;
}

void DepthBuffer::comparePutPixel(int x, int y, double depth){
    int element = (y * this->pitch) + x;
    if(element > this->size){
        return;
    }
    if(this->buffer[element] > depth){
        this->buffer[element] = depth;
    }
}

bool DepthBuffer::isCloser(int x, int y, double depth){
    int element = (y * this->pitch) + x;
    if(element > this->size){
        return false;
    }
    bool result;
    (this->buffer[element] > depth) ? (result = true) : (result = false);
    return result;
}

void DepthBuffer::depthToColor(float depth, float* r, float* g, float* b){
    //if(depth > 1.f){
    //    depth = 1.f;
    //}
    //else if(depth < 0.f){
    //    depth = 0.f;
    //}
    *r = *g = *b = 255.f * (1.f - depth);
}

void DepthBuffer::exportAsImage(std::string filepath){

}