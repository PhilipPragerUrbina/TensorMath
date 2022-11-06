# Fixed Vectors and Matrices
Have a constant size that is specified in the template.

No longer have matching size asserts, use the templates instead. 

They do not have any pointers, no dynamically allocated memory.
This makes them optimal for serialization, GPU usage, and copying data.

Always use FixedVector and FixedMatrix when possible, for better performance.

## FixedMatrix
```c++
FixedMatrix<width,height> a();
```
Has same API and methods, just used FixedMatrix in place of Matrix.

## FixedVector
```c++
FixedVector<dimensions> a();
```
Mostly same API, some slight differences.
### Constructor
Takes scalar rather than size.
```c++
FixedVector<dimensions> a(double scalar);
```

You can write Vector3 instead of FixedVector<3>;

You can write Vector2 instead of FixedVector<2>;


### Vector3

Also has some specialized methods.

```c++
FixedVector<3> a(double x, double y, double z); //faster constructor
Vector3 cross_product = a.crossProduct(b); //cross product(right-hand rule) 
```