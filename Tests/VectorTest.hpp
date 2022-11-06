//
// Created by Philip on 10/12/2022.
//

#ifndef TENSOR_VECTORTEST_HPP
#define TENSOR_VECTORTEST_HPP
#include "../TensorMath//Vector.hpp"
#include "gtest/gtest.h"
//tests for vector class
using namespace TensorMath;

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
        Vector v {1,2,3};
        const Vector expected = {1,2,3};
        v[0] = v.getValue(0);
        v[1] = v[1];
        v.setValues({v.x(),v.y(),v.z()});
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
        //test negation
        Vector to_negate  = {-1,-1,-1};
        to_negate = -to_negate;
        EXPECT_TRUE(to_negate == expected) << "negation failed" << expected << test;
    }

    //test vector to vector operations
    TEST(VectorTest, vector_arithmatic){
        //the expected value is always the same, operations should undo each other
        const Vector expected = {1,2,3};
        //test operations using 3d vectors
        Vector a {1,2,3};
        Vector b {5.22,3.12,2.0};
        a += b;
        a -= b;
        a = a + b;
        a = a - b;
        EXPECT_TRUE(a == expected) << "vector addition failed" << expected << a;
        a *= b; //multiplication and division
        a /= b;
        a = a * b;
        a = a / b;
        EXPECT_TRUE(a == expected) << "vector multiplication failed" << expected << a;
    }

    //test additional functionality
    TEST(VectorTest, vector_utilities){
        //test vector length
        double length_value = Vector{5, 0}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);
        length_value = Vector{5, 0, 0, 0, 0, 0, 0}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);
        length_value = Vector{1, 1, 1, 1}.length();
        EXPECT_DOUBLE_EQ(length_value , 2.0);
        length_value = Vector{4, 3}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);

        //Test normalization
        Vector unit_vector = Vector{4,3}.normalized();
        Vector expected_unit_vector = Vector{4.0/5.0,3.0/5.0};
        EXPECT_TRUE(unit_vector == expected_unit_vector);

        //test getting dimensions
        EXPECT_EQ(unit_vector.getDim(), 2);

        //test dot product
        double dot_value = Vector{2,2}.dotProduct(Vector{1,1}); //simple
        EXPECT_DOUBLE_EQ(dot_value,4);
        dot_value = Vector{7,0,-2}.dotProduct(Vector{1,-1,4}); //complex
        EXPECT_DOUBLE_EQ(dot_value,-1);
        dot_value = Vector{0,0.1,0.2,0.3}.dotProduct(Vector{0.3,0.2,0.1,0}); //decimal
        EXPECT_DOUBLE_EQ(dot_value,0.04);

        //test distance
        double dist = Vector{0,0,0}.distance(Vector{0,0,0});
        EXPECT_DOUBLE_EQ(dist,0);
        dist = Vector{5,0}.distance(Vector{1,0});
        EXPECT_DOUBLE_EQ(dist,4);
        dist = Vector{3,2,0}.distance(Vector{-1,-1,0});
        EXPECT_DOUBLE_EQ(dist,5);


        //min and max
        Vector a = {50,-10,0,5};
        Vector b = {-40,30,0,10};
        Vector min_expected{-40,-10,0,5};
        Vector max_expected{50,30,0,10};
        EXPECT_TRUE(a.min(b) == min_expected);
        EXPECT_TRUE(b.min(a) == min_expected); //should be interchangeable
        EXPECT_TRUE(a.max(b) == max_expected);
        EXPECT_TRUE(b.max(a) == max_expected);

        //test resizing vectors
        Vector big = {1,2,3};
        Vector small = {1,2};
        Vector bigger = {1,2,3,0};
        Vector small_offset = {2,3};
        EXPECT_TRUE(big.resized(0, 2) == small);
        EXPECT_TRUE(big.resized(0, 4) == bigger);
        EXPECT_TRUE(big.resized(1, 3) == small_offset);

        //abs
        Vector negative = {0,-1.5,-2};
        Vector positive = {0, 1.5,2};
        EXPECT_EQ(negative,positive);

        //reflection
        Vector direction = {2.0,1.0};
        Vector normal = {0.0,1.0};
        Vector reflected = {2.0,-1.0};
        EXPECT_EQ(direction.reflect(normal), reflected);
    }

#endif //TENSOR_VECTORTEST_HPP
