#ifndef WET_MATRIX_H
#define WET_MATRIX_H
#include <iostream>
#include "Utilities.h"

class Matrix{
private:
    int m_length;
    int m_width;
    int* m_data;

    //makes a matrix without the given coloumn and the first row
    static Matrix makeSmallerMatrix(const Matrix& m, int col);
    static double detAux(int n, const Matrix& m);
    void check_input(int row, int col) const {
        if(row < 0 || row >= m_length || col < 0 || col >= m_width || this->m_data == nullptr){
            exitWithError(MatamErrorType::OutOfBounds);
        }
    }
    void check_sizes(const Matrix& other){
        if(m_length != other.m_length || m_width != other.m_width){
            exitWithError(MatamErrorType::UnmatchedSizes) ;
        }
    }

public:
    //default constructor
    Matrix() : m_length(0), m_width(0), m_data(nullptr) {}

    Matrix(int length, int width, int value = 0) : m_length(length), m_width(width){
        m_data = new int[m_length*m_width];
        for(int i = 0; i < m_length*m_width ; i++){
            m_data[i] = value;
        }
    }
    //copy constructor
    Matrix(const Matrix& other) : m_length(other.m_length), m_width(other.m_width){
        m_data = new int[m_length*m_width];
        for(int i = 0; i < m_length*m_width ; i++){
            (*this).m_data[i] = other.m_data[i];
        }
    }

    ~Matrix() {
        delete[] m_data;
    }

    Matrix& operator=(const Matrix& other);
    int& operator()(int row, int col) {
        check_input(row, col);
        return m_data[row * m_width + col];
    }
    const int& operator()(int row, int col) const {
        check_input(row, col);
        return m_data[row * m_width + col];
    }
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    //operators: + - * matrices
    friend Matrix operator+(const Matrix& A, const Matrix& B);
    friend Matrix operator-(const Matrix& A, const Matrix& B);
    Matrix operator*(const Matrix& other) const;
    //operators: += -= *= matrices
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    //operator unary - : returns -A
    Matrix operator-() const;
    //operator * with scalar : n*A
    friend Matrix operator*(int scalar, const Matrix& A);
    //operator *= : A *= n
    Matrix& operator*=(int scalar);

    //operators: != / ==
    bool operator!=(const Matrix& other) const;
    bool operator==(const Matrix& other) const;

    //rotate clockWise / counterClockWise
    Matrix rotateClockwise() const;
    Matrix rotateCounterClockwise() const;

    //transpose
    Matrix transpose() const;

    //Frobenius
    static double CalcFrobeniusNorm(const Matrix& m);

    //Det
    static double CalcDeterminant(const Matrix& m);

};

Matrix operator*(const Matrix& A, int scalar);

#endif
