#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector3.h"
#include "Matrix4.h"

namespace gr {

//
// A camera on a spherical track around a point.
//
class Camera {
public:
    // 
    // Sets up the camera with default values (not NULL values).
    //
    Camera(int width, int height, const gr::Vector3H& at, float distance);

    //
    // returns the view-projection matrix for this camera.
    //
    void matrixVP(gr::Matrix4* pVP);

    //
    // returns the world-view-projection matrix for a body in view of this 
    // camera.
    //
    void matrixWVP(const gr::Matrix4& W, gr::Matrix4* pWVP);

    void setFOV(float fov);
    void setAspect(float aspect);
    void setNearPlane(float nearZ);
    void setFarPlane(float farZ);
    void setDistance(float distance);
    void setIncline(float theta);
    void setAzimuth(float phi);
    void setLookAt(gr::Vector3H& at);

    void moveIncline(float delta_theta);
    void moveAzimuth(float delta_phi);
    void moveDistance(float delta_distance);

private:
    void updateEye();
    void updateVP();

private:
    float fov; // field of view of camera (0 = orthogonal camera).
    float aspect;
    float near;
    float far;

    gr::Vector3H eye; // eye position of the camera.
    gr::Vector3H lookAt; // origin of sphere tack; point being looked at.

    float theta; // incline angle (angle between radial vector and y-axis).
    float phi;   // azumthal angle ( angle between radial vector and z=0 plane).
    float radius;// radial distance from sphere origin (i.e. sphere track radius).

    gr::Matrix4 VP; // only recalculate when change for efficiency.
};

}

#endif