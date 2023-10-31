/**
 * @file CMatrixConstructor.tpp
 * @brief This file contains the implementation of constructors and destructors.
 *
 * @see cmatrix
 */

// ==================================================
// CONSTRUCTORS

template <class T>
cmatrix<T>::cmatrix()
{
    __check_valid_type();
}

template <class T>
cmatrix<T>::cmatrix(const std::initializer_list<std::initializer_list<T>> &m) : cmatrix<T>(std::vector<std::vector<T>>(m.begin(), m.end())) {}

template <class T>
cmatrix<T>::cmatrix(const std::vector<std::vector<T>> &m)
{
    __check_valid_type();

    if (is_matrix(m))
        matrix = m;

    else
        throw std::invalid_argument("The vector must be a matrix.");
}

template <class T>
cmatrix<T>::cmatrix(const size_t &height, const size_t &width)
{
    __check_valid_type();

    matrix = std::vector<std::vector<T>>(height, std::vector<T>(width));
}

template <class T>
cmatrix<T>::cmatrix(const size_t &height, const size_t &width, const T &value)
{
    __check_valid_type();

    matrix = std::vector<std::vector<T>>(height, std::vector<T>(width, value));
}

template <class T>
template <class U>
cmatrix<T>::cmatrix(const cmatrix<U> &m)
{
    __check_valid_type();

    cmatrix<T> result = m.template cast<T>();
    matrix = result.to_vector();
}

// ==================================================
// DESTRUCTOR

template <class T>
cmatrix<T>::~cmatrix() {}