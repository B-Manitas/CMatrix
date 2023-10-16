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
    Matrix<T> m(dim_v(), dim_h());

    for (size_t r = 0; r < dim_v(); r++)
        for (size_t c = 0; c < dim_h(); c++)
            m.cell(r, c) = cell(r, c);

    return m;
}

template <class T>
void Matrix<T>::apply(const std::function<T(T, size_t *, size_t *)> &f, size_t *col, size_t *row)
{
    for (size_t r = 0; r < dim_v(); r++)
    {
        // If the user wants to know the row index
        if (row != nullptr)
            row = &r;

        for (size_t c = 0; c < dim_h(); c++)
        {
            // If the user wants to know the column index
            if (col != nullptr)
                col = &c;

            cell(r, c) = f(cell(r, c), col, row);
        }
    }
}

template <class T>
void Matrix<T>::apply(const std::function<T(T)> &f)
{
    apply([&](T cell, size_t *, size_t *)
          { return f(cell); });
}

template <class T>
Matrix<T> Matrix<T>::map(const std::function<T(T, size_t *, size_t *)> &f, size_t *col, size_t *row) const
{
    Matrix<T> m = copy();
    m.apply(f, col, row);
    return m;
}

template <class T>
Matrix<T> Matrix<T>::map(const std::function<T(T)> &f) const
{
    Matrix<T> m = copy();
    m.apply(f);
    return m;
}

template <class T>
void Matrix<T>::fill(const T &value)
{
    apply([&](T, size_t *, size_t *)
          { return value; });
}

template <class T>
std::vector<std::vector<T>> Matrix<T>::to_vector() const
{
    return matrix;
}

template <class T>
template <class U>
Matrix<U> Matrix<T>::cast() const
{
    if (std::is_convertible<T, U>::value)
    {
        Matrix<U> m(dim_v(), dim_h());

        // Set the casted value for each cell
        for (size_t r = 0; r < dim_v(); r++)
            for (size_t c = 0; c < dim_h(); c++)
                m.set_cell(c, r, static_cast<U>(cell(r, c)));

        return m;
    }

    else
        throw std::invalid_argument("T type" +
                                    std::string(typeid(T).name()) +
                                    " must be convertible into U type " +
                                    std::string(typeid(U).name()) + ".");
}
