/**
 * @defgroup operator CMatrixOperator
 * @file CMatrixOperator.tpp
 * @brief This file contains the implementation of operators.
 *
 * @see cmatrix
 */

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
    return cmatrix<T>(m);
}

// ==================================================
// COMPARISON OPERATORS

template <class T>
bool cmatrix<T>::operator==(const cmatrix<T> &m) const
{
    // Check if the dimensions are the same
    if (dim_h() != m.dim_h() or dim_v() != m.dim_v())
        return false;

    // For each cell, check if the values are the same
    for (size_t i = 0; i < dim_v(); i++)
        for (size_t j = 0; j < dim_h(); j++)
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
    return map([n](T value)
               { return value + n; });
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
    return map([n](T value)
               { return value - n; });
}

template <class T>
cmatrix<T> operator-(const T &n, const cmatrix<T> &m)
{
    return (-1)*m + n;
}

template <class T>
cmatrix<T> cmatrix<T>::operator*(const cmatrix<T> &m) const
{
    // Check if the number of columns of the first matrix
    // is equal to the number of rows of the second matrix
    if (dim_h() != m.dim_v())
        throw std::invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix. Expected: " +
                                    std::to_string(dim_h()) +
                                    ". Actual: " +
                                    std::to_string(m.dim_v()));

    // Create a new matrix with the same number of rows of the first matrix
    // and the same number of columns of the second matrix
    cmatrix<T> result(m.dim_h(), dim_v());

    // For each cell of the new matrix, calculate the sum of the products
    for (size_t i = 0; i < dim_v(); i++)
        for (size_t j = 0; j < m.dim_h(); j++)
        {
            T sum{};

            // For each cell of the first matrix, multiply the value of the cell
            // with the value of the corresponding cell of the second matrix
            for (size_t k = 0; k < dim_h(); k++)
                sum += cell(i, k) * m.cell(k, j);

            result.cell(i, j) = sum;
        }

    return result;
}

template <class T>
cmatrix<T> cmatrix<T>::operator*(const T &n) const
{
    return map([n](T value)
               { return value * n; });
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

    return map([n](T value)
               { return value / n; });
}

template <class T>
cmatrix<T> cmatrix<T>::operator^(const unsigned int &n) const
{
    // Check if the matrix is square
    if (not is_square())
        throw std::invalid_argument("The matrix must be square. Expected: " +
                                    std::to_string(dim_h()) +
                                    ". Actual: " +
                                    std::to_string(dim_v()));

    // If the exponent is 0, return the identity matrix
    if (n == 0)
        return cmatrix<T>::identity(dim_h());

    // If the exponent is 1, return a copy of itself
    if (n == 1)
        return copy();

    // If the exponent is even, return the square of the matrix to the power of n / 2
    // Ex: A^2 = (A * A)^1
    if (n % 2 == 0)
        return (*this * *this) ^ (n / 2);

    // If the exponent is odd, return the square of the matrix to the power of (n - 1) / 2
    // Ex: A^3 = (A * A)^1 * A
    return *this * ((*this * *this) ^ ((n - 1) / 2));
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

    for (size_t i = 0; i < m.dim_v(); i++)
    {
        out << "[";

        for (size_t j = 0; j < m.dim_h(); j++)
        {
            out << m.cell(i, j);

            if (j != m.dim_h() - 1)
                out << ", ";
        }

        out << "]";

        if (i != m.dim_v() - 1)
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
    check_dim(m);

    // Initialize variables to store the coordinates of the current cell.
    size_t col = -1, row = -1;

    // Apply the operator to each cell of the matrix
    return map([&](T value, size_t *col, size_t *row)
               { return f(value, m.cell(*row, *col)); },
               &col, &row);
}

template <class T>
cmatrix<short unsigned int> cmatrix<T>::__map_op_comparaison_val(const std::function<T(T, T)> &f, const T &n) const
{
    // Initialize a matrix with the same dimensions of the current matrix
    cmatrix<short unsigned int> result(dim_v(), dim_h(), 0);

    // Initialize variables to store the coordinates of the current cell.
    // At the beginning, they are set to -1.
    size_t col = -1, row = -1;

    // Check if the value of the cell is less than or equal to the value passed as parameter 'val'.
    result.apply([&](T _, size_t *col, size_t *row)
                 { return f(cell(*row, *col), n); },
                 &col, &row);

    return result;
}
