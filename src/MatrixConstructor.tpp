/**
 * @file MatrixConstructor.tpp
 * @brief This file contains the implementation of constructor methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// CONSTRUCTORS

template <class T>
Matrix<T>::Matrix() {}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> m)
{
    if (isMatrix(m))
        for (auto &&row : m)
            matrix.push_back(std::vector<T>(row));

    else
        throw std::invalid_argument("the argument is not a matrix");
}

// ==================================================
// DESTRUCTOR

template <class T>
Matrix<T>::~Matrix() {}