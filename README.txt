================================================================================
                    Real-Time Software Renderer in C++
================================================================================

This project is a real-time software renderer written from scratch in C++. The 
renderer makes no use of Opengl or DirectX (or any hardware acceleration) 
throughout the pipeline. SDL2 is used as the backend to blit the renderers 
output image to the window.

I started this project with the goal of:

- Studying the algorithms behind 3D graphics cards.
- Expanding my knowledge of linear algebra and projective geometry.

Since this is the 1st renderer I have implemented, the approach I took was to 
strip the problem down into its most simple of form. Thus this initial version 
implements only those aspects of the pipeline of core importance to getting an 
image on screen. No lighting, textures, normal mapping or any other more 
advanced effects are implemented in this version.

The following link is to a video demonstration of a rendering of a basic 3D 
scene.

https://www.youtube.com/watch?v=ZjEFwCRI4no&feature=youtu.be

note: the file 'demo' in the repository is the compiled demonstration being 
shown in the video linked above.

[pipeline]

The pipeline is kept as simple as possible. The following details the stages of
the pipeline and the algorithms used in each.

(1): Vertex Shader: Hardcoded (i.e. not programmable), simply transforms local 
  position vectors by a world-view-projection matrix (WVP matrix).

(2): Clipping: Uses the Sutherland-Hodgman algorithm to clip all geometry 
  against the view (camera) frustrum.

(3): Perspective Divide.

(4): Backface Culling: Uses the shoelace algorithm.

(5): Triangle Rasterisation: Uses edge equations (half-space algorithm). 
  Interpolates vertex properties using barycentric coordinates. Uses a depth
  buffer to sort draw order.

[features]

- Custom math library (Matrices, Vectors) including functions to construct 
  required transformation matrices.
- Index buffers to prevent duplicate vertices in meshes.
- Orthographic and perspective projections.
- Depth buffering.
- Switchable rendering modes: draw depth buffer or back buffer.
- Interactive scene: transformable camera and objects.

[todo]

For the next version of the project I want to implement:

- .obj file (and scene) loading.
- line and wireframe rendering (so far only fill triangles).
- perspective correct texture mapping.
- lighting and shading.
- Normal mapping.

[dependecies]

- SDL2
- SDL2_ttf

[Resources]

The following (in no particular order) is a selection of resources I found most 
helpful when researching for this project:

[1]: http://www.cs.bath.ac.uk/~pjw/NOTES/75-ACG/ch6-projective.pdf
[2]: https://www.uni-obuda.hu/journal/Mileff_Nehez_Dudra_63.pdf
[3]: http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.162.1859&rep=rep1&type=pdf
[4]: http://www.cs.gettysburg.edu/~ilinkin/courses/Fall-2014/cs373/handouts/papers/sh-rpc-74.pdf
[5]: Introduction to 3G Game Programming with DirectX10 by Frank D.Luna
[6]: Game Engine Architecture by Jason Gregory

[License]

MIT License

Copyright (c) 2019 Ian Murfin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
