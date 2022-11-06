//
// Created by Philip on 10/16/2022.
//

#ifndef TENSORMATH_FIXEDVECTOR_HPP
#define TENSORMATH_FIXEDVECTOR_HPP
#include "Vector.hpp"

namespace TensorMath {

    //Vector with constant size for easy serialization
    //Contains assertions for things like mismatched vector sizes(Make sure define NDEBUG for max performance)
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
            //todo optimize this, create specialized class for vec2, vec3
                std::vector<double> v(values);
                assert(v.size() == dimensions); //wrong amount
                for (int i = 0; i < dimensions; ++i) { m_data[i] = v[i]; }
            }   //{} initialization constructor
            FixedVector(double x, double y,double z){
                m_data[0] = x;
                m_data[1] = y;
                m_data[2] = z;

            } //3d vector optimized constructor
            //todo auto vectorization
            //todo finish docs
            //todo abs
            //todo opposite order add for doubles

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
            constexpr int getDim() const { return dimensions; } //get num dimensions
            //get by names
            double inline x() const { return getValue(0); }
            double inline y() const { return getValue(1); }
            double inline z() const { return getValue(2); }
            double inline w() const { return getValue(3); }

       //COMPARISON
            bool equalsScalar(const double &scalar, double epsilon = std::numeric_limits<double>::epsilon()*10) const {
                for (int i = 0; i < dimensions; ++i) { if (!doubleEquals(m_data[i], scalar, epsilon)) { return false; }}
                return true;
            } //compare to scalar value, using epsilon for reliability
            bool equals(const FixedVector &other, double epsilon = std::numeric_limits<double>::epsilon()*10) const {
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
            FixedVector<dimensions> inline operator+(const double &scalar) const { //adding
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] + scalar;
                }
                return out;
            }
            void inline operator+=(const double &scalar) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] + scalar;
                }
            }
            FixedVector<dimensions> inline operator-(const double &scalar) const { //subtracting
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] - scalar;
                }
                return out;
            }
            void inline operator-=(const double &scalar) {  //multiplying
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] - scalar;
                }
            }
            FixedVector<dimensions> inline operator*(const double &scalar) const {
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] * scalar;
                }
                return out;
            }
            void inline operator*=(const double &scalar) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] * scalar;
                }
            }
            FixedVector<dimensions> inline operator/(const double &scalar) const { //dividing
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] / scalar;
                }
                return out;
            }
            void inline operator/=(const double &scalar) {
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
            FixedVector<dimensions> inline operator+(const FixedVector<dimensions> &other) const { //adding
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] + other[i];
                }
                return out;
            }
            void inline operator+=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] + other[i];
                }
            }
            FixedVector<dimensions> inline operator-(const FixedVector<dimensions> &other) const { //subtracting
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] - other[i];
                }
                return out;
            }
            FixedVector<dimensions> inline operator-() const { //negating
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = -m_data[i];
                }
                return out;
             }
            void inline operator-=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] - other[i];
                }
            }
            FixedVector<dimensions> inline operator*(const FixedVector<dimensions> &other) const { //multiplying
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] * other[i];
                }
                return out;
            }
            void inline operator*=(const FixedVector<dimensions> &other) {
                for (int i = 0; i < dimensions; ++i) {
                    m_data[i] = m_data[i] * other[i];
                }
            }
            FixedVector<dimensions> inline operator/(const FixedVector<dimensions> &other) const { //dividing
                FixedVector<dimensions> out;
                for (int i = 0; i < dimensions; ++i) {
                    out[i] = m_data[i] / other[i];
                }
                return out;
            }
            void inline operator/=(const FixedVector<dimensions> &other) {
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
            //todo https://developer.nvidia.com/cuda-math-library cuda version

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
        FixedVector<3> crossProduct(const FixedVector<3> &other) const {
            return FixedVector<3>{getValue(1) * other[2] - getValue(2) * other[1],
                        getValue(2) * other[0] - getValue(0) * other[2],
                        getValue(0) * other[1] - getValue(1) * other[0]};
        } //Get the cross product of two vectors. Only for 3d vectors. (Right-hand rule)
        FixedVector<dimensions> reflect( FixedVector<dimensions> normal) const{
            return *this - normal * 2.0 * this->dotProduct(normal) / normal.dotProduct(normal) ;
        } //https://en.wikipedia.org/wiki/Reflection_(mathematics) , reflect a vector over a normal
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
        FixedVector<dimensions>  inverse() const {
            FixedVector<dimensions> one(1.0);
            return one / *this;
        } //get 1.0/vector. Useful for ray tracing.
        FixedVector<dimensions>  abs() const {
            FixedVector<dimensions> out;
            for (int i = 0; i < dimensions; ++i) {
                out[i] = std::abs(m_data[i]);
            }
            return out;
        } //absolute value
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
        inline static bool doubleEquals(double a, double b, double epsilon) {
            return (std::fabs(a - b) <= epsilon) || std::fabs(a - b) <= (epsilon * std::fmax(std::fabs(a), std::fabs(b)));
        } //helper function for comparing two floating point values: https://embeddeduse.com/2019/08/26/qt-compare-two-floats/

    };

    //helper names(easier typing for common uses)
    typedef FixedVector<3> Vector3;// 3d vector
    typedef FixedVector<2> Vector2;//2d vector


}
#endif //TENSORMATH_FIXEDVECTOR_HPP
