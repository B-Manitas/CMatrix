/**
 * @file MatrixConstructor.tpp
 * @brief This file contains the implementation of constructors and destructors.
 *
 * @see cmatrix
 */

// ==================================================
// CONSTRUCTORS

template <class T>
cmatrix<T>::cmatrix()
{
    check_valid_type();
}

template <class T>
cmatrix<T>::cmatrix(const std::initializer_list<std::initializer_list<T>> &m)
{
    check_valid_type();

    if (is_matrix(m))
        for (const std::initializer_list<T> &row : m)
            matrix.push_back(std::vector<T>(row));

    else
        throw std::invalid_argument("The initializer list must be a matrix.");
}

template <class T>
cmatrix<T>::cmatrix(const size_t &dim_v, const size_t &dim_h)
{
    check_valid_type();

    matrix = std::vector<std::vector<T>>(dim_v, std::vector<T>(dim_h));
}

template <class T>
cmatrix<T>::cmatrix(const size_t &dim_v, const size_t &dim_h, const T &value)
{
    check_valid_type();

    matrix = std::vector<std::vector<T>>(dim_v, std::vector<T>(dim_h, value));
}

template <class T>
template <class U>
cmatrix<T>::cmatrix(const cmatrix<U> &m)
{
    check_valid_type();

    cmatrix<T> result = m.template cast<T>();
    matrix = result.to_vector();
}

// ==================================================
// DESTRUCTOR

template <class T>
cmatrix<T>::~cmatrix() {}