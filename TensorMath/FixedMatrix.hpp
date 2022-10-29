//
// Created by Philip on 10/24/2022.
//

#ifndef TENSORMATH_FIXEDMATRIX_HPP
#define TENSORMATH_FIXEDMATRIX_HPP



#include "FixedVector.hpp"

namespace TensorMath {
    //matrix library for doubles, of constant size
    //Contains assertions for things like mismatched vector sizes(Make sure define NDEBUG for max performance)
    template< int width,  int height>class FixedMatrix {
    public:
        //CONSTRUCTORS
            FixedMatrix(){} //matrix of width and height, zero initialized
            FixedMatrix(const FixedMatrix<width,height> &other) {
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        setValue(x,y,other.getValue(x,y));
                    }
                }
            }   //copy constructor
            FixedMatrix(const FixedVector<width>&vec){
                    for (int x = 0; x < width; ++x) {
                        setValue(x,0,vec[x]); //copy over
                    }
            } //create flat matrix from vector(for conversions)
                //todo add TRS
        //SETTERS AND GETTERS
            double getValue(int x, int y) const{
                assert(x < width && y < height);//check if in bounds
                return m_data[x].getValue(y);
            }//get a double value at coordinates
            void setValue(int x, int y, double value) {
                assert(x < width && y < height);//check if in bounds
                m_data[x][y] = value;
            } //set a double value at coordinates
            void setZero(){
                for (int y = 0; y < width; ++y) {
                    for (int x = 0; x < height; ++x) {
                        setValue(x,y,0);
                    }
                }
            }  //create a null matrix, all zero values
            void setIdentity(){
                for (int y = 0; y < width; ++y) {
                    for (int x = 0; x < height; ++x) {
                        if(x == y){
                            setValue(x,y,1);
                        }else{
                            setValue(x,y,0);
                        }
                    }
                }
            }   //create an identity matrix, diagonal 1 values with others being zero
            void fillArray(std::vector<double> data){
                int counter = 0;
                for (int y = 0; y < height; ++y) { //go one row at a time
                    for (int x = 0; x < width; ++x) { //fill in values left to right
                        setValue(x,y,data[counter]);
                        counter++;
                        if(counter == data.size()){
                            return; //fill as much as possible, then stop
                        }
                    }
                }
            }      //fill the matrix from an array in standard left right then next row fashion
            std::vector<double> getArray(){
                std::vector<double> output;
                for (int y = 0; y < width; ++y) {
                    for (int x = 0; x < height; ++x) {
                        output.push_back(getValue(x,y));
                    }
                }
                return output;
            }   //get array, inverse of fill array. Useful for serialization.
            FixedVector<height> getColumn(int x)const{
                assert(x < width); //check bounds
                return m_data[x];
            }    //get a vector from matrix
            FixedVector<height> getRow(int y)const{
                assert(y < height); //check bounds
                FixedVector<width> out;
                for (int x = 0; x < width; ++x) {
                    out[x] = getValue(x, y); //fill vector
                }
                return out;
            }   //get a vector of the row rather than column
            static constexpr int getHeight()  {return height;} //get matrix height(# of rows)
            static constexpr int getWidth()  {return width;} //get matrix width
            void randomFill(double  min, double  max){
                for (int x = 0; x < width; ++x) {
                    for (int y = 0; y < height; ++y) {
                        double random_value = min + ((double)rand() / RAND_MAX) * (max-min);
                        setValue(x,y,random_value);
                    }
                }
            } //fill the matrix with random floating point values using rand() between two bounds

        //COMPARISON
            bool equals(const FixedMatrix& other, double epsilon = std::numeric_limits<double>::epsilon()*10) const {
                if(width != other.getWidth() || height != other.getHeight()){
                    return false; //different dimensions
                }
                for (int x = 0; x < width; ++x) {
                    if(!other[x].equals(getColumn(x), epsilon)){ //compare vectors
                        return false;
                    };
                }
                return true;
            } //compare two matrices based on an epsilon for floating point values

        //OPERATORS
        //allows matrix[x][y] to work, returns a vector
        FixedVector<height> operator[](int x) const {  assert(x < width); //check if in bounds
            return m_data[x]; } //get vector using brackets
        FixedVector<height> &operator[](int x) {  assert(x < width); //check if in bounds
            return m_data[x]; } //modify vector with brackets
        FixedMatrix operator * (const FixedMatrix<width, height>& other) const {
            FixedMatrix<other.getWidth(),height> out; //create new matrix to output
            for (int x = 0; x < out.getWidth(); ++x) {
                for (int y = 0; y < out.getHeight(); ++y) {
                    FixedVector a = getRow(y);
                    FixedVector b = other[x];
                    out[x][y] = a.dotProduct(b); //set new matrix value to dot product of row and column
                }
            }
            return out;
        }   //multiply two matrices, only same size for fixed matrices

        FixedVector<width> operator * (const FixedVector<height>& other) const {
            FixedVector<width> out;
            for (int x = 0; x < width; ++x) {
                    FixedVector b = getColumn(x);
                    out[x] = other.dotProduct(b); //set new matrix value to dot product of row and column
            }
            return out;
        }   //multiply with vector

        FixedMatrix<width,height> operator + (const FixedMatrix<width,height>& other) const {
            FixedMatrix<width,height> out; //output matrix
            for (int x = 0; x < width; ++x) {
                out[x] = getColumn(x) + other[x] ; //add the vectors
            }
            return out;
        }    //add two matrices
        FixedMatrix<width,height> operator - (const FixedMatrix<width,height>& other) const {
            FixedMatrix<width,height> out; //output matrix
            for (int x = 0; x < width; ++x) {
                out[x] =  getColumn(x) - other[x]; //subtract the vectors
            }
            return out;
        }   //subtract two matrices
        bool operator == (const FixedMatrix<width,height>& other) const {
            return equals(other);
        } //equality operator
        bool operator != (const FixedMatrix<width,height>& other) const {
            return !equals(other);
        } //inequality operator
        operator FixedVector<height>(){
            return getRow(0); //return first row
        } //convert flat matrix to vector

        //PRINTING
        std::string toString() const {
            std::string out = "";
            for (int y = 0; y < height; ++y) {
                out +=  "[ ";
                for (int x = 0; x < width; ++x) {
                    out += std::to_string(getValue(x,y)) + " ";
                }
                out += "]\n";
            }
            return out;
        } //make Matrix into string(contains newlines)
        friend auto operator<<(std::ostream &os, FixedMatrix<width,height> const &m) -> std::ostream & {return os << m.toString();} //standard output overload

    private:
        FixedVector<height> m_data[width];  //actual data
    };

}




#endif //TENSORMATH_FIXEDMATRIX_HPP
