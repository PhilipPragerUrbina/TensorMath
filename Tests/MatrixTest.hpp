//
// Created by Philip on 10/19/2022.
//

#ifndef TENSORMATH_MATRIXTEST_HPP
#define TENSORMATH_MATRIXTEST_HPP

#include "../TensorMath//Matrix.hpp"
#include "gtest/gtest.h"

//tests for vector class
using namespace TensorMath;

TEST(MatrixTest, matrix_serialization){
    std::vector<double> data = {2.0,4.5,4.2,0}; //test data
    //create matrix
    Matrix a(2,2);
    a.fillArray(data); //fill with values
    EXPECT_EQ(data , a.getArray()); //test serialization

    //test deserialization
    EXPECT_DOUBLE_EQ(data[0], a[0][0]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[1], a[1][0]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[2], a[0][1]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[3], a[1][1]); //check each value for equality
}


TEST(MatrixTest, matrix_comparison){
    Matrix a(2,2); //first matrix
    a.fillArray({2.0,4.5,4.2,0});
    Matrix b(2,2); //should equal a
    b.fillArray({2,4.50,4.2,0});
    Matrix c(2,3); //different size
    c.fillArray({2,4.50,4.2,0,0,0.1,0.2});
    Matrix d(2,2); //different contents
    d.fillArray({2,4.10,4.1,0});

    ASSERT_TRUE(a == b); //a and b are the same
    ASSERT_FALSE(b == c); //different sizes
    ASSERT_TRUE(a != d); //a should not equal d

}

TEST(MatrixTest, matrix_add){
    //set up two 4x4 matrices
    Matrix a(2,2);
    a.fillArray({2.0,4.5,4.2,0});
    Matrix b(2,2);
    b.fillArray({2,4.10,4.1,0});
    //test addition
    Matrix expected(2,2);
    expected.fillArray({4,8.6,8.3,0});
    EXPECT_EQ(expected, a+b); //add two matrices
    //test subtraction
    expected.fillArray({0,0.4,0.1,0});
    EXPECT_EQ(expected ,(a-b)); //subtract two matrices
}

TEST(MatrixTest, matrix_utils){
    Vector vec{2,3,4,5};
    //matrix from vector
    Matrix from_vec(vec);
    Matrix not_from_vec(4,1);
    not_from_vec.fillArray({2,3,4,5});
    EXPECT_EQ(from_vec,not_from_vec);
    //matrix to vector
    EXPECT_EQ(vec,not_from_vec );
    //matrix identity
    Matrix identity(2,2);
    identity.setIdentity();
    Matrix expected_identity(2,2);
    expected_identity.fillArray({1,0,0,1});
    EXPECT_EQ(identity, expected_identity );
    //square matrix
    Matrix of_size(2);
    EXPECT_EQ(of_size.getWidth(),2);
    EXPECT_EQ(of_size.getHeight(),2);

}

TEST(MatrixTest, matrix_mul){
    //test cases taken from: https://www.mathsisfun.com/algebra/matrix-multiplying.html
    //two same size matrices
    Matrix a(2,2);
    a.fillArray({1,2,3,4});
    Matrix b(2,2);
    b.fillArray({2,0,1,2});
    Matrix a_times_b(2,2);
    a_times_b.fillArray({4,4,10,8}); //result
    EXPECT_EQ( a_times_b, a * b);

    //two different size matrices
    Matrix c(3,2);
    c.fillArray({1,2,3,4,5,6});
    Matrix d(2,3);
    d.fillArray({7,8,9,10,11,12});
    Matrix c_times_d(2,2);
    c_times_d.fillArray({58,64,139,154}); //result
    EXPECT_EQ( c_times_d , c * d);

    //vector by matrix
    Matrix from_vector(Vector{3,4,2});
    Matrix e(4,3);
    e.fillArray({13,9,7,15,8,7,4,6,6,4,0,3});
    Matrix vector_times_e(4,1);
    vector_times_e.fillArray({83,63,37,75});
    EXPECT_EQ( vector_times_e , from_vector * e);
}


#endif //TENSORMATH_MATRIXTEST_HPP
