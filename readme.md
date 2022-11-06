# TensorMath
### A header-only linear algebra library

Designed to be a lightweight alternative to libraries like Eigen.

Usable for small computer graphics, physics, or machine learning projects.




_A little taste:_
```c++
Vector3 origin{1,2.2,3.24};
double distance = 3.0;
//write your code almost like the equation!
Vector3 ray_position = origin + dir.normalized() * distance;
```
>There is a lot more than just this, take a look at the **_Docs_**!  

Components:
- Matrices
- Vectors
- Constant size vectors(serializable)
- Constant size matrices(serializable)


  All of it is under the TensorMath  namespace.

Features:
- Header only
- All the utilities you will ever need
- Completely integrated types, lots of operators
- Documented and tested
- Clean commented code, easy to modify

  
> Known Issue:
>
 > Subpar performance compared to specialized Vector3 or Vector2 implementations. Due to initializer lists being slow, 
and the compiler not being able to make as many assumptions about the library due to its generalized nature.
>
> _Still a great reference for making more specialized implementations though!_






