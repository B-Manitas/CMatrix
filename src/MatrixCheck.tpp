/**
 * @file MatrixCheck.tpp
 * @brief This file contains the implementation of check methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// IS METHODS

template <class T>
bool Matrix<T>::isEmpty() const
{
    return dimH() == 0 and dimV() == 0;
}

template <class T>
bool Matrix<T>::isSquare() const
{
    return dimH() == dimV();
}

template <class T>
bool Matrix<T>::isAll(const std::function<bool(T)> &f) const
{
    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            if (!f(getCell(c, r)))
                return false;

    return true;
}

template <class T>
bool Matrix<T>::isAll(const T &val) const
{
    return isAll([&](T e)
                 { return e == val; });
}

template <class T>
bool Matrix<T>::isAny(const std::function<bool(T)> &f) const
{
    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            if (f(getCell(c, r)))
                return true;

    return false;
}

template <class T>
bool Matrix<T>::isAny(const T &val) const
{
    return isAny([&](T e)
                 { return e == val; });
}
