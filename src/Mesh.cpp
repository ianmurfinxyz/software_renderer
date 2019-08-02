#include "Mesh.h"

using namespace gr;

void gr::constructCubeSolid(Mesh& mesh){
    mesh.vertices.reserve(24);

    // VERTICES:

    gr::Vertex v;

    //-- front face ------------------------------------------------------------

    // V0 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V1 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V2 : (V2)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V3 : (V3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    //-- back face -------------------------------------------------------------

    // V4 : (V4)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V5 : (v5)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V6 : (v6)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V7 : (v7)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    //-- left face -------------------------------------------------------------

    // V8 : (V4)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V9 : (v5)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V10 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V11 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- right face ------------------------------------------------------------

    // V12 : (V2)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V13 : (V3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V14 : (v6)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V15 : (v7)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- top face --------------------------------------------------------------

    // V16 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V17 : (V2)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V18 : (v5)
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V19 : (v6)
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- bottom face -----------------------------------------------------------

    // V20 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V21 : (V3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V22 : (V4)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V23 : (v7)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // INDICES:

    // Front: Triangle 0
    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);

    // Front: Triangle 1
    mesh.indices.push_back(0);
    mesh.indices.push_back(2);
    mesh.indices.push_back(3);

    // Back: Triangle 0
    mesh.indices.push_back(5);
    mesh.indices.push_back(7);
    mesh.indices.push_back(6);

    // Back: Triangle 1
    mesh.indices.push_back(5);
    mesh.indices.push_back(4);
    mesh.indices.push_back(7);

    // Left: Triangle 0
    mesh.indices.push_back(8);
    mesh.indices.push_back(11);
    mesh.indices.push_back(10);

    // Left: Triangle 1
    mesh.indices.push_back(8);
    mesh.indices.push_back(9);
    mesh.indices.push_back(11);

    // Right: Triangle 0
    mesh.indices.push_back(13);
    mesh.indices.push_back(14);
    mesh.indices.push_back(15);

    // Right: Triangle 1
    mesh.indices.push_back(13);
    mesh.indices.push_back(12);
    mesh.indices.push_back(14);

    // Top: Triangle 0
    mesh.indices.push_back(16);
    mesh.indices.push_back(19);
    mesh.indices.push_back(17);

    // Top: Triangle 1
    mesh.indices.push_back(16);
    mesh.indices.push_back(18);
    mesh.indices.push_back(19);

    // Bottom: Triangle 0
    mesh.indices.push_back(22);
    mesh.indices.push_back(21);
    mesh.indices.push_back(23);

    // Bottom: Triangle 1
    mesh.indices.push_back(22);
    mesh.indices.push_back(20);
    mesh.indices.push_back(21);
}

void gr::constructCubeGraded(Mesh& mesh){
    mesh.vertices.reserve(8);

    // VERTICES:

    gr::Vertex v;

    // V0
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    mesh.vertices.push_back(v);

    // V1
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V2
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V3
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V4
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V5
    v.posL.x = -0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V6
    v.posL.x = 0.5f;
    v.posL.y = 0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V7
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // INDICES:

    // Front: Triangle 0
    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);

    // Front: Triangle 1
    mesh.indices.push_back(0);
    mesh.indices.push_back(2);
    mesh.indices.push_back(3);

    // Bottom: Triangle 0
    mesh.indices.push_back(4);
    mesh.indices.push_back(3);
    mesh.indices.push_back(7);

    // Bottom: Triangle 1
    mesh.indices.push_back(4);
    mesh.indices.push_back(0);
    mesh.indices.push_back(3);

    // Left: Triangle 0
    mesh.indices.push_back(4);
    mesh.indices.push_back(1);
    mesh.indices.push_back(0);

    // Left: Triangle 1
    mesh.indices.push_back(4);
    mesh.indices.push_back(5);
    mesh.indices.push_back(1);

    // Top: Triangle 0
    mesh.indices.push_back(1);
    mesh.indices.push_back(6);
    mesh.indices.push_back(2);

    // Top: Triangle 1
    mesh.indices.push_back(1);
    mesh.indices.push_back(5);
    mesh.indices.push_back(6);

    // Back: Triangle 0
    mesh.indices.push_back(5);
    mesh.indices.push_back(7);
    mesh.indices.push_back(6);

    // Back: Triangle 1
    mesh.indices.push_back(5);
    mesh.indices.push_back(4);
    mesh.indices.push_back(7);

    // Right: Triangle 0
    mesh.indices.push_back(3);
    mesh.indices.push_back(6);
    mesh.indices.push_back(7);

    // Right: Triangle 1
    mesh.indices.push_back(3);
    mesh.indices.push_back(2);
    mesh.indices.push_back(6);
}

void gr::constructPyramidSolid(Mesh& mesh){
    mesh.vertices.reserve(16);

    // VERTICES:

    gr::Vertex v;

    //-- Base face -------------------------------------------------------------

    // V0 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V1 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V2 : (v2)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V3 : (v3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- Front face ------------------------------------------------------------

    // V4 : (V4)
    v.posL.x = 0.f;
    v.posL.y = 0.5f;
    v.posL.z = 0.f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V5 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V6 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- Left face -------------------------------------------------------------

    // V7 : (v2)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V8 : (V4)
    v.posL.x = 0.f;
    v.posL.y = 0.5f;
    v.posL.z = 0.f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    // V9 : (V1)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(0);
    v.color.setG(0);
    v.color.setB(255);
    mesh.vertices.push_back(v);

    //-- Right face ------------------------------------------------------------

    // V10 : (V0)
    v.posL.x = -0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V11 : (V4)
    v.posL.x = 0.f;
    v.posL.y = 0.5f;
    v.posL.z = 0.f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V12 : (v3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(0);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    //-- Back face -------------------------------------------------------------

    // V13 : (v3)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = -0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V14 : (V4)
    v.posL.x = 0.f;
    v.posL.y = 0.5f;
    v.posL.z = 0.f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // V15 : (v2)
    v.posL.x = 0.5f;
    v.posL.y = -0.5f;
    v.posL.z = 0.5f;
    v.color.setR(255);
    v.color.setG(255);
    v.color.setB(0);
    mesh.vertices.push_back(v);

    // INDICES:

    // Base: Triangle 0
    mesh.indices.push_back(2);
    mesh.indices.push_back(1);
    mesh.indices.push_back(0);

    // Base: Triangle 1
    mesh.indices.push_back(2);
    mesh.indices.push_back(0);
    mesh.indices.push_back(3);

    // Front: Triangle 0
    mesh.indices.push_back(6);
    mesh.indices.push_back(4);
    mesh.indices.push_back(5);

    // Left: Triangle 0
    mesh.indices.push_back(7);
    mesh.indices.push_back(8);
    mesh.indices.push_back(9);

    // Right: Triangle 0
    mesh.indices.push_back(10);
    mesh.indices.push_back(11);
    mesh.indices.push_back(12);

    // Back: Triangle 0
    mesh.indices.push_back(13);
    mesh.indices.push_back(14);
    mesh.indices.push_back(15);
}