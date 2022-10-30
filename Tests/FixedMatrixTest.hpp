//
// Created by Philip on 10/19/2022.
//

#ifndef TENSORMATH_FMATRIXTEST_HPP
#define TENSORMATH_FMATRIXTEST_HPP


#include "gtest/gtest.h"
#include "../TensorMath/FixedMatrix.hpp"

//tests for vector class
using namespace TensorMath;

TEST(FixedMatrixTest, matrix_serialization){
    std::vector<double> data = {2.0,4.5,4.2,0}; //test data
    //create matrix
    FixedMatrix<2,2> a;
    a.fillArray(data); //fill with values
    EXPECT_EQ(data , a.getArray()); //test serialization

    //test deserialization
    EXPECT_DOUBLE_EQ(data[0], a[0][0]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[1], a[1][0]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[2], a[0][1]); //check each value for equality
    EXPECT_DOUBLE_EQ(data[3], a[1][1]); //check each value for equality
}


TEST(FixedMatrixTest, matrix_copy){
    FixedMatrix<2,2> a;
    a.fillArray({2,1,4,3});

    //test copy constructor
    FixedMatrix<2,2> b = a;
    EXPECT_EQ(a,b); //should have same values

    //test = operator
    b.fillArray({1,3,4,5});
    a = b;
    EXPECT_EQ(a,b); //should have same values
}

TEST(FixedMatrixTest, matrix_comparison){
    FixedMatrix<2,2> a; //first matrix
    a.fillArray({2.0,4.5,4.2,0});
    FixedMatrix<2,2> b; //should equal a
    b.fillArray({2,4.50,4.2,0});
    FixedMatrix<2,2> d; //different contents
    d.fillArray({2,4.10,4.1,0});

    ASSERT_TRUE(a == b); //a and b are the same
    ASSERT_TRUE(a != d); //a should not equal d

}

TEST(FixedMatrixTest, matrix_add){
    //set up two 4x4 matrices
    FixedMatrix<2,2> a;
    a.fillArray({2.0,4.5,4.2,0});
    FixedMatrix<2,2> b;
    b.fillArray({2,4.10,4.1,0});
    //test addition
    FixedMatrix<2,2> expected;
    expected.fillArray({4,8.6,8.3,0});
    EXPECT_EQ(expected, a + b); //add two matrices
    //test subtraction
    expected.fillArray({0,0.4,0.1,0});
    EXPECT_EQ(expected ,(a-b)); //subtract two matrices
}

TEST(FixedMatrixTest, matrix_utils){
    FixedVector<4> vec{2,3,4,5};
    //matrix from vector
    FixedMatrix<4,1> from_vec(vec);
    FixedMatrix<4,1> not_from_vec;
    not_from_vec.fillArray({2,3,4,5});
    EXPECT_EQ(from_vec,not_from_vec);
    //matrix to vector
    EXPECT_EQ((FixedMatrix<4,1>(vec)),not_from_vec );
    //matrix identity
    FixedMatrix<2,2> identity;
    identity.setIdentity();
    FixedMatrix<2,2> expected_identity;
    expected_identity.fillArray({1,0,0,1});
    EXPECT_EQ(identity, expected_identity );
    //square matrix
    FixedMatrix<2,2> of_size;
    EXPECT_EQ(of_size.getWidth(),2);
    EXPECT_EQ(of_size.getHeight(),2);

}

TEST(FixedMatrixTest, matrix_mul){
    //test cases taken from: https://www.mathsisfun.com/algebra/matrix-multiplying.html
    //two same size matrices
    FixedMatrix<2,2> a;
    a.fillArray({1,2,3,4});
    FixedMatrix<2,2> b;
    b.fillArray({2,0,1,2});
    FixedMatrix<2,2> a_times_b;
    a_times_b.fillArray({4,4,10,8}); //result
    EXPECT_EQ( a_times_b, a * b);


    //vector by matrix
    FixedVector<3> vec{3,4,2};
    FixedMatrix<4,3> e;
    e.fillArray({13,9,7,15,8,7,4,6,6,4,0,3});
    FixedVector<4> vector_times_e{83,63,37,75};
    EXPECT_EQ( vector_times_e ,e * vec);
}


#endif //TENSORMATH_FMATRIXTEST_HPP
