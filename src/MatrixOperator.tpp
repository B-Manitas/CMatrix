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
Matrix<T> Matrix<T>::operatorMap(const std::function<T(T, T)> &f, const Matrix<T> &m) const
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

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) const
{
    if (dimH() != m.dimV())
        throw std::invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix.");

    Matrix<T> result(dimV(), m.dimH());

    for (size_t i = 0; i < dimV(); i++)
        for (size_t j = 0; j < m.dimH(); j++)
        {
            T sum{};

            for (size_t k = 0; k < dimH(); k++)
                sum += getCell(k, i) * m.getCell(j, k);

            result.setCell(j, i, sum);
        }

    return result;
}
// ==================================================
// OTHER OPERATORS

template <class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &m)
{
    out << "[";

    for (size_t i = 0; i < m.dimV(); i++)
    {
        out << "[";

        for (size_t j = 0; j < m.dimH(); j++)
        {
            out << m.getCell(j, i);

            if (j != m.dimH() - 1)
                out << ", ";
        }

        out << "]";

        if (i != m.dimV() - 1)
            out << ", ";
    }

    out << "]";

    return out;
}