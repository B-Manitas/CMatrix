/**
 * @file MatrixCheck.tpp
 * @brief This file contains the implementation of check methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// IS METHODS

template <class T>
bool Matrix<T>::isEmpty() const
{
    return dimH() == 0 and dimV() == 0;
}

template <class T>
bool Matrix<T>::isSquare() const
{
    return dimH() == dimV();
}

template <class T>
bool Matrix<T>::isDiagonal() const
{
    return isSquare() and isUpperTriangular() and isLowerTriangular();
}

template <class T>
bool Matrix<T>::isIdentity() const
{
    return identity(dimH()) == *this;
}

template <class T>
bool Matrix<T>::isSymmetric() const
{
    return *this == transpose();
}

template <class T>
bool Matrix<T>::isUpperTriangular() const
{
    if (isSquare())
    {
        for (size_t r = 0; r < dimV(); r++)
            for (size_t c = 0; c < dimH(); c++)
                if (r > c and cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool Matrix<T>::isLowerTriangular() const
{
    if (isSquare())
    {
        for (size_t r = 0; r < dimV(); r++)
            for (size_t c = 0; c < dimH(); c++)
                if (r < c and cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool Matrix<T>::isAll(const std::function<bool(T)> &f) const
{
    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            if (!f(cell(r, c)))
                return false;

    return true;
}

template <class T>
bool Matrix<T>::isAll(const T &val) const
{
    return isAll([&](T e)
                 { return e == val; });
}

template <class T>
bool Matrix<T>::isAny(const std::function<bool(T)> &f) const
{
    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            if (f(cell(r, c)))
                return true;

    return false;
}

template <class T>
bool Matrix<T>::isAny(const T &val) const
{
    return isAny([&](T e)
                 { return e == val; });
}

// ==================================================
// THROW METHODS

template <class T>
void Matrix<T>::checkDim(const std::tuple<size_t, size_t> &dim) const
{
    if (std::get<0>(dim) != dimV() || std::get<1>(dim) != dimH())
        throw std::invalid_argument("The matrices must have the same dimension. Expected: " +
                                    std::to_string(dimV()) +
                                    "x" +
                                    std::to_string(dimH()) +
                                    ". Actual: " +
                                    std::to_string(std::get<0>(dim)) +
                                    "x" +
                                    std::to_string(std::get<1>(dim)));
}

template <class T>
void Matrix<T>::checkDim(const Matrix<T> &m) const
{
    checkDim(m.dim());
}

template <class T>
void Matrix<T>::checkValidRow(const std::vector<T> &row) const
{
    if (row.size() != dimH())
        throw std::invalid_argument("Invalid row size. Expected: " +
                                    std::to_string(dimH()) +
                                    ". Actual: " +
                                    std::to_string(row.size()));
}

template <class T>
void Matrix<T>::checkValidCol(const std::vector<T> &col) const
{
    if (col.size() != dimV())
        throw std::invalid_argument("Invalid column size. Expected: " +
                                    std::to_string(dimV()) +
                                    ". Actual: " +
                                    std::to_string(col.size()));
}

template <class T>
void Matrix<T>::checkValidDiag(const std::vector<T> &diag) const
{
    const size_t min = std::min(dimH(), dimV());
    if (diag.size() != min)
        throw std::invalid_argument("Invalid diagonal size. Expected: " +
                                    std::to_string(min) +
                                    ". Actual: " +
                                    std::to_string(diag.size()));
}

template <class T>
void Matrix<T>::checkIdRow(const size_t &n) const
{
    if (n < 0 || n >= dimV())
        throw std::out_of_range("Invalid row index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(dimV()));
}

template <class T>
void Matrix<T>::checkIdCol(const size_t &n) const
{
    if (n < 0 || n >= dimH())
        throw std::out_of_range("Invalid column index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(dimH()));
}

template <class T>
void Matrix<T>::checkIdExpected(const size_t &n, const size_t &expectedBegin, const size_t &exepectedEnd) const
{
    if (n < expectedBegin || n > exepectedEnd)
        throw std::out_of_range("Invalid index. Expected: " +
                                std::to_string(expectedBegin) +
                                " <= " +
                                std::to_string(n) +
                                " <= " +
                                std::to_string(exepectedEnd));
}

template <class T>
void Matrix<T>::checkIdExpected(const size_t &n, const size_t &expected) const
{
    checkIdExpected(n, expected, expected);
}