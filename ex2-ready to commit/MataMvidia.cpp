#include "MataMvidia.h"

MataMvidia& MataMvidia::operator=(const MataMvidia& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < m_length; ++i) {
        delete m_frames[i];
    }
    delete[] m_frames;

    m_length = other.m_length;
    m_filmName = other.m_filmName;
    m_producerName = other.m_producerName;

    m_frames = new Matrix*[m_length];
    for (int i = 0; i < m_length; ++i) {
        m_frames[i] = new Matrix(*other.m_frames[i]);
    }

    return *this;
}

MataMvidia& MataMvidia::operator+=(const Matrix& other) {
    Matrix** newFrames = new Matrix*[m_length + 1];
    for (int i = 0; i < m_length; i++) {
        newFrames[i] = m_frames[i];
    }
    newFrames[m_length] = new Matrix(other);
    delete[] m_frames;
    m_frames = newFrames;
    m_length++;
    return *this;
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& other) {
    Matrix** newFrames = new Matrix*[m_length + other.m_length];
    for (int i = 0; i < m_length; i++) {
        newFrames[i] = m_frames[i];
    }
    for (int i = 0; i < other.m_length; i++) {
        newFrames[m_length + i] = new Matrix(*other.m_frames[i]);
    }
    delete[] m_frames;
    m_frames = newFrames;
    m_length += other.m_length;
    return *this;
}

MataMvidia operator+(const MataMvidia& A, const MataMvidia& B) {
    MataMvidia newMovie(A);
    newMovie += B;
    return newMovie;
}

std::ostream& operator<<(std::ostream& os, const MataMvidia& movie) {
    os << "Movie Name: " << movie.m_filmName << std::endl;
    os << "Author: " << movie.m_producerName << std::endl;

    for (int i = 0; i < movie.m_length; i++) {
        os << std::endl << "Frame " << i << ":" << std::endl;
        os << *movie.m_frames[i];
    }

    if (movie.m_length > 0) {
        os << std::endl;
    }

    os << "-----End of Movie-----" << std::endl;
    return os;
}
