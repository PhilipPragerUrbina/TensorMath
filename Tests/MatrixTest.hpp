//
// Created by Philip on 10/19/2022.
//

#ifndef TENSORMATH_MATRIXTEST_HPP
#define TENSORMATH_MATRIXTEST_HPP

#include "../TensorMath//Matrix.hpp"
#include "gtest/gtest.h"

//tests for vector class
using namespace TensorMath;

//todo finish tests
TEST(MatrixTest, matrix_mul){
    Matrix m(2,2);
    m[0][0]=1; m[1][0]=2;
    m[0][1]= 3;  m[1][1]= 4;



    Matrix m1(2,2);
    m1[0][0]=2; m1[1][0]=0;
    m1[0][1]= 1;  m1[1][1]= 2;
    //m * m1 ;
/*
 * [ 4.000000 4.000000 ]
[ 10.000000 8.000000 ]
 */
}


#endif //TENSORMATH_MATRIXTEST_HPP
