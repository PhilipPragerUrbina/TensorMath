//
// Created by Philip on 10/11/2022.
//

#ifndef TENSOR_VECTOR_HPP
#define TENSOR_VECTOR_HPP

#include "assert.h"
#include <string>
#include <cstdarg>
#include <vector>
#include <iostream>
namespace TensorMath {

//n dimensional vector class for doubles
//Contains assertions for things like mismatched vector sizes(Make sure define NDEBUG for max performance)
class Vector {
    public:

        //CONSTRUCTORS
        //create a new vector of dimensions n, zero initialized
        Vector(int dimensions) {
            assert(dimensions > 0); //too small dimensions
            m_dimensions = dimensions;
            m_data = new double[dimensions];
            setZero();
        }
        //copy constructor
        Vector(const Vector &other) {
            m_dimensions = other.m_dimensions;
            m_data = new double[m_dimensions];
            for (int i = 0; i < m_dimensions; ++i) {m_data[i] = other[i];}
        }
        //{} initialization constructor
        Vector(std::initializer_list<double> values) {
            std::vector<double> v(values);
            m_dimensions = v.size();
            assert(m_dimensions > 0); //too small dimensions
            m_data = new double[m_dimensions];
            for (int i = 0; i < v.size(); ++i) {m_data[i] = v[i];}
        }
        //destructor
        ~Vector() {delete[] m_data;}


        //SETTER AND GETTERS
        //todo resize function
        //set all or some values
        void setValues(std::vector<double> values) {
            for (int i = 0; i < std::min(m_dimensions, (int) values.size()); ++i) {
                m_data[i] = values[i];
            }
        }
        //set to scalar value
        void setScalar(double scalar) {for (int i = 0; i < m_dimensions; ++i) {m_data[i] = scalar;}}
        //set all to zero
        void setZero() {setScalar(0);}
        //get a value
        double getValue(int i) const{
            assert(i < m_dimensions); //index out of vector range
            return m_data[i];}
        int getDim(){return m_dimensions;} //get num dimensions
        //get by names
        double x() const {return getValue(0);}
        double y() const {return getValue(1);}
        double z() const {return getValue(2);}
        double w() const {return getValue(3);}

        //COMPARISON
        bool equalsScalar(const double &scalar, double epsilon = std::numeric_limits<double>::epsilon()) const{
                for (int i = 0; i < m_dimensions; ++i) {if(!doubleEquals(m_data[i], scalar, epsilon)){return false;}}
                return true;
        } //compare to scalar value, using epsilon for reliability
        bool equals(const Vector &other, double epsilon = std::numeric_limits<double>::epsilon()) const{
            if(other.m_dimensions != m_dimensions){return false;}//not same size
            for (int i = 0; i < m_dimensions; ++i) {if(!doubleEquals(m_data[i], other[i], epsilon)){return false;}}
            return true;
        } //compare to other vector, using epsilon for reliability


        //OPERATORS
        //Getting and setting values
        double operator[](int i) const {return getValue(i);} //getting with brackets
        double &operator[](int i) {
            assert(i < m_dimensions); //index out of vector range
            return m_data[i];} //setting with brackets
        void operator=(double scalar) {setScalar(scalar);}   //set to a scalar value with operator
        void operator=(const Vector& other) { //assign from other vector
            assert(other.m_dimensions == m_dimensions); //can not assign different dimensional vector
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = other[i];
            }
        }   //set to a scalar value with operator
        void operator=(std::initializer_list<double> values) {setValues(std::vector<double>(values));}   //set values from list with operator

        //Scalar operations
        Vector operator+(const double &scalar) const { //adding
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] + scalar;
            }
            return out;
        }
        void operator+=(const double &scalar) {
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] + scalar;
            }
        }
        Vector operator - (const double &scalar) const { //subtracting
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] - scalar;
            }
            return out;
        }
        void operator-=(const double &scalar) {  //multiplying
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] - scalar;
            }
        }
        Vector operator *(const double &scalar) const {
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] * scalar;
            }
            return out;
        }
        void operator*=(const double &scalar) {
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] * scalar;
            }
        }
        Vector operator/(const double &scalar) const { //dividing
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] / scalar;
            }
            return out;
        }
        void operator/=(const double &scalar) {
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] / scalar;
            }
        }
        bool operator == (const double  &scalar) const{ //comparison
            return equalsScalar(scalar);
        }
        bool operator != (const double  &scalar) const{ //comparison
            return !equalsScalar(scalar);
        }


        //Vector operations
        Vector operator+(const Vector &other) const { //adding
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] + other[i];
            }
            return out;
        }
        void operator+=(const Vector &other) {
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] + other[i];
            }
        }
        Vector operator-(const Vector &other) const { //subtracting
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] - other[i];
            }
            return out;
        }
        void operator-=(const Vector &other) {
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] - other[i];
            }
        }
        Vector operator*(const Vector &other) const { //multiplying
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] * other[i];
            }
            return out;
        }
        void operator*=(const Vector &other) {
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] * other[i];
            }
        }
        Vector operator/(const Vector &other) const { //dividing
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions);
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = m_data[i] / other[i];
            }
            return out;
        }
        void operator/=(const Vector &other) {
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            for (int i = 0; i < m_dimensions; ++i) {
                m_data[i] = m_data[i] / other[i];
            }
        }
        bool operator==(const Vector &other) const { //comparison
            return equals(other);
        }
        bool operator!=(const Vector &other) const { //comparison
            return !equals(other);
        }


        //UTILITIES
        double length() const{
            double sum = 0; //sqrt(x^2 + y^2 ...) == ||v||
            for (int i = 0; i < m_dimensions; ++i) {sum += std::pow(m_data[i],2.0);}
            return std::sqrt(sum);
        } //length of vector, the magnitude
        double dotProduct(const Vector& other) const{
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            double sum = 0; //x1*x2 + y1*y2...
            for (int i = 0; i < m_dimensions; ++i) {
                sum += m_data[i] + other[i];
            }
            return sum;
        } //Get the dot product of two vectors. Combine two vectors into single value.
        Vector distance(const Vector& other) const{
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            double sum = 0; //sqrt((x2-x1)^2 + (y2-y1)^2...)
            for (int i = 0; i < m_dimensions; ++i) {
                sum += std::pow(m_data[i] - other[i],2.0);
            }
            return std::sqrt(sum);
        } //get the distance between two vectors.
        Vector normalized() const {
            return *this / length();  //(1/||v||) * v = unit v
        } //get the normalized(unit) vector. The direction of the vector.
        Vector min(const Vector& other) const{
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions); //vector to return
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = std::fmin(m_data[i], other[i]);
            }
            return out;
        } //get a new vector with the minimum components from both other vectors
        Vector max(const Vector& other) const{
            assert(other.m_dimensions == m_dimensions); //Not same size vectors
            Vector out(m_dimensions); //vector to return
            for (int i = 0; i < m_dimensions; ++i) {
                out[i] = std::max(m_data[i], other[i]);
            }
            return out;
        } //get a new vector with the maximum components from both other vectors


        //PRINTING
        operator std::string() const {return toString();}     //conversion into string
        friend auto operator<<(std::ostream &os, Vector const &v) -> std::ostream & {return os << v.toString();} //standard output overload
        //make vector into string
        std::string toString() const {
            std::string out = "{";
            for (int i = 0; i < m_dimensions; ++i) {out += " " + std::to_string(m_data[i]);}
            return out + " }";
        }


    private:

        int m_dimensions; //how many dimensions
        double *m_data; //actual data

        //helper function for comparison
        static bool doubleEquals(double a, double  b, double epsilon = std::numeric_limits<double>::epsilon() ) { //uses epsilon for reliable comparison
            return std::fabs(b - a) < epsilon;
        }

    };


}
#endif TENSOR_VECTOR_HPP
