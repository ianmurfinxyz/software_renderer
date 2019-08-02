#ifndef _COLOR_H_
#define _COLOR_H_

#include <SDL2/SDL.h>

namespace gr{

class Color{
public:
    Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 0);

    void setR(Uint8 r);
    void setG(Uint8 g);
    void setB(Uint8 b);
    void setA(Uint8 a);

    Uint8 getR() const;
    Uint8 getG() const;
    Uint8 getB() const;
    Uint8 getA() const;

    Uint32 getPacked(SDL_PixelFormat* pFmt) const;
    

private:
    Uint8 rgba[4];
};

}


#endif