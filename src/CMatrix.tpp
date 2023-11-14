/**
 * @defgroup general CMatrix
 * @file CMatrix.tpp
 * @brief This file contains the implementation of general methods of the class.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_TPP
#define CMATRIX_TPP

// ==================================================
// GENERAL FUNCTIONS

template <class T>
void cmatrix<T>::print() const
{
    std::cout << *this << std::endl;
}

template <class T>
void cmatrix<T>::clear()
{
    matrix = std::vector<std::vector<T>>();
}

template <class T>
cmatrix<T> cmatrix<T>::copy() const
{
    return *this;
}

template <class T>
void cmatrix<T>::apply(const std::function<T(T, size_t, size_t)> &f)
{
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            cell(r, c) = f(cell(r, c), r, c);
}

template <class T>
void cmatrix<T>::apply(const std::function<T(T)> &f)
{
    #pragma omp parallel for collapse(2)
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            set_cell(r, c, f(cell(r, c)));
}

template <class T>
cmatrix<T> cmatrix<T>::map(const std::function<T(T, size_t, size_t)> &f) const
{
    cmatrix<T> m = copy();
    m.apply(f);
    return m;
}

template <class T>
template <class U>
cmatrix<U> cmatrix<T>::map(const std::function<U(T, size_t, size_t)> &f) const
{
    cmatrix<U> m = cmatrix<U>(height(), width());

    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            m.cell(r, c) = f(cell(r, c), r, c);

    return m;
}

template <class T>
cmatrix<T> cmatrix<T>::map(const std::function<T(T)> &f) const
{
    cmatrix<T> m = copy();
    m.apply(f);
    return m;
}

template <class T>
template <class U>
cmatrix<U> cmatrix<T>::map(const std::function<U(T)> &f) const
{
    // Create a new matrix with the same dimensions
    cmatrix<U> m = cmatrix<U>(height(), width());

    // Set the mapped value for each cell
    #pragma omp parallel for collapse(2)
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            m.cell(r, c) = f(cell(r, c));

    return m;
}

template <class T>
void cmatrix<T>::fill(const T &value)
{
    *this = cmatrix<T>(height(), width(), value);
}

template <class T>
std::vector<std::vector<T>> cmatrix<T>::to_vector() const
{
    return matrix;
}

// ==================================================
// CAST FUNCTIONS

template <class T>
template <class U>
cmatrix<U> cmatrix<T>::__cast(std::true_type) const
{
    // Create a new matrix with the same dimensions
    cmatrix<U> m(height(), width());

    // Set the casted value for each cell
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            m.set_cell(r, c, static_cast<U>(cell(r, c)));

    return m;
}

template <class T>
template <class U>
cmatrix<U> cmatrix<T>::__cast(std::false_type) const
{
    throw std::invalid_argument("T type" +
                                std::string(typeid(T).name()) +
                                " must be convertible into U type " +
                                std::string(typeid(U).name()) + ".");
}

template <class T>
template <class U>
cmatrix<U> cmatrix<T>::cast() const
{
    return __cast<U>(std::is_convertible<T, U>());
}

// ==================================================
// TYPE CONVERSION FUNCTIONS

// TO INT

template <class T>
cmatrix<int> cmatrix<T>::to_int() const
{
    return cast<int>();
}

template <>
cmatrix<int> cmatrix<std::string>::to_int() const
{
    return map<int>([&](std::string cell)
                    { 
                        try
                        {
                            return std::stoi(cell);
                        }
                        catch(const std::exception& e)
                        {
                            #pragma omp critical
                            throw std::runtime_error("The string matrix contains non-int values.");
                        } });
}

// TO FLOAT

template <>
cmatrix<float> cmatrix<std::string>::to_float() const
{
    return map<float>([&](std::string cell)
                      { 
                        try
                        {
                            return std::stof(cell);
                        }
                        catch(const std::exception& e)
                        {
                            #pragma omp critical
                            throw std::runtime_error("The string matrix contains non-float values.");
                        } });
}

template <class T>
cmatrix<float> cmatrix<T>::to_float() const
{
    return cast<float>();
}

// TO STRING

template <class T>
cmatrix<std::string> cmatrix<T>::__to_string(std::true_type) const
{
    return map<std::string>([&](T cell)
                            { return std::to_string(cell); });
}

template <class T>
cmatrix<std::string> cmatrix<T>::__to_string(std::false_type) const
{
    throw std::invalid_argument("The type should be a primitive type. Actual type: " +
                                std::string(typeid(T).name()) + ".");
}

template <class T>
cmatrix<std::string> cmatrix<T>::to_string() const
{
    return __to_string(std::is_fundamental<T>());
}

#endif // CMATRIX_TPP
