#ifndef WET_MATAMVIDIA_H
#define WET_MATAMVIDIA_H
#include "Matrix.h"
using std::string;

class MataMvidia {
private:
    int m_length;
    Matrix** m_frames;
    string m_filmName;
    string m_producerName;

public:
    MataMvidia(const string& filmName, const string& producerName, Matrix* frames, int size) :
    m_length(size), m_frames(nullptr), m_filmName(filmName), m_producerName(producerName
    ) {
        m_frames = new Matrix*[m_length];
        for(int i = 0; i < m_length; i++){
            m_frames[i] = new Matrix(frames[i]);
        }
    }

    MataMvidia(const MataMvidia& other): m_length(other.m_length), m_frames(nullptr),
    m_filmName(other.m_filmName), m_producerName(other.m_producerName) {
        m_frames = new Matrix*[m_length];
        for (int i = 0; i < m_length; ++i) {
            m_frames[i] = new Matrix(*other.m_frames[i]);
        }
    }

    MataMvidia& operator=(const MataMvidia& other);

    Matrix& operator[](int frmaeNum){
        return *m_frames[frmaeNum];
    }

    const Matrix& operator[](int frmaeNum) const{
        return *m_frames[frmaeNum];
    }

    MataMvidia& operator+=(const MataMvidia& other);

    MataMvidia& operator+=(const Matrix& other);

    friend MataMvidia operator+(const MataMvidia& A, const MataMvidia& B);

    friend std::ostream& operator<<(std::ostream& os, const MataMvidia& movie);

    ~MataMvidia() {
        for (int i = 0; i < m_length; ++i) {
            delete m_frames[i];
        }
        delete[] m_frames;
    }


};

#endif