#ifndef _MESH_H_
#define _MESH_H_

#include <SDL2/SDL.h>
#include <vector>
#include "Vector3.h"
#include "Color.h"

namespace gr{

// A mesh vertex.
//
// @member posL: A position vector w.r.t the local coordinate space of the mesh.
// @member color: A packed color (RGBA) for the vertex.
//
struct Vertex {
    Vector3H posL;
    Color color;
};

// A geometric object which can be drawn to the screen.
//
// @member vertices: Set of all unique vertices in the mesh.
// @member indices: set of indices into 'vertices' vector. Every subset of 3 
//         indices defines a triangle, thus the vector size should be a multiple
//         of 3.
struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

//
// Constructs a cube with each side a unique solid color.
//
void constructCubeSolid(Mesh& mesh);

//
// Constructs a cube with each corner a unique color that is interpolated 
// over the sides.
//
void constructCubeGraded(Mesh& mesh);

//
// Constructs a pyramid with each side a unique solid color.
//
void constructPyramidSolid(Mesh& mesh);

}

#endif