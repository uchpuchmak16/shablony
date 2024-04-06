#include <iostream>

template <typename T>
int findSecondMaxIndex(T* arr, int size) {
    if (size < 2) {
        std::cerr << "Array size is less than 2\n";
        return -1;
    }

    int maxIndex = 0;
    int secondMaxIndex = -1;

    for (int i = 1; i < size; ++i) {
        if (arr[i] > arr[maxIndex]) {
            secondMaxIndex = maxIndex;
            maxIndex = i;
        }
        else if (secondMaxIndex == -1 || arr[i] > arr[secondMaxIndex]) {
            secondMaxIndex = i;
        }
    }

    return secondMaxIndex;
}

template <typename T>
class Matrix {
private:
    unsigned int m, n;
    T** data;

public:
    Matrix(unsigned int rows, unsigned int cols);
    ~Matrix();
    T* operator[](unsigned int index);
    void fillRandom();
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    Matrix operator+(const Matrix& other);
    Matrix operator*(const Matrix& other);
};

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
    data = new T * [m];
    for (unsigned int i = 0; i < m; ++i) {
        data[i] = new T[n];
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    for (unsigned int i = 0; i < m; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

template <typename T>
T* Matrix<T>::operator[](unsigned int index) {
    return data[index];
}

template <typename T>
void Matrix<T>::fillRandom() {
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            data[i][j] = static_cast<T>(rand() % 10);
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (unsigned int i = 0; i < matrix.m; ++i) {
        for (unsigned int j = 0; j < matrix.n; ++j) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    Matrix<T> result(m, n);
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < n; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    Matrix<T> result(m, other.n);
    for (unsigned int i = 0; i < m; ++i) {
        for (unsigned int j = 0; j < other.n; ++j) {
            result.data[i][j] = 0;
            for (unsigned int k = 0; k < n; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}
