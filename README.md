bezier-surfaces
===============
C++ implementation of uniform and adaptive tesselation of bezier patches.
![Screenshot](img/gif-1.gif?raw=true)


## Dependencies

 * OpenGL and GLUT.
 * Eigen.
 * C++ compiler.

## Build
```
cd path/to/bezier-surfaces
make
./bezier-surfaces test.bez -u 0.4
```

## Usage
```
./bezier-surfaces [.bez file] [-u for uniform / -a for adaptive] [error measurement for adaptive / spacing for uniform]
```

 * Arrow Keys to rotate the bezier surface
 * SHIFT + Arrow Keys to translate the surface
