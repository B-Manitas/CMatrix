/**
 * @defgroup math CMatrixMath
 * @file CMatrixMath.tpp
 * @brief This file contains the implementation of mathematical functions.
 *
 * @see cmatrix
 */

// ==================================================
// COMPARISON FUNCTIONS

template <class T>
bool cmatrix<T>::near(const cmatrix<T> &m, const T &tolerance) const
{
    // Check if the dimensions are the same
    if (width() != m.width() or height() != m.height())
        return false;

    // For each cell, check if the values are the same
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (not std::isgreaterequal(cell(i, j), m.cell(i, j) - tolerance) or
                not std::islessequal(cell(i, j), m.cell(i, j) + tolerance))
                return false;

    return true;
}

template <class T>
bool cmatrix<T>::near(const T &n, const T &tolerance) const
{
    // For each cell, check if the values are the same
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (not std::isgreaterequal(cell(i, j), n - tolerance) or
                not std::islessequal(cell(i, j), n + tolerance))
                return false;

    return true;
}

template <class T>
bool cmatrix<T>::nearq(const cmatrix<T> &m, const T &tolerance) const
{
    return not near(m, tolerance);
}

template <class T>
bool cmatrix<T>::nearq(const T &n, const T &tolerance) const
{
    return not near(n, tolerance);
}

// ==================================================
// MATHEMATICAL OPERATIONS

template <class T>
cmatrix<T> cmatrix<T>::matmul(const cmatrix<T> &m) const
{
    // Check if the number of columns of the first matrix
    // is equal to the number of rows of the second matrix
    if (width() != m.height())
        throw std::invalid_argument("The number of columns of the first matrix must be equal to the number of rows of the second matrix. Expected: " +
                                    std::to_string(width()) +
                                    ". Actual: " +
                                    std::to_string(m.height()));

    // Create a new matrix with the same number of rows of the first matrix
    // and the same number of columns of the second matrix
    cmatrix<T> result(height(), m.width());

    // For each cell of the new matrix, calculate the sum of the products
    #pragma omp parallel for collapse(2)
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < m.width(); j++)
        {
            T sum{};

            // For each cell of the first matrix, multiply the value of the cell
            // with the value of the corresponding cell of the second matrix
            #pragma omp parallel for reduction(+ : sum)
            for (size_t k = 0; k < width(); k++)
                sum += cell(i, k) * m.cell(k, j);

            result.cell(i, j) = sum;
        }

    return result;
}

template <class T>
cmatrix<T> cmatrix<T>::matpow(const unsigned int &n) const
{
    // Check if the matrix is square
    if (not is_square())
        throw std::invalid_argument("The matrix must be square. Expected: " +
                                    std::to_string(width()) +
                                    ". Actual: " +
                                    std::to_string(height()));

    // If the exponent is 0, return the identity matrix
    if (n == 0)
        return cmatrix<T>::identity(width());

    // If the exponent is 1, return a copy of itself
    if (n == 1)
        return copy();

    // If the exponent is even, return the square of the matrix to the power of n / 2
    // Ex: A^2 = (A * A)^1
    if (n % 2 == 0)
        return matmul(*this) ^ (n / 2);

    // If the exponent is odd, return the square of the matrix to the power of (n - 1) / 2
    // Ex: A^3 = (A * A)^1 * A
    return matmul(matmul(*this) ^ ((n - 1) / 2));
}

// ==================================================
// MATHEMATICAL FUNCTIONS

template <class T>
cmatrix<T> cmatrix<T>::log() const
{
    return map([](const T &n)
               { return std::log(n); });
}

template <class T>
cmatrix<T> cmatrix<T>::log2() const
{
    return map([](const T &n)
               { return std::log2(n); });
}

template <class T>
cmatrix<T> cmatrix<T>::log10() const
{
    return map([](const T &n)
               { return std::log10(n); });
}

template <class T>
cmatrix<T> cmatrix<T>::exp() const
{
    return map([](const T &n)
               { return std::exp(n); });
}