//
// Created by Philip on 10/12/2022.
//

#ifndef TENSOR_FVECTORTEST_HPP
#define TENSOR_FVECTORTEST_HPP
#include "../TensorMath/FixedVector.hpp"
#include "gtest/gtest.h"
//tests for constant size vector class
using namespace TensorMath;

    //Comparison test(Asserts since these are required for every other test):
    TEST(FixedVectorTest, comparison){
        FixedVector<3> a = {0,1,2};
        FixedVector<3> b = {0,1,2};
        ASSERT_TRUE(a==b) << "equals failed";
        a = {-0,1,2.0};
        ASSERT_TRUE(a==b)<< "equals failed";
        a = {0.0,1.001,1.99};
        ASSERT_TRUE(a != b)<< "not equals failed";
        a = {3.5,3.5,3.5};
        EXPECT_TRUE(a == 3.5) << "scalar equals failed";
    }

    //tests for creating vectors and assigning them
    TEST(FixedVectorTest, general_operations){
        //test vector zero initialization
        FixedVector<4> empty(0);
        FixedVector<4> empty_2 = {0,0,0,0};
        EXPECT_TRUE(empty == empty_2) << "Zero initialization failed" << empty << empty_2;
        //test lists
        FixedVector<3> list_init = {1,2,3};
        FixedVector<3> list_init_2 = FixedVector<3>{1,2,3};
        FixedVector<3> list_assign = FixedVector<3>(3);
        list_assign = {1,2,3};
        EXPECT_TRUE(list_init == list_init_2  && list_init == list_assign) << "List initialization failed" << list_init << list_init_2 << list_assign;
        //test assign
        FixedVector<3> a = {2,3,4};
        FixedVector<3> b = {1,2,3};
        b = a;
        EXPECT_TRUE(a == b) << "Assign failed" << a << b;
        //test scalar assign
        FixedVector<3> scalar_vec (3);
        scalar_vec = 3;
        FixedVector<3> vec {3,3,3};
        EXPECT_TRUE(scalar_vec == vec) << "Scalar Assign failed" << scalar_vec << vec;
        //test copy constructor
        FixedVector<3> copy = list_init;
        EXPECT_TRUE(copy == list_init) << "Copy  failed" << list_init << copy;
    }

    //tests for assigning values
    TEST(FixedVectorTest, value_changes){
        FixedVector<3> v {1,2,3};
        const FixedVector<3> expected = {1,2,3};
        v[0] = v.getValue(0);
        v[1] = v[1];
        v.setValues({v.x(),v.y(),v.z()});
        EXPECT_TRUE(v == expected) << "value changes failed" << v << expected;
    }

    //tests for operations involving vector and a scalar
    TEST(FixedVectorTest, scalar_arithmatic){
        //the expected value is always the same, operations should undo each other
        const FixedVector<3> expected = {1,1,1};
        //test operations using 3d vector
        FixedVector<3> test {1,1,1};
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
        FixedVector<3> to_negate  = {-1,-1,-1};
        to_negate = -to_negate;
        EXPECT_TRUE(to_negate == expected) << "negation failed" << expected << test;
    }

    //test vector to vector operations
    TEST(FixedVectorTest, vector_arithmatic){
        //the expected value is always the same, operations should undo each other
        const FixedVector<3> expected = {1,2,3};
        //test operations using 3d vectors
        FixedVector<3> a {1,2,3};
        FixedVector<3> b {5.22,3.12,2.0};
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
    TEST(FixedVectorTest, vector_utilities){
        //test vector length
        double length_value = FixedVector<2>{5, 0}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);
        length_value = FixedVector<7>{5, 0, 0, 0, 0, 0, 0}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);
        length_value = FixedVector<4>{1, 1, 1, 1}.length();
        EXPECT_DOUBLE_EQ(length_value , 2.0);
        length_value = FixedVector<2>{4, 3}.length();
        EXPECT_DOUBLE_EQ(length_value , 5.0);

        //Test normalization
        FixedVector<2> unit_vector = FixedVector<2>{4,3}.normalized();
        FixedVector<2> expected_unit_vector = FixedVector<2>{4.0/5.0,3.0/5.0};
        EXPECT_TRUE(unit_vector == expected_unit_vector);

        //test getting dimensions
        EXPECT_EQ(unit_vector.getDim(), 2);

        //test dot product
        double dot_value = FixedVector<2>{2,2}.dotProduct(FixedVector<2>{1,1}); //simple
        EXPECT_DOUBLE_EQ(dot_value,4);
        dot_value = FixedVector<3>{7,0,-2}.dotProduct(FixedVector<3>{1,-1,4}); //complex
        EXPECT_DOUBLE_EQ(dot_value,-1);
        dot_value = FixedVector<4>{0,0.1,0.2,0.3}.dotProduct(FixedVector<4>{0.3,0.2,0.1,0}); //decimal
        EXPECT_DOUBLE_EQ(dot_value,0.04);

        //test distance
        double dist = FixedVector<3>{0,0,0}.distance(FixedVector<3>{0,0,0});
        EXPECT_DOUBLE_EQ(dist,0);
        dist = FixedVector<2>{5,0}.distance(FixedVector<2>{1,0});
        EXPECT_DOUBLE_EQ(dist,4);
        dist = FixedVector<3>{3,2,0}.distance(FixedVector<3>{-1,-1,0});
        EXPECT_DOUBLE_EQ(dist,5);


        //min and max
        FixedVector<4> a = {50,-10,0,5};
        FixedVector<4> b = {-40,30,0,10};
        FixedVector<4> min_expected{-40,-10,0,5};
        FixedVector<4> max_expected{50,30,0,10};
        EXPECT_TRUE(a.min(b) == min_expected);
        EXPECT_TRUE(b.min(a) == min_expected); //should be interchangeable
        EXPECT_TRUE(a.max(b) == max_expected);
        EXPECT_TRUE(b.max(a) == max_expected);

        //abs
        FixedVector<3> negative = {0,-1.5,-2};
        FixedVector<3> positive = {0, 1.5,2};
        EXPECT_EQ(negative,positive);

        //cross product
        Vector3 forward = {1,0,0};
        Vector3 up = {0,0,1};
        Vector3 side = {0,1,0};
        EXPECT_EQ(up.crossProduct(forward),side);

        //reflection
        Vector2 direction = {2.0,1.0};
        Vector2 normal = {0.0,1.0};
        Vector2 reflected = {2.0,-1.0};
        EXPECT_EQ(direction.reflect(normal), reflected);

    }

#endif //TENSOR_FVECTORTEST_HPP
