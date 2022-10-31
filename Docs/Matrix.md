# Matrices
Matrices are a 2d grid of values. They are composed of multiple vectors. 

### ⚠ Warning ⚠
> These Matrices have their size defined at runtime, and therefore dynamically allocate memory in a pointer.
If you are looking for a constant size Matrices, like Mat4, see _FixedMatrix_. Fixedmatrix has compile time compatibility checks, and is easier copy(to a GPU for example) or serialize.

### ❗ Notice ❗
> This class contains assertions for things like mismatched Matrix sizes. Make sure define NDEBUG for max performance and to remove these assertions for your release build.

## Usage
### Include
```c++
//add the library
#include "TensorMath/Matrix.hpp"
```

### Creating Matrices
```c++
//create a Matrix with a width of 4, and a height of 2. Zero initialized.
Matrix a(4,2);
//Create a Matrix from another matrix
Matrix b = a;
//Create a matrix from a vector
Matrix c(vec);
```
### Setting and Getting Matrix values
```c++
//get and setting double values
a.setValue(2,3,12.0); //set (2,3) to 12
a.getValue(2,3);
a[2][3] = 12;

//set to identity or null
a.setZero();
a.setIdentity();

//fill with array values from a std::vector
a.fillArray({2,3,4,5,1,2})
std::vector<double> arr = a.getArray();

//get a column from an x value
Vector c = a[0];
//get a row from a y value
Vector r = a.getRow(0);
```
### Matrix operations
```c++
//Matrix multiplication
Matrix m = a * b;
//Matrix addition and subtraction
Matrix l = a - b + c;
//Matrix times a vector
Vector transformed = Matrix(vec) * a;
```
### Comparison
```c++
//compare two Matrices
if(a == b && a != c){
}

const double epsilon = 0.0001;
if(a.equals(b,epsilon)){
//use your own epsilon
};
```
### Using Utilities
```c++
a.randomFill(-1,2.5); //fill a matrix with random values in a range
Matrix small = a.resize(3,2); //resize a matrix
```

### Printing
```c++
std::string mat_str = a.toString();
std::cout << a;
```

## Reference
### Constructors

<table>
<tr> <td> Example </td> <td> Syntax </td> <td> Description </td></tr>
<tr><td> 

```c++ 
Matrix m(2,3);
```

</td><td>


```c++ 
 explicit Matrix(int w, int h) 
```

</td>
<td>
Create a new matrix with a width and height.
</td>
</tr>
<tr>
<td> 

```c++ 
Matrix m(4);
```

</td>
<td>

```c++ 
  explicit Matrix(int w)
```

</td>
<td>
Create a square matrix.
</td>

</tr>
<tr>
<td> 

```c++ 
Matrix m(vec);
```

</td>
<td>

```c++ 
 Matrix(const Vector&vec)
```

</td>
<td>
Create a matrix with a height of 1 and a width corresponding to the vector. Copies vector values to matrix.
</td>
</tr>

<tr>
<td> 

```c++ 
Matrix m = b;
```

</td>
<td>

```c++ 
   Matrix(const Matrix &other)
```

</td>
<td>
Create a matrix from another matrix. Has same width and height, copies over values.
</td>
</tr>
</table>

### Setters
#### From list
Will loop through the std::vector and set as many components as possible to the corresponding values.

If values < w*h, will keep remaining components

If values > w*h, will ignore additional values

Fills from 0 to width for each row, one column at a time(0 to height).

$$\left [ 0,1,2,3,4,5,6,7,8 \right ] \rightarrow \begin{bmatrix}
0 & 1 & 2\\
3 & 4 & 5\\
6 & 7 & 8
\end{bmatrix}$$
```c++ 
   void setValues(std::vector<double> values)
```

#### Set a double value
Set a component at an x and y value to a double value.
Asserts that x and y are in bounds.
```c++ 
   void setValue(int x, int y, double value)
```
#### Null Matrix
Will set all components of the matrix to 0.

$$\begin{bmatrix}
0 & 0\\
0 & 0
\end{bmatrix}$$

```c++ 
   void setZero()
```

#### Identity Matrix
Will set all components of the matrix to 0. Then sets diagonal elements to 1.

$$\begin{bmatrix}
1 & 0\\
0 & 1
\end{bmatrix}$$
```c++ 
    void setIdentity()
```

#### operator []
Get a specific vector(column) from an x value. Asserts that x < width;
```c++ 
    Vector &operator[](int x)
```

#### operator = Matrix
Asserts that matrices are the same size. Copies over values by copying over the vectors.
```c++ 
    Matrix &operator=(const Matrix &other)
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
#### Get dimensions
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
