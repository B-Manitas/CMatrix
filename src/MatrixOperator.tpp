/**
 * @file MatrixOperator.tpp
 * @brief This file contains the implementation of operator methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// ASSIGMENT OPERATOR

template <class T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &m)
{
    if (this != &m)
        matrix = m.matrix;

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>> &m)
{
    return Matrix<T>(m);
}

// ==================================================
// COMPARISON OPERATORS

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &m) const
{
    if (dimH() != m.dimH() or dimV() != m.dimV())
        return false;

    for (size_t i = 0; i < dimV(); i++)
        if (getRow(i) != m.getRow(i))
            return false;

    return true;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T> &m) const
{
    return not(*this == m);
}

// ==================================================
// ARITHMETIC OPERATORS

template <class T>
Matrix<T> Matrix<T>::operatorMap(std::function<T(T, T)> f, const Matrix<T> &m) const
{
    if (dim() != m.dim())
        throw std::invalid_argument("The matrices must have the same dimension.");

    size_t col = 0, row = 0;
    size_t *colPtr = &col, *rowPtr = &row;

    return map([&](T value, size_t *col, size_t *row)
               { return f(value, m.getCell(*col, *row)); },
               colPtr, rowPtr);
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const
{
    return operatorMap(std::plus<T>(), m);
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const
{
    return operatorMap(std::minus<T>(), m);
}