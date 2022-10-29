# Vectors
Vectors are usually used to represent a direction or position in N dimensions.

### Warning
These vectors have their size defined at runtime, and therefore dynamically allocate memory in a pointer.
If you are looking for a constant sizes vectors, like Vector3, see _FixedVector_. FixedVector has compile time compatibility checks, and is easier copy(to a GPU for example) or serialize.


## Usage
### Include
```c++
//add the library
#include "TensorMath/Vector.hpp"
```

### Creating Vectors
```c++
//create a vector of 4 dimensions
Vector a(4);

//Create a 3d vector from an initialization list
Vector b = {2.0,1,-1};

//Create a vector from another vector(copy)
Vector c = a;
```

## Reference
### Constructors
