#include "Matrix.h"
#include <cmath>

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    delete[] m_data;
    m_length = other.m_length;
    m_width = other.m_width;
    m_data = new int[m_length * m_width];

    for (int i = 0; i < m_length * m_width; ++i) {
        m_data[i] = other.m_data[i];
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    if (matrix.m_width == 0) {
        return os;
    }

    for (int i = 0; i < matrix.m_length; ++i) {
        os << "|";
        for (int j = 0; j < matrix.m_width; ++j) {
            os << matrix.m_data[i * matrix.m_width + j] << "|";
        }
        os << "\n";
    }
    return os;
}

Matrix operator+(const Matrix& A, const Matrix& B) {
    Matrix result(A);
    result += B;
    return result;
}

Matrix operator-(const Matrix& A, const Matrix& B) {
    Matrix result(A);
    result -= B;
    return result;
}

Matrix operator*(int scalar, const Matrix& A) {
    Matrix result(A);
    result *= scalar;
    return result;
}

Matrix operator*(const Matrix& A, int scalar) {
    return scalar * A;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    check_sizes(other);
    for (int i = 0; i < m_length; ++i) {
        for (int j = 0; j < m_width; ++j) {
            (*this)(i, j) += other(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    check_sizes(other);
    for (int i = 0; i < m_length; ++i) {
        for (int j = 0; j < m_width; ++j) {
            (*this)(i, j) -= other(i, j);
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if (m_width != other.m_length) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(m_length, other.m_width);
    for (int i = 0; i < m_length; i++) {
        for (int j = 0; j < other.m_width; j++) {
            for (int k = 0; k < m_width; k++) {
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    *this = result;
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(*this);
    for (int i = 0; i < m_length; ++i) {
        for (int j = 0; j < m_width; ++j) {
            result(i, j) = -(*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(*this);
    result *= other;
    return result;
}

Matrix& Matrix::operator*=(int scalar) {
    for (int i = 0; i < m_length; ++i) {
        for (int j = 0; j < m_width; ++j) {
            (*this)(i, j) *= scalar;
        }
    }
    return *this;
}

bool Matrix::operator!=(const Matrix& other) const {
    if (this->m_length != other.m_length || this->m_width != other.m_width) {
        return true;
    }
    for (int i = 0; i < this->m_length; i++) {
        for (int j = 0; j < this->m_width; j++) {
            if ((*this)(i, j) != other(i, j)) {
                return true;
            }
        }
    }
    return false;
}

bool Matrix::operator==(const Matrix& other) const {
    return !((*this) != other);
}

Matrix Matrix::rotateClockwise() const {
    Matrix rotatedMatrix(m_width, m_length);
    for (int i = 0; i < m_length; i++) {
        for (int j = 0; j < m_width; j++) {
            rotatedMatrix(j, m_length - 1 - i) = (*this)(i, j);
        }
    }
    return rotatedMatrix;
}


Matrix Matrix::rotateCounterClockwise() const {
    return this->rotateClockwise().rotateClockwise().rotateClockwise();
}

Matrix Matrix::transpose() const {
    Matrix transposeMatrix(this->m_width, this->m_length);
    for (int i = 0; i < this->m_length; i++) {
        for (int j = 0; j < this->m_width; j++) {
            (transposeMatrix)(j, i) = (*this)(i, j);
        }
    }
    return transposeMatrix;
}

double Matrix::CalcFrobeniusNorm(const Matrix& m) {
    double sum = 0;
    for (int i = 0; i < m.m_length; i++) {
        for (int j = 0; j < m.m_width; j++) {
            sum += pow(m(i, j), 2);
        }
    }
    return sqrt(sum);
}

Matrix Matrix::makeSmallerMatrix(const Matrix& m, int col) {
    Matrix newMatrix(m.m_length - 1, m.m_width - 1);
    int curRow = 0;
    for (int i = 1; i < m.m_length; i++) {
        int curCol = 0;
        for (int j = 0; j < m.m_width; j++) {
            if (j == col) continue;
            newMatrix(curRow, curCol) = m(i, j);
            curCol++;
        }
        curRow++;
    }
    return newMatrix;
}

double Matrix::detAux(int n, const Matrix& m) {
    if (n == 1) return m(0, 0);
    if (n == 2) return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

    double det = 0;
    for (int i = 0; i < n; i++) {
        double subDet = detAux(n - 1, makeSmallerMatrix(m, i));
        det += (i % 2 == 0 ? 1 : -1) * m(0, i) * subDet;
    }
    return det;
}

double Matrix::CalcDeterminant(const Matrix& m) {
    if (m.m_length != m.m_width || m.m_length == 0 || m.m_width == 0) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    return detAux(m.m_width, m);
}
