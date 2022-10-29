# Vectors
Vectors are usually used to represent a direction or position in N dimensions. Contains N amount fo double components.

### ⚠ Warning ⚠
> These vectors have their size defined at runtime, and therefore dynamically allocate memory in a pointer.
If you are looking for a constant sizes vectors, like Vector3, see _FixedVector_. FixedVector has compile time compatibility checks, and is easier copy(to a GPU for example) or serialize.

### ❗ Notice ❗
> This class contains assertions for things like mismatched vector sizes. Make sure define NDEBUG for max performance and to remove these assertions for your release build.

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
### Setting and Getting Vector values
```c++
//set a vector to a scalar(all components will be this value)
Vector a(4);
a = 2; // {2,2,2,2}

//set or get specific value
a[2] = 4.0 + a[1];

//set to other vector(must be same size)
Vector b = {2,3,4,5};
a = b;

//get a value by name
double x_val = a.x();
```
### Vector operations
```c++
//vectors must be same size for operations
Vector a = b + c / d * e;
a /= b * c;
//vectors also have scalar operations
a = b * 2.0;
a += 1.0;
```
### Comparison
```c++
//compare two vectors
if(a == b && a != c){
}
//compare vector to scalar
if(a == 2.0 && a != 1.0){
    //compares all components to the scalar
}
//both above use an epsilon value to reliably compare floating point values

const double epsilon = 0.0001;
if(a.equals(b,epsilon) || a.equalsScalar(2.0,epsilon)){
//use your own epsilon
};
```
### Using Utilities
```c++
double length = a.length();
Vector normal = a.normalized();
//There are a lot more utilities , check reference for details
```

### Printing
```c++
std::string vec_str = a.toString();
std::cout << a;
```

## Reference
### Constructors

<table>
<tr> <td> Example </td> <td> Syntax </td> <td> Description </td></tr>
<tr><td> 

```c++ 
Vector vec3(3); //{0,0,0}
```

</td><td>


```c++ 
explicit Vector(int dimensions)
```

</td>
<td>
Create a new vector of with a size of N dimensions. Asserts that dimensions > 0. Is zero initialized.
</td>
</tr>
<tr>
<td> 

```c++ 
Vector copy_of_other = other;
```

</td>
<td>

```c++ 
Vector(const Vector &other)
```

</td>
<td>
Create a new vector, with the same size and values of another vector. Does not contain any references to other vector.
</td>

</tr>
<tr>
<td> 

```c++ 
Vector vec{1,2,3,4};
Vector v = {1,2,3,4};
```

</td>
<td>

```c++ 
Vector(std::initializer_list<double> values)
```

</td>
<td>
Creates a new vector from an initializer list of doubles. Will be the size of the list.
</td>
</tr>
</table>

### Setters
Will loop through the list and set as many components as possible to the corresponding values. 

If values < dimensions, will keep remaining components

If values > dimensions, will ignore additional values
```c++ 
   void setValues(std::vector<double> values)
```

#### From a scalar
Will set all components of the vector to the scalar value.
```c++ 
   void setScalar(double scalar)
```
#### Null Vector
Will set all components of the vector to 0.
```c++ 
   void setZero()
```
#### operator []
Set a specific component by returning a reference to it. Asserts that i < dimensions.
```c++ 
   double &operator[](int i)
```
#### operator = scalar
Calls setScalar.
```c++ 
   Vector &operator=(double scalar)
```
#### operator = Vector
Asserts that vectors are the same size. Copies over values.
```c++ 
    Vector &operator=(const Vector &other)
```
### Getters
#### Get a specific component.
Will get the value of a specific component. Asserts that i < dimensions.
```c++ 
    double getValue(int i) const
```

#### Named Components
Calls getValue using a common name.
```c++ 
    double x() const { return getValue(0); }
    double y() const { return getValue(1); }
    double z() const { return getValue(2); }
    double w() const { return getValue(3); }
```
#### operator []
Calls getValue.
```c++ 
    double operator[](int i) const
```
#### get dimensions
Return the number of dimensions(components) the vector has.
```c++ 
    int getDim() const
```
### Comparison
> Note: The epsilon is used in the formula abs(a-b)<epsilon, to make sure double values are properly compared. std::numeric_limits<double>::epsilon()*10 was found to work for all tested operations.
> 
> More Info: https://embeddeduse.com/2019/08/26/qt-compare-two-floats/
#### Compare to scalar
Check if all components of the vector are equal to the scalar value,using an epsilon value for reliable floating point comparison.
```c++ 
    bool equals(const Vector &other, double epsilon = std::numeric_limits<double>::epsilon()*10)
```
#### Compare to Vector
Checks whether they have the same size. Then checks if all components are equal, using an epsilon value for reliable floating point comparison.
```c++ 
    bool equals(const Vector &other, double epsilon = std::numeric_limits<double>::epsilon()*10)
```
#### operator ==
Calls the above methods. Const.
#### operator != 
Calls the above methods, and returns !that. Const.

### Operations
#### Operator * + - / vector
All of these operators are the same, other than performing their corresponding operations. They perform the operations component-wise, using standard double operations. Asserts that both vectors are the same size.
```c++ 
    Vector operator/(const Vector &other) const
```
#### Operator *= /= +/ -= vector
All of these operators are the same, other than performing their corresponding operations. They perform the operations component-wise, using standard double operations, then assigns the value to the component of the left vector. Asserts that both vectors are the same size.
```c++ 
    void operator/=(const Vector &other)
```
#### Operator * + - / *= /= +/ -= scalar
Same as above methods, but uses scalar as second value in operations, rather than a vector value.
> Note: Dividing by 0, using max double value, etc. is undefined behavior. The library will behave as normal double operations do.

### Utilities
#### Length
Returns the length of the vector. This is the magnitude. 

$$\left\| a \right\|=\sqrt{x^2+y^2...}$$
```c++ 
    double length() const
```
#### Dot product
Asserts that vectors are same size. Combines two vectors into single double value.

$$a\bullet b=ax*bx+ay*by...$$
```c++ 
     double dotProduct(const Vector &other) const
```
#### Distance
Asserts that vectors are same size. Returns the distance between two points.

$$\left\| b-a \right\|$$
```c++ 
     double distance(const Vector &other) const
```
#### Inverse
Returns the reciprocal of a vector. Useful for ray intersections.

$$\frac{1}{a}$$
```c++ 
     Vector inverse() const 
```
#### Normalize
Returns the unit vector of a vector. A vector with a length of 1 and in the same direction as the original. Used for directions.

$$\frac{1}{\left\| a \right\|}*a$$
```c++ 
      Vector normalized() const
```

#### Minimum and maximum
Asserts that vectors are same size. Returns a new vector containing the smallest or largest components from either vector.

Great for creating bounding boxes.
```c++ 
      Vector min(const Vector &other) const
      Vector max(const Vector &other) const
```
#### Resize
Creates a new vector with size: end-start.
Copies value over, start inclusive, end not inclusive.
Extra values will be zero initialized.

```c++ 
       Vector resized(int start, int end) const
```
#### Reflect
Asserts that vectors are same size. Reflects a vector over a normal.

$$v-2*\frac{v\bullet n}{n\bullet n}*n$$
```c++ 
      Vector reflect(Vector normal) const
```

#### To String
Converts Vector to readable string. { x y z w... }
Also can be used with std::cout.
```c++ 
      std::string toString() const
      friend auto operator<<(std::ostream &os, Vector const &v) -> std::ostream &
```
