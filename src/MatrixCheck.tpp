/**
 * @file MatrixCheck.tpp
 * @brief This file contains the implementation of check methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// IS METHODS

template <class T>
bool Matrix<T>::is_empty() const
{
    return dim_h() == 0 and dim_v() == 0;
}

template <class T>
bool Matrix<T>::is_square() const
{
    return dim_h() == dim_v();
}

template <class T>
bool Matrix<T>::is_diag() const
{
    return is_square() and is_triangular_up() and is_triangular_low();
}

template <class T>
bool Matrix<T>::is_identity() const
{
    return identity(dim_h()) == *this;
}

template <class T>
bool Matrix<T>::is_symetric() const
{
    return *this == transpose();
}

template <class T>
bool Matrix<T>::is_triangular_up() const
{
    if (is_square())
    {
        // Check if the upper triangle is zero
        for (size_t r = 0; r < dim_v(); r++)
            for (size_t c = 0; c < dim_h(); c++)
                if (r > c and cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool Matrix<T>::is_triangular_low() const
{
    if (is_square())
    {
        // Check if the lower triangle is zero
        for (size_t r = 0; r < dim_v(); r++)
            for (size_t c = 0; c < dim_h(); c++)
                if (r < c and cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool Matrix<T>::all(const std::function<bool(T)> &f) const
{
    // Check if all elements satisfy the condition
    for (size_t r = 0; r < dim_v(); r++)
        for (size_t c = 0; c < dim_h(); c++)
            if (!f(cell(r, c)))
                return false;

    return true;
}

template <class T>
bool Matrix<T>::all(const T &val) const
{
    return all([&](T e)
                 { return e == val; });
}

template <class T>
bool Matrix<T>::any(const std::function<bool(T)> &f) const
{
    // Check if any element satisfies the condition
    for (size_t r = 0; r < dim_v(); r++)
        for (size_t c = 0; c < dim_h(); c++)
            if (f(cell(r, c)))
                return true;

    return false;
}

template <class T>
bool Matrix<T>::any(const T &val) const
{
    return any([&](T e)
                 { return e == val; });
}

// ==================================================
// THROW METHODS

template <class T>
void Matrix<T>::check_dim(const std::tuple<size_t, size_t> &dim) const
{
    if (std::get<0>(dim) != dim_v() || std::get<1>(dim) != dim_h())
        throw std::invalid_argument("The matrices must have the same dimension. Expected: " +
                                    std::to_string(dim_v()) +
                                    "x" +
                                    std::to_string(dim_h()) +
                                    ". Actual: " +
                                    std::to_string(std::get<0>(dim)) +
                                    "x" +
                                    std::to_string(std::get<1>(dim)));
}

template <class T>
void Matrix<T>::check_dim(const Matrix<T> &m) const
{
    check_dim(m.dim());
}

template <class T>
void Matrix<T>::check_valid_row(const std::vector<T> &row) const
{
    if (row.size() != dim_h())
        throw std::invalid_argument("Invalid row size. Expected: " +
                                    std::to_string(dim_h()) +
                                    ". Actual: " +
                                    std::to_string(row.size()));
}

template <class T>
void Matrix<T>::check_valid_col(const std::vector<T> &col) const
{
    if (col.size() != dim_v())
        throw std::invalid_argument("Invalid column size. Expected: " +
                                    std::to_string(dim_v()) +
                                    ". Actual: " +
                                    std::to_string(col.size()));
}

template <class T>
void Matrix<T>::check_valid_diag(const std::vector<T> &diag) const
{
    const size_t min = std::min(dim_h(), dim_v());
    if (diag.size() != min)
        throw std::invalid_argument("Invalid diagonal size. Expected: " +
                                    std::to_string(min) +
                                    ". Actual: " +
                                    std::to_string(diag.size()));
}

template <class T>
void Matrix<T>::check_valid_row_id(const size_t &n) const
{
    if (n < 0 || n >= dim_v())
        throw std::out_of_range("Invalid row index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(dim_v()));
}

template <class T>
void Matrix<T>::check_valid_col_id(const size_t &n) const
{
    if (n < 0 || n >= dim_h())
        throw std::out_of_range("Invalid column index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(dim_h()));
}

template <class T>
void Matrix<T>::check_expected_id(const size_t &n, const size_t &expectedBegin, const size_t &exepectedEnd) const
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
void Matrix<T>::check_expected_id(const size_t &n, const size_t &expected) const
{
    check_expected_id(n, expected, expected);
}

template <class T>
void Matrix<T>::check_valid_type() const
{
    if (std::is_same<T, bool>::value)
        throw std::invalid_argument("The type " + std::string(typeid(T).name()) + " is not supported.");
}