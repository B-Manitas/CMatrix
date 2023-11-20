/**
 * @defgroup check CMatrixCheck
 * @file CMatrixCheck.tpp
 * @brief This file contains the implementation of methods to verify matrix conditions
 * and perform checks before operations to prevent errors.
 * @see cmatrix
 */

#ifndef CMATRIX_CHECK_TPP
#define CMATRIX_CHECK_TPP

// ==================================================
// IS METHODS

template <class T>
bool cmatrix<T>::is_empty() const
{
    return width() == 0 and height() == 0;
}

template <class T>
bool cmatrix<T>::is_square() const
{
    return width() == height();
}

template <class T>
bool cmatrix<T>::is_diag() const
{
    return is_square() and is_triangular_up() and is_triangular_low();
}

template <class T>
bool cmatrix<T>::is_identity() const
{
    return identity(width()) == *this;
}

template <class T>
bool cmatrix<T>::is_symetric() const
{
    return *this == transpose();
}

template <class T>
bool cmatrix<T>::is_triangular_up() const
{
    if (is_square())
    {
        // Check if the upper triangle is zero
        for (size_t r = 0; r < height(); r++)
            for (size_t c = 0; c < r; c++)
                if (cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool cmatrix<T>::is_triangular_low() const
{
    if (is_square())
    {
        // Check if the lower triangle is zero
        for (size_t r = 0; r < height(); r++)
            for (size_t c = r + 1; c < width(); c++)
                if (cell(r, c) != 0)
                    return false;

        return true;
    }

    return false;
}

template <class T>
bool cmatrix<T>::all(const std::function<bool(T)> &f) const
{
    // Check if all elements satisfy the condition
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            if (!f(cell(r, c)))
                return false;

    return true;
}

template <class T>
bool cmatrix<T>::all(const T &val) const
{
    return all([&](T e)
               { return e == val; });
}

template <class T>
bool cmatrix<T>::any(const std::function<bool(T)> &f) const
{
    // Check if any element satisfies the condition
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            if (f(cell(r, c)))
                return true;

    return false;
}

template <class T>
bool cmatrix<T>::any(const T &val) const
{
    return any([&](T e)
               { return e == val; });
}

// ==================================================
// THROW METHODS

template <class T>
void cmatrix<T>::__check_size(const std::tuple<size_t, size_t> &size) const
{
    if (std::get<0>(size) != height() || std::get<1>(size) != width())
        throw std::invalid_argument("The matrices must have the same dimension. Expected: " +
                                    std::to_string(height()) +
                                    "x" +
                                    std::to_string(width()) +
                                    ". Actual: " +
                                    std::to_string(std::get<0>(size)) +
                                    "x" +
                                    std::to_string(std::get<1>(size)));
}

template <class T>
void cmatrix<T>::__check_size(const cmatrix<T> &m) const
{
    __check_size(m.size());
}

template <class T>
void cmatrix<T>::__check_valid_row(const std::vector<T> &row) const
{
    if (row.size() != width())
        throw std::invalid_argument("Invalid row size. Expected: " +
                                    std::to_string(width()) +
                                    ". Actual: " +
                                    std::to_string(row.size()));
}

template <class T>
void cmatrix<T>::__check_valid_col(const std::vector<T> &col) const
{
    if (col.size() != height())
        throw std::invalid_argument("Invalid column size. Expected: " +
                                    std::to_string(height()) +
                                    ". Actual: " +
                                    std::to_string(col.size()));
}

template <class T>
void cmatrix<T>::__check_valid_diag(const std::vector<T> &diag) const
{
    const size_t min = std::min(width(), height());
    if (diag.size() != min)
        throw std::invalid_argument("Invalid diagonal size. Expected: " +
                                    std::to_string(min) +
                                    ". Actual: " +
                                    std::to_string(diag.size()));
}

template <class T>
void cmatrix<T>::__check_valid_row_id(const size_t &n) const
{
    if (n < 0 || n >= height())
        throw std::out_of_range("Invalid row index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(height()));
}

template <class T>
void cmatrix<T>::__check_valid_col_id(const size_t &n) const
{
    if (n < 0 || n >= width())
        throw std::out_of_range("Invalid column index. Expected: 0 <= " +
                                std::to_string(n) +
                                " < " +
                                std::to_string(width()));
}

template <class T>
void cmatrix<T>::__check_expected_id(const size_t &n, const size_t &expectedBegin, const size_t &exepectedEnd) const
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
void cmatrix<T>::__check_expected_id(const size_t &n, const size_t &expected) const
{
    __check_expected_id(n, expected, expected);
}

#endif // CMATRIX_CHECK_TPP
