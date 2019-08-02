#ifndef _BODY_H_
#define _BODY_H_

#include "Mesh.h"
#include "Matrix4.h"
#include "Vector3.h"

namespace gr {

//
// Represents a renderable body in a scene.
//
class Body {
public:
    Body(gr::Mesh* pMesh);
    Body(gr::Mesh* pMesh, float x, float y, float z, float yaw, float pitch, float roll);

    void setPosX(float x);
    void setPosY(float y);
    void setPosZ(float z);
    void setYaw(float yaw);
    void setPitch(float pitch);
    void setRoll(float roll);
    void setScale(float scale);

    float getPosX() const;
    float getPosY() const;
    float getPosZ() const;
    float getYaw() const;
    float getPitch() const;
    float getRoll() const;
    float getScale() const;

    gr::Mesh* getMesh() const;

    void buildWorld(gr::Matrix4* pOut);

private:
    gr::Mesh* pMesh;
    gr::Vector3H posW;
    float yaw;
    float roll;
    float pitch;
    float scale; // uniform scale.
};

}

#endif