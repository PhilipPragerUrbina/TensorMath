# Matrices
Matrices are a 2d grid of values. They are composed of multiple vectors. 

### ⚠ Warning ⚠
> These Matrices have their size defined at runtime, and therefore dynamically allocate memory.
If you are looking for a constant size Matrices, like Mat4, see _FixedMatrix_. Fixedmatrix has compile time compatibility checks, and is easier copy(to a GPU for example) or serialize.

### ❗ Notice ❗
> This class contains assertions for mismatched Matrix sizes and out of bounds index. Make sure define NDEBUG for max performance and to remove these assertions for your release build.

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
Get a value at a coordinate. Asserts bounds.
```c++ 
    double getValue(int x, int y) const
```
#### Get a specific vector.
Gets one of the vector components. Gets vertical column based on x value. Assert bounds.
```c++ 
    Vector getColumn(int x)const
```
#### Get a specific row.
Gets one of the vector components. Gets horizontal row based on y value. Assert bounds. Slower than column.
```c++ 
    Vector getRow(int y)const
```

#### operator []
Calls getColumn.
```c++ 
    Vector operator[](int x) const
```
#### Get dimensions
Return the number of x and y double components
```c++ 
    int getHeight() const
    int getWidth() const
```
### Comparison
> Note: See vector comparison for more details on how comparison works,

#### Compare to Matrix
Checks whether they have the same size. Then compares all corresponding vector components.
```c++ 
    bool equals(const Matrix& other, double epsilon  = std::numeric_limits<double>::epsilon()*10) const
```
#### operator ==
Calls the above methods. 
#### operator !=
Calls the above methods, and returns !that.

### Operations
#### Operator + and -
Perform matrix addition and subtraction by adding or subtracting the corresponding vector components. Asserts matching size.
```c++ 
    Matrix operator + (const Matrix& other) const 
    Matrix operator - (const Matrix& other) const 
```
#### Operator *
Performs matrix multiplication, by taking dot products of the vector components. Asserts that a.width == b.height.
```c++ 
     Matrix operator * (const Matrix& other)
```
### Utilities

#### Resize
Creates a new Matrix with specified size
Copies values over, start inclusive, end not inclusive.
Extra values will be zero initialized.
```c++ 
       Matrix resized(int w, int h) const
```


#### To String
Converts Matrix to readable string. 

"[1 2 3]

[4 5 6]"


Also can be used with std::cout.
```c++ 
      std::string toString() const
      friend auto operator<<(std::ostream &os, Matrix const &m) -> std::ostream & {return os << m.toString();} 
```
