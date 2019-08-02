#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace gr{

//
// A 4x4 matrix of floats.
//
class Matrix4 {
public:
    Matrix4();

    Matrix4(float e00, float e01, float e02, float e03,
               float e10, float e11, float e12, float e13,
               float e20, float e21, float e22, float e23,
               float e30, float e31, float e32, float e33);

    //
    // Multiplies this matrix by another matrix and returns the result as a new
    // matrix.
    //
    Matrix4 mul(const Matrix4& m) const;

public:
    float e[4][4]; // note: [row][col]
};

}

#endif