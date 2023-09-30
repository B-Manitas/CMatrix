/**
 * @file MatrixSetter.tpp
 * @brief This file contains the implementation of setter methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// SET FUNCTIONS

template <class T>
void Matrix<T>::setRow(const size_t n, const std::vector<T> val)
{
    if (val.size() != dimH())
        throw std::invalid_argument("val must be the same length than matrix" + std::to_string(val.size()) + " " + std::to_string(dimV()));

    if (n < dimV())
        matrix.at(n) = val;

    else
        throw std::invalid_argument("invalid row");
}

template <class T>
void Matrix<T>::setCol(const size_t n, const std::vector<T> val)
{
    if (val.size() != dimV())
        throw std::invalid_argument("val must be the same length than matrix");

    if (n < dimH())
        for (size_t i = 0; i < dimV(); i++)
            matrix.at(i).at(n) = val.at(i);

    else
        throw std::invalid_argument("invalid col");
}

template <class T>
void Matrix<T>::setCell(const int col, const int row, T val)
{
    if (dimH() > (size_t)col and dimV() > (size_t)row)
        matrix.at(row).at(col) = val;

    else
        throw std::invalid_argument("invalid row or col");
}

    if (val.size() != min)
    for (size_t i = 0; i < min; i++)
