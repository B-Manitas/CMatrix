/**
 * @file MatrixManipulation.tpp
 * @brief This file contains the implementation of manipulation methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// INSERT FUNCTIONS

template <class T>
void Matrix<T>::insert_row(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the row of any size.
    if (is_empty())
        check_expected_id(pos, 0);

    else
    {
        check_expected_id(pos, 0, dim_v());
        check_valid_row(val);
    }

    matrix.insert(matrix.begin() + pos, val);
}

template <class T>
void Matrix<T>::insert_column(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the column of any size.
    if (is_empty())
    {
        check_expected_id(pos, 0);

        for (size_t i = 0; i < val.size(); i++)
            matrix.push_back(std::vector<T>{val.at(i)});
    }

    else
    {
        check_expected_id(pos, 0, dim_h());
        check_valid_col(val);

        for (size_t i = 0; i < dim_v(); i++)
            matrix.at(i).insert(matrix.at(i).begin() + pos, val.at(i));
    }
}

// ==================================================
// PUSH FUNCTIONS

template <class T>
void Matrix<T>::push_row_front(const std::vector<T> &val)
{
    insert_row(0, val);
}

template <class T>
void Matrix<T>::push_row_back(const std::vector<T> &val)
{
    insert_row(dim_v(), val);
}

template <class T>
void Matrix<T>::push_col_front(const std::vector<T> &val)
{
    insert_column(0, val);
}

template <class T>
void Matrix<T>::push_col_back(const std::vector<T> &val)
{
    insert_column(dim_h(), val);
}

// ==================================================
// FIND FUNCTIONS

template <class T>
int Matrix<T>::find_row(const std::function<bool(std::vector<T>)> &f) const
{
    for (size_t row = 0; row < dim_v(); row++)
        if (f(rows_vec(row)))
            return row;

    return -1;
}

template <class T>
int Matrix<T>::find_row(const std::vector<T> &val) const
{
    return find_row([&](std::vector<T> row)
                   { return row == val; });
}

template <class T>
int Matrix<T>::find_column(const std::function<bool(std::vector<T>)> &f) const
{
    for (size_t col = 0; col < dim_h(); col++)
        if (f(columns_vec(col)))
            return col;

    return -1;
}

template <class T>
int Matrix<T>::find_column(const std::vector<T> &val) const
{
    return find_column([&](std::vector<T> col)
                   { return col == val; });
}

template <class T>
std::tuple<int, int> Matrix<T>::find(const std::function<bool(T)> &f) const
{
    for (size_t row = 0; row < dim_v(); row++)
        for (size_t col = 0; col < dim_h(); col++)
            if (f(cell(row, col)))
                return std::tuple<int, int>(int(col), int(row));

    return std::tuple<int, int>(-1, -1);
}

template <class T>
std::tuple<int, int> Matrix<T>::find(const T &val) const
{
    return find([&](T e)
                { return e == val; });
}

// ==================================================
// ERASE FUNCTIONS

template <class T>
void Matrix<T>::remove_row(const size_t &pos)
{
    check_valid_row_id(pos);
    matrix.erase(matrix.begin() + pos);
}

template <class T>
void Matrix<T>::remove_column(const size_t &pos)
{
    check_valid_col_id(pos);

    if (dim_h() == 1)
        matrix.clear();

    else
        for (size_t i = 0; i < dim_v(); i++)
            matrix.at(i).erase(matrix.at(i).begin() + pos);
}