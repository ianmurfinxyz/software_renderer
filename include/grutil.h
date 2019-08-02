#ifndef _GRUTIL_H_
#define _GRUTIL_H_

#include "Vector3.h"
#include "Matrix4.h"

namespace gr {

// Constructs a view matrix.
// @param pEye: Position vector w.r.t world space to the view space origin.
// @param pAt: Position vector w.r.t world space to the point being looked at.
// @param pUp: World space up axis unit vector.
// @param pOut: Used to output the resultant view matrix.
void MatrixView(Vector3H* pEye, Vector3H* pAt, Vector3H* pUp, Matrix4* pOut);

// Constructs a model->world transformation matrix.
// @param pPos: Position vector to local space origin w.r.t world space.
// @param yaw: angle of rotation around y-axis. (world space UP direction)
// @param pitch: angle of rotation around x-axis. (world space LEFT direction)
// @param roll: angle of rotation around z-axis. (world space FRONT direction)
// @param scale: The scale of the object w.r.t world space in x, y, and z.
// @param pOut: Used to output the resultant transormation matrix.
void MatrixWorld(Vector3H* pPos, float yaw, float pitch, float roll, Vector3H* scale, Matrix4* pOut);

// Constructs a projection matrix. 
// @param fov: Vertical field of view angle. (requires fov >= 0).
// @param aspect: Aspect ratio of the window surface.
// @param near: Near plane distance (z-axis coordinate).
// @param far: Far plane distance (z-axis coordinate).
// @param pOut: Used to output the resultant projection matrix.
// note: if fov = 0, returns an orthographic projection. If fov > 0 returns a 
// perspective projection.
void MatrixProjectionFOV(float fov, float aspect, float near, float far, Matrix4* pOut);

}

#endif