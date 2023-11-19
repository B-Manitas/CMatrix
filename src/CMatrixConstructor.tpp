/**
 * @file CMatrixConstructor.tpp
 * @brief This file contains the implementation of constructors and destructors.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_CONSTRUCTOR_TPP
#define CMATRIX_CONSTRUCTOR_TPP

// ==================================================
// CONSTRUCTORS

template <class T>
cmatrix<T>::cmatrix() {}

template <class T>
cmatrix<T>::cmatrix(const std::initializer_list<std::initializer_list<T>> &m) : cmatrix<T>(std::vector<std::vector<T>>(m.begin(), m.end())) {}

template <class T>
cmatrix<T>::cmatrix(const std::vector<std::vector<T>> &m)
{
    if (is_matrix(m))
        matrix = m;

    else
        throw std::invalid_argument("The vector must be a matrix.");
}

template <class T>
cmatrix<T>::cmatrix(const size_t &height, const size_t &width)
{
    matrix = std::vector<std::vector<T>>(height, std::vector<T>(width));
}

template <class T>
cmatrix<T>::cmatrix(const size_t &height, const size_t &width, const T &value)
{
    matrix = std::vector<std::vector<T>>(height, std::vector<T>(width, value));
}

template <class T>
template <class U>
cmatrix<T>::cmatrix(const cmatrix<U> &m)
{
    cmatrix<T> result = m.template cast<T>();
    matrix = result.to_vector();
}

// ==================================================
// DESTRUCTOR

template <class T>
cmatrix<T>::~cmatrix() {}

#endif // CMATRIX_CONSTRUCTOR_TPP
