#include <iostream>
#include "TensorMath//Matrix.hpp"
#include "TensorMath/Vector.hpp"
int main() {
    using namespace TensorMath;
  //  Matrix m(2,4);
    Vector v{6,2,3};
    Vector b{2,2,4};

    Matrix m(2,2);
    m[0][0]=2;
    m[1][0]=2;
  //  m[1].setZero();
    std::cout << m;

   // std::cout << v + b;

    return 0;
}
