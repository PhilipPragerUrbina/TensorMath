# TensorMath
### A header-only linear algebra library

Designed to be a lightweight alternative to libraries like Eigen.

Perfect for small computer graphics, physics, or machine learning projects.

_A little taste:_
```c++
Vector3 origin{1,2.2,3.24};
double distance = 3.0;
//write your code almost like the equation!
Vector3 ray_position = origin + dir.normalized() * distance;
```
>There is a lot more than just this,take a look at  the Docs!  

Components:
- Matrices
- Vectors
- Constant size vectors(serializable)
- Constant size matrices(serializable)


Features:
- Header only
- All the utilities you will ever need
- Completely integrated types, lots of operators
- Documented and tested
- Clean commented code, easy to modify

Potential Future Features:
- Some extra goodies for GPU acceleration
- CUDA version and Cuda math interoperability
- Tensors(n dimensional matrices)
- Sparse matrices
- Templated version(not just doubles)
- Maximum matrix multiplication optimizations(memory layout, multithreading, chunking, etc)

