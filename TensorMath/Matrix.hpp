//
// Created by Philip on 10/7/2022.
//

#ifndef TENSOR_MATRIX_HPP
#define TENSOR_MATRIX_HPP

#include "Vector.hpp"

namespace TensorMath {
    //matrix library for doubles
    class Matrix {
    public:
//todo add TRS
        //CONSTRUCTORS
        //matrix of width and height, zero initialized
        Matrix(int w, int h) : m_width(w) , m_height(h){
            initialize();
        }
        //square matrix
        Matrix(int w): m_width(w) , m_height(w) {
            initialize();
        }
        //destructor for clean up
        ~Matrix(){
            for (int i = 0; i < m_width; ++i) {
                delete m_data[i]; //clean up vectors
            }
            delete[] m_data;
        }

        //SETTERS AND GETTERS
        double getValue(int x, int y) const{
            assert(x < m_width);//check if in bounds
            return m_data[x]->getValue(y);
        }
        void setValue(int x, int y, double value) {
            assert(x < m_width);//check if in bounds
            (*(m_data[x]))[y] = value;
        }
        //create a null matrix, all zero values
        void setZero(){
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    setValue(x,y,0);
                }
            }
        }
        //create an identity matrix, diagonal 1 values with others being zero
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
        }

        //fill the matrix from an array
        //in standard left right then next row fashion
        void fillArray(std::vector<double> data){
            int counter = 0;
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    setValue(x,y,data[counter]);
                    counter++;
                    if(counter == data.size()){
                        return; //fill as much as possible, then stop
                    }
                }
            }
        }
        //get array, inverse of fill array. Useful for serialization.
        std::vector<double> getArray(){
            std::vector<double> output;
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    output.push_back(getValue(x,y));
                }
            }
            return output;
        }

        //OPERATORS
        //allows matrix[x][y] to work
        Vector operator[](int x) const {  assert(x < m_width); //check if in bounds
            return *m_data[x]; } //get vector using brackets
        Vector &operator[](int x) {  assert(x < m_width); //check if in bounds
            return *m_data[x]; } //modify vector with brackets
            //todo multiplication and adding

            //todo define cuda, cuda array

        //PRINTING
        //make Matrix into string
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
        }
        friend auto operator<<(std::ostream &os, Matrix const &m) -> std::ostream & {return os << m.toString();} //standard output overload



    private:
        //dimensions
        int m_width;
        int m_height;
        Vector **m_data;   //actual data(contained in multiple vector pointers)
        //each column is a vector(top down)

        //initialize the matrix
        void initialize(){
            m_data = new Vector*[m_width];
            for (int i = 0; i < m_width; ++i) {
                m_data[i] = new Vector(m_height); //create vectors(columns)
                //vectors are 0 initialized by default
            }
        }


    };

}
#endif TENSOR_MATRIX_HPP
