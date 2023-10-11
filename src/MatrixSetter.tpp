/**
 * @file MatrixSetter.tpp
 * @brief This file contains the implementation of setter methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// SET FUNCTIONS

template <class T>
void Matrix<T>::setRow(const size_t &n, const std::vector<T> &val)
{
    checkIdRow(n);
    checkValidRow(val);
    matrix.at(n) = val;
}

template <class T>
void Matrix<T>::setCol(const size_t &n, const std::vector<T> &val)
{
    checkIdCol(n);
    checkValidCol(val);
    for (size_t i = 0; i < dimV(); i++)
        matrix.at(i).at(n) = val.at(i);
}

template <class T>
void Matrix<T>::setCell(const size_t &col, const size_t &row, const T &val)
{
    checkIdRow(row);
    checkIdCol(col);
    matrix.at(row).at(col) = val;
}

template <class T>
void Matrix<T>::setDiag(const std::vector<T> &val)
{
    checkValidDiag(val);
    size_t min = std::min(dimH(), dimV());

    for (size_t i = 0; i < min; i++)
        cell(i, i) = val.at(i);
}
