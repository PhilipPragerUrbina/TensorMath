//
// Created by Philip on 10/12/2022.
//

#ifndef TENSOR_VECTORTEST_HPP
#define TENSOR_VECTORTEST_HPP
#include "../TensorMath//Vector.hpp"
#include "gtest/gtest.h"

    using namespace TensorMath;
    //tests for vector class
    //Comparison test(Asserts since these are required for every other test):
    TEST(VectorTest, comparison){
        Vector a = {0,1,2};
        Vector b = {0,1,2};
        ASSERT_TRUE(a==b) << "equals failed";
        a = {-0,1,2.0};
        ASSERT_TRUE(a==b)<< "equals failed";
        a = {0.0,1.001,1.99};
        ASSERT_TRUE(a != b)<< "not equals failed";
        a = {3.5,3.5,3.5};
        EXPECT_TRUE(a == 3.5) << "scalar equals failed";
    }


    //tests for creating vectors and assigning them
    TEST(VectorTest, general_operations){
        //test vector zero initialization
        Vector empty(4);
        Vector empty_2 = {0,0,0,0};
        EXPECT_TRUE(empty == empty_2) << "Zero initialization failed" << empty << empty_2;
        //test lists
        Vector list_init = {1,2,3};
        Vector list_init_2 = Vector{1,2,3};
        Vector list_assign = Vector(3);
        list_assign = {1,2,3};
        EXPECT_TRUE(list_init == list_init_2  && list_init == list_assign) << "List initialization failed" << list_init << list_init_2 << list_assign;
        //test assign
        Vector a = {2,3,4};
        Vector b = {1,2,3};
        b = a;
        EXPECT_TRUE(a == b) << "Assign failed" << a << b;
        //test scalar assign
        Vector scalar_vec (3);
        scalar_vec = 3;
        Vector vec {3,3,3};
        EXPECT_TRUE(scalar_vec == vec) << "Scalar Assign failed" << scalar_vec << vec;
        //test copy constructor
        Vector copy = list_init;
        EXPECT_TRUE(copy == list_init) << "Copy  failed" << list_init << copy;
    }

    //tests for assigning values
    TEST(VectorTest, value_changes){
        //test value changes
        Vector v {1,2,3};
        const Vector expected = {1,2,3};
        v[0] = v.getValue(0);
        v[1] = v[1];
        v.setValues({v.x(),v[1],v[2]});
        EXPECT_TRUE(v == expected) << "value changes failed" << v << expected;
    }

    //tests for operations involving vector and a scalar
    TEST(VectorTest, scalar_arithmatic){
        //the expected value is always the same, operations should undo each other
        const Vector expected = {1,1,1};
        //test operations using 3d vector
        Vector test {1,1,1};
        test += 2; //addition and subtraction
        test -= 3;
        test = test + 3;
        test = test - 2;
        test -= -1;
        test += -1;
        EXPECT_TRUE(test == expected) << "scalar addition failed" << expected << test;
        test *= 2; //multiplication and division
        test /= 2;
        test = test * 4;
        test = test / 2;
        test *= 0.25;
        test /= 0.5;
        EXPECT_TRUE(test == expected) << "scalar multiplication failed" << expected << test;
    }

    //vector operations, vector utilities

#endif //TENSOR_VECTORTEST_HPP
