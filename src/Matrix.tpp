/**
 * @file Matrix.tpp
 * @brief This file contains the implementation of global methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// GENERAL FUNCTIONS

template <class T>
void Matrix<T>::print() const
{
    std::cout << *this << std::endl;
}

template <class T>
void Matrix<T>::clear()
{
    matrix = std::vector<std::vector<T>>();
}

template <class T>
Matrix<T> Matrix<T>::copy() const
{
    Matrix<T> m(dimH(), dimV());

    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            m.setCell(c, r, cell(r, c));

    return m;
}

template <class T>
void Matrix<T>::apply(const std::function<T(T, size_t *, size_t *)> &f, size_t *col, size_t *row)
{
    for (size_t r = 0; r < dimV(); r++)
    {
        if (row != nullptr)
            row = &r;

        for (size_t c = 0; c < dimH(); c++)
        {
            if (col != nullptr)
                col = &c;

            setCell(c, r, f(cell(r, c), col, row));
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::map(const std::function<T(T, size_t *, size_t *)> &f, size_t *col, size_t *row) const
{
    Matrix<T> m = copy();
    m.apply(f, col, row);
    return m;
}

template <class T>
void Matrix<T>::fill(const T &value)
{
    apply([&](T, size_t *, size_t *) { return value; });
}
