/**
 * @defgroup setter CMatrixSetter
 * @file CMatrixSetter.tpp
 * @brief This file contains the implementation of methods to set values in the matrix.
 * 
 * @see cmatrix
 */

// ==================================================
// SET FUNCTIONS

template <class T>
void cmatrix<T>::set_row(const size_t &n, const std::vector<T> &val)
{
    __check_valid_row_id(n);
    __check_valid_row(val);
    matrix.at(n) = val;
}

template <class T>
void cmatrix<T>::set_column(const size_t &n, const std::vector<T> &val)
{
    __check_valid_col_id(n);
    __check_valid_col(val);

    // For each row, set the value at the given position
    for (size_t i = 0; i < dim_v(); i++)
        matrix.at(i).at(n) = val.at(i);
}

template <class T>
void cmatrix<T>::set_cell(const size_t &row, const size_t &col, const T &val)
{
    __check_valid_row_id(row);
    __check_valid_col_id(col);
    matrix.at(row).at(col) = val;
}

template <class T>
void cmatrix<T>::set_diag(const std::vector<T> &val)
{
    __check_valid_diag(val);

    // Iterate over the diagonal
    for (size_t i = 0; i < std::min(dim_h(), dim_v()); i++)
        cell(i, i) = val.at(i);
}
