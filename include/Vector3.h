#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "Matrix4.h"

namespace gr {

//
// A vector in R^3 homogeneous coordinates.
//
class Vector3H {
public:
    Vector3H();

    Vector3H(float x, float y, float z);

    // 
    // Adds another vector to this vector and returns the result as a new 
    // vector.
    //
    Vector3H add(const Vector3H& v) const;

    // 
    // Adds another vector to this vector in-place.
    //
    void addIP(const Vector3H& v);

    // 
    // Subtracts another vector from this vector and returns the result as a new 
    // vector.
    //
    Vector3H sub(const Vector3H& v) const;

    // 
    // Subtracts another vector from this vector in-place.
    //
    void subIP(const Vector3H& v);

    //
    // Scales this vector and returns the result as a new vector.
    //
    Vector3H scale(float factor) const;

    //
    // Scales this vector in-place.
    //
    void scaleIP(float factor);

    //
    // Performs the dot product between this vector and another vector.
    //
    float dot(const Vector3H& v) const;

    //
    // Performs the cross product vetween this vector and another vector and 
    // returns the result as a new vector.
    //
    Vector3H cross(const Vector3H& v) const;

    //
    // Multiplies this vector by a 4x4 matrix and returns the result as a new 
    // vector.
    //
    Vector3H mul(const Matrix4& m) const;

    //
    // Multiples this vector by a 4x4 vector in-place.
    //
    void mulIP(const Matrix4& m);

    //
    // Normalises the vector and returns the result as a new vector.
    //
    Vector3H normalise() const;

    //
    // Normalises the vector in-place.
    //
    void normaliseIP();

    //
    // Calculates and returns the magnitude of the vector. 
    //
    float length() const;

public:
    float x;
    float y;
    float z;
    float w;
};

}

#endif