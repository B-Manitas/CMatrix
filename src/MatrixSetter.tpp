/**
 * @file MatrixSetter.tpp
 * @brief This file contains the implementation of setter methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// SET FUNCTIONS

template <class T>
void Matrix<T>::set_row(const size_t &n, const std::vector<T> &val)
{
    check_valid_row_id(n);
    check_valid_row(val);
    matrix.at(n) = val;
}

template <class T>
void Matrix<T>::set_column(const size_t &n, const std::vector<T> &val)
{
    check_valid_col_id(n);
    check_valid_col(val);

    // For each row, set the value at the given position
    for (size_t i = 0; i < dim_v(); i++)
        matrix.at(i).at(n) = val.at(i);
}

template <class T>
void Matrix<T>::set_cell(const size_t &col, const size_t &row, const T &val)
{
    check_valid_row_id(row);
    check_valid_col_id(col);
    matrix.at(row).at(col) = val;
}

template <class T>
void Matrix<T>::set_diag(const std::vector<T> &val)
{
    check_valid_diag(val);
    size_t min = std::min(dim_h(), dim_v());

    // Iterate over the diagonal
        cell(i, i) = val.at(i);
}
