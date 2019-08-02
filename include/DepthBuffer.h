#ifndef _DEPTH_BUFFER_H_
#define _DEPTH_BUFFER_H_

#include <string>

namespace gr {

class DepthBuffer {
public:
    DepthBuffer(int width, int height);

    ~DepthBuffer();

    //
    // Fills the buffer with values of infinity.
    //
    void clear();

    //
    // Sets the value of the pixel at pos [row,col] to the value "depth".
    //
    void putPixel(int row, int col, double depth);

    //
    // Sets the value of the pixel at pos [row,col] to the value "depth" if
    // the value is less than the current value of the pixel. Note: all pixels
    // are initialised to inifinity.
    //
    void comparePutPixel(int row, int col, double depth);

    //
    // Tests if the value of the argument 'depth' is closer to the screen than 
    // the value in the buffer for a given pixel.
    //
    bool isCloser(int row, int col, double depth);

    //
    // converts a depth value to a grey-scale color value.
    //
    void depthToColor(float depth, float* r, float* g, float* b);

    //
    // Export the image to a file.
    //
    void exportAsImage(std::string filepath);

private:
    double* buffer;
    int size;
    int pitch;
    float max;
    float colorSF;  // conversion factor from depth value to color value.
};

}

#endif