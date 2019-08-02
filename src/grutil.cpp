#include <math.h>
#include "Vector3.h"
#include "Matrix4.h"

namespace gr {

// Constructs a view matrix.
// @param pEye: Position vector w.r.t world space to the view space origin.
// @param pAt: Position vector w.r.t world space to the point being looked at.
// @param pUp: World space up axis unit vector.
// @param pOut: Used to output the resultant view matrix.
void MatrixView(Vector3H* pEye, Vector3H* pAt, Vector3H* pUp, Matrix4* pOut){
    // calculate the unit basis vectors of the view space w.r.t world space.
    Vector3H zbasis = pAt->sub(*pEye); 
    zbasis.normaliseIP();
    Vector3H xbasis = pUp->cross(zbasis);
    Vector3H ybasis = zbasis.cross(xbasis);

    // compute the world->view matrix which is the inverse of the view->world 
    // matrix.
    pOut->e[0][0] = xbasis.x;
    pOut->e[0][1] = ybasis.x;
    pOut->e[0][2] = zbasis.x;
    pOut->e[0][3] = 0.f;
    pOut->e[1][0] = xbasis.y;
    pOut->e[1][1] = ybasis.y;
    pOut->e[1][2] = zbasis.y;
    pOut->e[1][3] = 0.f;
    pOut->e[2][0] = xbasis.z;
    pOut->e[2][1] = ybasis.z;
    pOut->e[2][2] = zbasis.z;
    pOut->e[2][3] = 0.f;
    pOut->e[3][0] = -(pEye->dot(xbasis));
    pOut->e[3][1] = -(pEye->dot(ybasis));
    pOut->e[3][2] = -(pEye->dot(zbasis));
    pOut->e[3][3] = 1.f;
}

// Constructs a model->world transformation matrix.
// @param pPos: Position vector to local space origin w.r.t world space.
// @param yaw: angle of rotation around y-axis. (world space UP direction)
// @param pitch: angle of rotation around x-axis. (world space LEFT direction)
// @param roll: angle of rotation around z-axis. (world space FRONT direction)
// @param scale: The scale of the object w.r.t world space in x, y, and z.
// @param pOut: Used to output the resultant transormation matrix.
void MatrixWorld(Vector3H* pPos, float yaw, float pitch, float roll, Vector3H* scale, Matrix4* pOut){
    pOut->e[0][0] = scale->x*cos(yaw)*cos(roll);
    pOut->e[0][1] = scale->y*cos(yaw)*sin(roll);
    pOut->e[0][2] = -scale->z*sin(yaw);
    pOut->e[0][3] = 0.f;
    pOut->e[1][0] = scale->x*((sin(yaw)*sin(pitch)*cos(roll))-(sin(roll)*cos(pitch)));
    pOut->e[1][1] = scale->y*((sin(yaw)*sin(pitch)*sin(roll))+(cos(pitch)*cos(roll)));
    pOut->e[1][2] = scale->z*sin(pitch)*cos(yaw);
    pOut->e[1][3] = 0.f;
    pOut->e[2][0] = scale->x*((cos(pitch)*sin(yaw)*cos(roll))+(sin(roll)*sin(pitch)));
    pOut->e[2][1] = scale->y*((cos(pitch)*sin(yaw)*sin(roll))-(sin(pitch)*cos(roll)));
    pOut->e[2][2] = scale->z*cos(pitch)*cos(yaw);
    pOut->e[2][3] = 0.f;
    pOut->e[3][0] = pPos->x;
    pOut->e[3][1] = pPos->y;
    pOut->e[3][2] = pPos->z;
    pOut->e[3][3] = 1.f;
}

// Constructs a projection matrix. 
// @param fov: Vertical field of view angle. (requires fov >= 0). (unit: degrees)
// @param aspect: Aspect ratio of the window surface.
// @param near: Near plane distance (z-axis coordinate).
// @param far: Far plane distance (z-axis coordinate).
// @param pOut: Used to output the resultant projection matrix.
// note: if fov = 0, returns an orthographic projection. If fov > 0 returns a 
// perspective projection.
void MatrixProjectionFOV(float fov, float aspect, float near, float far, Matrix4* pOut){
    pOut->e[0][0] = 1.f/aspect;
    pOut->e[0][1] = 0.f;
    pOut->e[0][2] = 0.f;
    pOut->e[0][3] = 0.f;
    pOut->e[1][0] = 0.f;
    pOut->e[1][1] = 1.f;
    pOut->e[1][2] = 0.f;
    pOut->e[1][3] = 0.f;
    pOut->e[2][0] = 0.f;
    pOut->e[2][1] = 0.f;
    pOut->e[2][2] = far/(far-near);
    pOut->e[2][3] = tan((fov*M_PI)/180.f);
    pOut->e[3][0] = 0.f;
    pOut->e[3][1] = 0.f;
    pOut->e[3][2] = -near*far/(far-near); 
    pOut->e[3][3] = 1.f;
}

}