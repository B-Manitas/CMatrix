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


