/**
 * @defgroup operator CMatrixOperator
 * @file CMatrixOperator.tpp
 * @brief This file contains the implementation of operators.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_OPERATOR_TPP
#define CMATRIX_OPERATOR_TPP

// ==================================================
// ASSIGMENT OPERATOR

template <class T>
cmatrix<T> &cmatrix<T>::operator=(const cmatrix<T> &m)
{
    // Check if the matrix is the same
    // Prevents self-assignment
    if (this != &m)
        matrix = m.matrix;

    return *this;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator=(const std::initializer_list<std::initializer_list<T>> &m)
{
    cmatrix<T> tmp(m);
    *this = tmp;
    return *this;
}

// ==================================================
// COMPARISON OPERATORS

template <class T>
bool cmatrix<T>::operator==(const cmatrix<T> &m) const
{
    // Check if the dimensions are the same
    if (width() != m.width() or height() != m.height())
        return false;

    // For each cell, check if the values are the same
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (cell(i, j) != m.cell(i, j))
                return false;

    return true;
}

template <class T>
bool cmatrix<T>::operator!=(const cmatrix<T> &m) const
{
    return not(*this == m);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator==(const T &n) const
{
    return __map_op_comparaison_val(std::equal_to<T>(), n);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator!=(const T &n) const
{
    return __map_op_comparaison_val(std::not_equal_to<T>(), n);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator<(const T &n) const
{
    return __map_op_comparaison_val(std::less<T>(), n);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator<=(const T &n) const
{
    return __map_op_comparaison_val(std::less_equal<T>(), n);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator>(const T &n) const
{
    return __map_op_comparaison_val(std::greater<T>(), n);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::operator>=(const T &n) const
{
    return __map_op_comparaison_val(std::greater_equal<T>(), n);
}

// ==================================================
// ARITHMETIC OPERATORS

template <class T>
cmatrix<T> cmatrix<T>::operator+(const cmatrix<T> &m) const
{
    return __map_op_arithmetic(std::plus<T>(), m);
}

template <class T>
cmatrix<T> cmatrix<T>::operator+(const T &n) const
{
    return __map_op_arithmetic(std::plus<T>(), n);
}

template <class T>
cmatrix<T> operator+(const T &n, const cmatrix<T> &m)
{
    return m + n;
}

template <class T>
cmatrix<T> cmatrix<T>::operator-(const cmatrix<T> &m) const
{
    return __map_op_arithmetic(std::minus<T>(), m);
}

template <class T>
cmatrix<T> cmatrix<T>::operator-(const T &n) const
{
    return __map_op_arithmetic(std::minus<T>(), n);
}

template <class T>
cmatrix<T> operator-(const T &n, const cmatrix<T> &m)
{
    return (-1) * m + n;
}

template <class T>
cmatrix<T> operator-(const cmatrix<T> &m)
{
    return m * (-1);
}

template <class T>
cmatrix<T> cmatrix<T>::operator*(const cmatrix<T> &m) const
{
    return __map_op_arithmetic(std::multiplies<T>(), m);
}

template <class T>
cmatrix<T> cmatrix<T>::operator*(const T &n) const
{
    return __map_op_arithmetic(std::multiplies<T>(), n);
}

template <class T>
cmatrix<T> operator*(const T &n, const cmatrix<T> &m)
{
    return m * n;
}

template <class T>
cmatrix<T> cmatrix<T>::operator/(const T &n) const
{
    if (n == 0)
        throw std::invalid_argument("The value must be different from 0.");

    return __map_op_arithmetic(std::divides<T>(), n);
}

template <class T>
cmatrix<T> cmatrix<T>::operator^(const unsigned int &n) const
{
    return __map_op_arithmetic([&](const T &a, const unsigned int &b)
                               { return std::pow(a, b); },
                               n);
}

// ==================================================
// ARITHMETIC ASSIGNMENT OPERATORS

template <class T>
cmatrix<T> &cmatrix<T>::operator+=(const cmatrix<T> &m)
{
    return *this = *this + m;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator+=(const T &n)
{
    return *this = *this + n;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator-=(const cmatrix<T> &m)
{
    return *this = *this - m;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator-=(const T &n)
{
    return *this = *this - n;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator*=(const cmatrix<T> &m)
{
    return *this = *this * m;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator*=(const T &n)
{
    return *this = *this * n;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator/=(const T &n)
{
    return *this = *this / n;
}

template <class T>
cmatrix<T> &cmatrix<T>::operator^=(const unsigned int &n)
{
    return *this = *this ^ n;
}

// ==================================================
// OTHER OPERATORS

template <class T>
std::ostream &operator<<(std::ostream &out, const cmatrix<T> &m)
{
    out << "[";

    for (size_t i = 0; i < m.height(); i++)
    {
        out << "[";

        for (size_t j = 0; j < m.width(); j++)
        {
            out << m.cell(i, j);

            if (j != m.width() - 1)
                out << ", ";
        }

        out << "]";

        if (i != m.height() - 1)
            out << ", ";
    }

    out << "]";

    return out;
}

// ==================================================
// PRIVATE METHODS

template <class T>
cmatrix<T> cmatrix<T>::__map_op_arithmetic(const std::function<T(T, T)> &f, const cmatrix<T> &m) const
{
    __check_size(m);

    // Initialize a matrix with the same dimensions of the current matrix
    cmatrix<T> result = copy();

    // Apply the operator to each cell of the matrix
    #pragma omp parallel for collapse(2)
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            result.set_cell(r, c, f(cell(r, c), m.cell(r, c)));

    return result;
}

template <class T>
cmatrix<T> cmatrix<T>::__map_op_arithmetic(const std::function<T(T, T)> &f, const T &val) const
{
    cmatrix<T> result = copy();

    #pragma omp parallel for collapse(2)
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            result.set_cell(i, j, f(cell(i, j), val));

    return result;
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::__map_op_comparaison_val(const std::function<T(T, T)> &f, const T &n) const
{
    // Initialize a matrix with the same dimensions of the current matrix
    cmatrix<short unsigned int> result(height(), width(), 0);

    // Check if the value of the cell is less than or equal to the value passed as parameter 'val'.
    result.apply([&](T _, size_t row, size_t col)
                 { return f(cell(row, col), n); });

    return result;
}

#endif // CMATRIX_OPERATOR_TPP
