/**
 * @file MatrixConstructor.tpp
 * @brief This file contains the implementation of constructor methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// CONSTRUCTORS

template <class T>
Matrix<T>::Matrix()
{
    checkValidType();
}

template <class T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &m)
{
    checkValidType();

    if (isMatrix(m))
        for (auto &&row : m)
            matrix.push_back(std::vector<T>(row));

    else
        throw std::invalid_argument("The initializer list must be a matrix.");
}

template <class T>
Matrix<T>::Matrix(const size_t &dimV, const size_t &dimH)
{
    checkValidType();

    matrix = std::vector<std::vector<T>>(dimV, std::vector<T>(dimH));
}

template <class T>
Matrix<T>::Matrix(const size_t &dimV, const size_t &dimH, const T &value)
{
    checkValidType();

    matrix = std::vector<std::vector<T>>(dimV, std::vector<T>(dimH, value));
}

template <class T>
template <class U>
Matrix<T>::Matrix(const Matrix<U> &m)
{
    checkValidType();

    Matrix<T> result = m.template cast<T>();
    matrix = result.toVector();
}

// ==================================================
// DESTRUCTOR

template <class T>
Matrix<T>::~Matrix() {}