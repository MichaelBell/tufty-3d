# Tufty 3D Rendering

This project renders 3D models on the Tufty2040.  Still very much a work in progress!

To make a model suitable for the renderer, run the convert.py script on a model in obj format, e.g.:

    python convert.py teapot

to convert teapot.obj to teapot.cpp

The model must have less than 512 vertices, and all faces must be triangles.

You can use [Mesh Lab](https://www.meshlab.net/) to reduce the number of triangles in meshes - use the Simplification: Quadric Edge Collapse Decimation function, and set the number of faces to around 800.  Then export the mesh to an obj file turning off Vert Normal, TexCoord and Polygonal.
