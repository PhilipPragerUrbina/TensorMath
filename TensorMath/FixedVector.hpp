//
// Created by Philip on 10/16/2022.
//

#ifndef TENSORMATH_FIXEDVECTOR_HPP
#define TENSORMATH_FIXEDVECTOR_HPP
#include "Vector.hpp"
//Vector with constant size for easy serialization
namespace TensorMath {
    template<int dimensions>
    class FixedVector {

    public:
        //CONSTRUCTORS
            FixedVector() {
                setZero();
            }   //create a new vector , zero initialized
            FixedVector(double scalar) {
                setScalar(scalar);
            }   //create a new vector , scalar initialized
            FixedVector(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) { m_data[i] = other[i]; }
            }  //copy constructor
            FixedVector(std::initializer_list<double> values) {
                std::vector<double> v(values);
                assert(v.size() == dimensions); //wrong amount
                for (int i = 0; i < v.size(); ++i) { m_data[i] = v[i]; }
            }   //{} initialization constructor

        //SETTER AND GETTERS
            void setValues(std::vector<double> values) {
                for (int i = 0; i < std::min(dimensions, (int) values.size()); ++i) {
                    m_data[i] = values[i];
                }
            } //set all or some values
            void setScalar(double scalar) { for (int i = 0; i < dimensions; ++i) { m_data[i] = scalar; }} //set to scalar value
            void setZero() { setScalar(0); }  //set all to zero
            double getValue(int i) const {
                assert(i < dimensions); //index out of vector range
                return m_data[i];
            } //get a value
            int getDim() const { return dimensions; } //get num dimensions
            //get by names
            double x() const { return getValue(0); }
            double y() const { return getValue(1); }
            double z() const { return getValue(2); }
            double w() const { return getValue(3); }

       //COMPARISON
            bool equalsScalar(const double &scalar, double epsilon = std::numeric_limits<double>::epsilon()* 10.0) const {
                for (int i = 0; i < dimensions; ++i) { if (!doubleEquals(m_data[i], scalar, epsilon)) { return false; }}
                return true;
            } //compare to scalar value, using epsilon for reliability
            bool equals(const FixedVector &other, double epsilon = std::numeric_limits<double>::epsilon()* 10.0) const {
                if (other.getDim() != dimensions) { return false; }//not same size
                for (int i = 0; i < dimensions; ++i) { if (!doubleEquals(m_data[i], other[i], epsilon)) { return false; }}
                return true;
            } //compare to other vector, using epsilon for reliability

        //OPERATORS
            //Getting and setting values
            double operator[](int i) const { return getValue(i); } //getting with brackets
            double &operator[](int i) {
                assert(i < dimensions); //index out of vector range
                return m_data[i];
            } //setting with brackets
            FixedVector<dimensions> &operator=(double scalar) {
                setScalar(scalar);
                return *this;
            }   //set to a scalar value with operator
            FixedVector<dimensions> &operator=(const FixedVector<dimensions> &other) { //assign from other vector
                if (this != &other) {//handle self assignment
                    for (int i = 0; i < dimensions; ++i) {
                        m_data[i] = other[i];
                    }
                }
                return *this;
            }   //set to a scalar value with operator
            FixedVector<dimensions> &operator=(std::initializer_list<double> values) {
                setValues(std::vector<double>(values));
                return *this;
            }   //set values from list with operator
            //Scalar operations
            FixedVector<dimensions> operator+(const double &scalar) const { //adding
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] + scalar;
                }
                return out;
            }
            void operator+=(const double &scalar) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] + scalar;
                }
            }
            FixedVector<dimensions> operator-(const double &scalar) const { //subtracting
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] - scalar;
                }
                return out;
            }
            void operator-=(const double &scalar) {  //multiplying
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] - scalar;
                }
            }
            FixedVector<dimensions> operator*(const double &scalar) const {
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] * scalar;
                }
                return out;
            }
            void operator*=(const double &scalar) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] * scalar;
                }
            }
            FixedVector<dimensions> operator/(const double &scalar) const { //dividing
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] / scalar;
                }
                return out;
            }
            void operator/=(const double &scalar) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] / scalar;
                }
            }
            bool operator==(const double &scalar) const {
                return equalsScalar(scalar);
            } //comparison
            bool operator!=(const double &scalar) const {
                return !equalsScalar(scalar);
            } //comparison
            //Vector operations
            FixedVector<dimensions> operator+(const FixedVector<dimensions> &other) const { //adding
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] + other[i];
                }
                return out;
            }
            void operator+=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] + other[i];
                }
            }
            FixedVector<dimensions> operator-(const FixedVector<dimensions> &other) const { //subtracting
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] - other[i];
                }
                return out;
            }
            FixedVector<dimensions> operator-() const { //negating
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = -m_data[i];
                }
                return out;
             }
            void operator-=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] - other[i];
                }
            }
            FixedVector<dimensions> operator*(const FixedVector<dimensions> &other) const { //multiplying
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] * other[i];
                }
                return out;
            }
            void operator*=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] * other[i];
                }
            }
            FixedVector<dimensions> operator/(const FixedVector<dimensions> &other) const { //dividing
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] / other[i];
                }
                return out;
            }
            void operator/=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] / other[i];
                }
            }
            bool operator==(const FixedVector<dimensions> &other) const { //comparison
                return equals(other);
            }
            bool operator!=(const FixedVector<dimensions> &other) const { //comparison
                return !equals(other);
            }

        //UTILITIES
        double length() const {
            double sum = 0; //sqrt(x^2 + y^2 ...) == ||v||
            for (int i = 0; i < dimensions; ++i) { sum += std::pow(m_data[i], 2.0); }
            return std::sqrt(sum);
        } //length of vector, the magnitude
        double dotProduct(const FixedVector<dimensions> &other) const {
            double sum = 0; //x1*x2 + y1*y2...
            for (int i = 0; i < dimensions; ++i) {
                sum += m_data[i] * other[i];
            }
            return sum;
        } //Get the dot product of two vectors. Combine two vectors into single value.
        double distance(const FixedVector<dimensions> &other) const {
            double sum = 0; //sqrt((x2-x1)^2 + (y2-y1)^2...)
            for (int i = 0; i < dimensions; ++i) {
                sum += std::pow(m_data[i] - other[i], 2.0);
            }
            return std::sqrt(sum);
        } //get the distance between two vectors.
        FixedVector<dimensions> normalized() const {
            return *this / length();  //(1/||v||) * v = unit v
        } //get the normalized(unit) vector. The direction of the vector.
        FixedVector<dimensions> min(const FixedVector<dimensions> &other) const {
            FixedVector<dimensions> out; //vector to return
            for (int i = 0; i < dimensions; ++i) {
                out[i] = std::fmin(m_data[i], other[i]);
            }
            return out;
        } //get a new vector with the minimum components from both other vectors(Very useful for bounding boxes)
        FixedVector<dimensions> max(const FixedVector<dimensions> &other) const {
            FixedVector<dimensions> out; //vector to return
            for (int i = 0; i < dimensions; ++i) {
                out[i] = std::max(m_data[i], other[i]);
            }
            return out;
        } //get a new vector with the maximum components from both other vectors(Very useful for bounding boxes)

        //PRINTING
        friend auto operator<<(std::ostream &os, FixedVector<dimensions> const &v) -> std::ostream & {
            return os << v.toString();
        } //standard output overload
        std::string toString() const {
            std::string out = "{";
            for (int i = 0; i < dimensions; ++i) { out += " " + std::to_string(m_data[i]); }
            return out + " }";
        }  //make vector into string

    private:
        double m_data[dimensions]; //actual data
        static bool doubleEquals(double a, double b, double epsilon) { //uses epsilon for reliable comparison
            return std::fabs(b - a) < epsilon;
        }  //helper function for comparison

    };

}
#endif //TENSORMATH_FIXEDVECTOR_HPP
