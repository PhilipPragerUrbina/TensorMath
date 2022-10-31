//
// Created by Philip on 10/7/2022.
//

#ifndef TENSOR_MATRIX_HPP
#define TENSOR_MATRIX_HPP

#include "Vector.hpp"

namespace TensorMath {
    //matrix library for doubles
    //Contains assertions for things like mismatched vector sizes(Make sure define NDEBUG for max performance)
    class Matrix {
    public:
        //CONSTRUCTORS
            explicit Matrix(int w, int h) : m_width(w) , m_height(h){
                initialize();
            } //matrix of width and height, zero initialized
            explicit Matrix(int w): m_width(w) , m_height(w) {
                initialize();
            }   //square matrix
            Matrix(const Vector&vec){
                m_width = vec.getDim();
                m_height = 1;//flat
                initialize();
                for (int x = 0; x < m_width; ++x) {
                    setValue(x,0,vec[x]); //copy over
                }
            } //create flat matrix from vector(for conversions)
            Matrix(const Matrix &other) : Matrix(other.m_width, other.m_height){
                for (int y = 0; y < m_height; ++y) {
                    for (int x = 0; x < m_width; ++x) {
                        setValue(x,y,other.getValue(x,y));
                    }
                }
            }   //copy constructor
            ~Matrix(){
                for (int i = 0; i < m_width; ++i) {
                    delete m_data[i]; //clean up vectors
                }
                delete[] m_data;
            }   //destructor for clean up

        //SETTERS AND GETTERS
            double getValue(int x, int y) const{
                assert(x < m_width && y < m_height);//check if in bounds
                return m_data[x]->getValue(y);
            }//get a double value at coordinates
            void setValue(int x, int y, double value) {
                assert(x < m_width && y < m_height);//check if in bounds
                (*(m_data[x]))[y] = value;
            } //set a double value at coordinates
            void setZero(){
                for (int y = 0; y < m_height; ++y) {
                    for (int x = 0; x < m_width; ++x) {
                        setValue(x,y,0);
                    }
                }
            }  //create a null matrix, all zero values
            void setIdentity(){
                for (int y = 0; y < m_height; ++y) {
                    for (int x = 0; x < m_width; ++x) {
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
                for (int y = 0; y < m_height; ++y) { //go one row at a time
                    for (int x = 0; x < m_width; ++x) { //fill in values left to right
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
                for (int y = 0; y < m_height; ++y) {
                    for (int x = 0; x < m_width; ++x) {
                        output.push_back(getValue(x,y));
                    }
                }
                return output;
            }   //get array, inverse of fill array. Useful for serialization.
            Vector getColumn(int x)const{
                assert(x < m_width); //check bounds
                return *m_data[x];
            }    //get a vector from matrix
            Vector getRow(int y)const{
                assert(y < m_height); //check bounds
                Vector out (m_width); //new vector since data is stored in other ordination
                for (int x = 0; x < m_width; ++x) {
                    out[x] = getValue(x, y); //fill vector
                }
                return out;
            }   //get a vector of the row rather than column
            int getHeight() const {return m_height;} //get matrix height(# of rows)
            int getWidth() const {return m_width;} //get matrix width
            Matrix &operator=(const Matrix &other) { //assign from other Matrix
                if (this != &other) {//handle self assignment
                    assert(other.m_width == m_width); //can not assign different dimensional matrix
                    for (int i = 0; i < m_width; ++i) {
                        *m_data[i] = other[i];
                    }
                }
                return *this;
            }

       //COMPARISON
            bool equals(const Matrix& other, double epsilon  = std::numeric_limits<double>::epsilon()*10) const {
                if(m_width != other.getWidth() || m_height != other.getHeight()){
                    return false; //different dimensions
                }
                for (int x = 0; x < m_width; ++x) {
                    if(!other[x].equals(getColumn(x), epsilon)){ //compare vectors
                        return false;
                    };
                }
                return true;
            } //compare two matrices based on an epsilon for floating point values

        //OPERATORS
            //allows matrix[x][y] to work, returns a vector
            Vector operator[](int x) const {  assert(x < m_width); //check if in bounds
                return *m_data[x]; } //get vector using brackets
            Vector &operator[](int x) {  assert(x < m_width); //check if in bounds
                return *m_data[x]; } //modify vector with brackets
            Matrix operator * (const Matrix& other) const {
                assert(m_width == other.m_height); //number of columns in a must be equal to # of rows in b
                Matrix out(other.getWidth(),m_height); //create new matrix to output
                for (int x = 0; x < out.m_width; ++x) {
                    for (int y = 0; y < out.m_height; ++y) {
                        Vector a = getRow(y);
                        Vector b = other[x];
                        out[x][y] = a.dotProduct(b); //set new matrix value to dot product of row and column
                    }
                }
                return out;
            }   //multiply two matrices todo optimize this https://coffeebeforearch.github.io/2020/06/23/mmul.html#:~:text=Matrix%20multiplication%20is%20an%20incredibly,multi%2Dcore%20CPU%20or%20GPU.
            Matrix operator + (const Matrix& other) const {
                assert(m_width == other.m_width && other.m_height == m_height); //must be same size
                Matrix out(m_width,m_height); //output matrix
                for (int x = 0; x < out.m_width; ++x) {
                    out[x] = getColumn(x) + other[x] ; //add the vectors
                }
                return out;
            }    //add two matrices
            Matrix operator - (const Matrix& other) const {
                assert(m_width == other.m_width && m_height == other.m_height); //must be same size
                Matrix out(m_width,m_height); //output matrix
                for (int x = 0; x < out.m_width; ++x) {
                    out[x] =  getColumn(x) - other[x]; //subtract the vectors
                }
                return out;
            }   //subtract two matrices
            bool operator == (const Matrix& other) const {
                return equals(other);
            } //equality operator
            bool operator != (const Matrix& other) const {
                return !equals(other);
            } //inequality operator
            operator Vector() const{
                return getRow(0); //return first row
            } //convert flat matrix to vector

       // UTILITIES
       void randomFill(double  min, double  max){
           for (int x = 0; x < m_width; ++x) {
               for (int y = 0; y < m_height; ++y) {
                   double random_value = min + ((double)rand() / RAND_MAX) * (max-min);
                   setValue(x,y,random_value);
               }
           }
        } //fill the matrix with random floating point values using rand() between two bounds
       //todo cuda array helper and cuda version, using and interoperating with cuda math
       Matrix resized(int w, int h) const{
            Matrix new_matrix(w,h); //create new matrix of size
           for (int x = 0; x < std::min(m_width, w); ++x) { //use the smallest size
               for (int y = 0; y < std::min(m_height, h); ++y) {
                   new_matrix[x][y] = getValue(x,y); //copy over data
               }
           }
           return new_matrix;
        } //get a smaller or bigger version of the matrix. New values are set to 0.
       //PRINTING
            std::string toString() const {
                std::string out = "";
                for (int y = 0; y < m_height; ++y) {
                    out +=  "[ ";
                    for (int x = 0; x < m_width; ++x) {
                        out += std::to_string(getValue(x,y)) + " ";
                    }
                    out += "]\n";
                }
                return out;
            } //make Matrix into string(contains newlines)
            friend auto operator<<(std::ostream &os, Matrix const &m) -> std::ostream & {return os << m.toString();} //standard output overload

    private:
        int m_width;   //dimensions
        int m_height;
        Vector **m_data;  //actual data(contained in multiple vector pointers) each column is a vector(top down)

        void initialize(){
            m_data = new Vector*[m_width];
            for (int i = 0; i < m_width; ++i) {
                m_data[i] = new Vector(m_height); //create vectors(columns)
                //vectors are 0 initialized by default
            }
        }  //initialize the matrix with vectors

    };

}
#endif TENSOR_MATRIX_HPP
