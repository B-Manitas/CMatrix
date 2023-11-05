/**
 * @defgroup manipulation CMatrixManipulation
 * @file CMatrixManipulation.tpp
 * @brief This file contains the implementation of methods to find elements and to perform manipulations on the matrix.
 *
 * @see cmatrix
 */

// ==================================================
// INSERT FUNCTIONS

template <class T>
void cmatrix<T>::insert_row(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the row of any size
    // However, the position must be 0
    if (is_empty())
        __check_expected_id(pos, 0);

    // Otherwise, we can only insert a row of the same size as the others
    // The position must be between 0 and the number of rows
    else
    {
        __check_expected_id(pos, 0, height());
        __check_valid_row(val);
    }

    matrix.insert(matrix.begin() + pos, val);
}

template <class T>
void cmatrix<T>::insert_column(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the column of any size
    if (is_empty())
    {
        // The position must be 0
        __check_expected_id(pos, 0);

        // Insert the column
        for (size_t i = 0; i < val.size(); i++)
            matrix.push_back(std::vector<T>{val[i]});
    }

    // Otherwise, we can only insert a column of the same size as the others
    else
    {
        // Check if the position is valid
        __check_expected_id(pos, 0, width());
        __check_valid_col(val);
        
        // Reserve the space for the new column
        matrix.reserve(height() + val.size());

        // For each row, insert the value at the given position
        #pragma omp parallel for
        for (size_t i = 0; i < height(); i++)
            matrix[i].insert(matrix[i].begin() + pos, val[i]);
    }
}

// ==================================================
// PUSH FUNCTIONS

template <class T>
void cmatrix<T>::push_row_front(const std::vector<T> &val)
{
    insert_row(0, val);
}

template <class T>
void cmatrix<T>::push_row_back(const std::vector<T> &val)
{
    insert_row(height(), val);
}

template <class T>
void cmatrix<T>::push_col_front(const std::vector<T> &val)
{
    insert_column(0, val);
}

template <class T>
void cmatrix<T>::push_col_back(const std::vector<T> &val)
{
    insert_column(width(), val);
}

// ==================================================
// FIND FUNCTIONS

template <class T>
int cmatrix<T>::find_row(const std::function<bool(std::vector<T>)> &f) const
{
    // For each row, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        if (f(rows_vec(row)))
            return row;

    return -1;
}

template <class T>
int cmatrix<T>::find_row(const std::vector<T> &val) const
{
    return find_row([&](std::vector<T> row)
                    { return row == val; });
}

template <class T>
int cmatrix<T>::find_column(const std::function<bool(std::vector<T>)> &f) const
{
    // For each column, check if the condition is satisfied
    for (size_t col = 0; col < width(); col++)
        if (f(columns_vec(col)))
            return col;

    return -1;
}

template <class T>
int cmatrix<T>::find_column(const std::vector<T> &val) const
{
    return find_column([&](std::vector<T> col)
                       { return col == val; });
}

template <class T>
std::tuple<int, int> cmatrix<T>::find(const std::function<bool(T)> &f) const
{
    // For each cell, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        for (size_t col = 0; col < width(); col++)
            if (f(cell(row, col)))
                return std::tuple<int, int>(int(col), int(row));

    return std::tuple<int, int>(-1, -1);
}

template <class T>
std::tuple<int, int> cmatrix<T>::find(const T &val) const
{
    return find([&](T e)
                { return e == val; });
}

// ==================================================
// ERASE FUNCTIONS

template <class T>
void cmatrix<T>::remove_row(const size_t &pos)
{
    __check_valid_row_id(pos);
    matrix.erase(matrix.begin() + pos);
}

template <class T>
void cmatrix<T>::remove_column(const size_t &pos)
{
    __check_valid_col_id(pos);

    // If the matrix has only one column, we can clear it
    // To prevent matrix = [[]]
    if (width() == 1)
        matrix.clear();

    // Otherwise, for each row, remove the value at the given position
    else
        for (size_t i = 0; i < height(); i++)
            matrix[i].erase(matrix[i].begin() + pos);
}

template <class T>
void cmatrix<T>::concatenate(const cmatrix<T> &m, const unsigned int &axis)
{
    // Concatenate the rows
    if (axis == 0)
    {
        if (width() != m.width())
            throw std::invalid_argument("The matrices must have the same number of columns. Actual: " +
                                        std::to_string(width()) +
                                        " and " +
                                        std::to_string(m.width()));

        // Push the rows of the second matrix
        for (size_t i = 0; i < m.height(); i++)
            push_row_back(m.rows_vec(i));
    }

    // Concatenate the columns
    else if (axis == 1)
    {
        if (height() != m.height())
            throw std::invalid_argument("The matrices must have the same number of rows. Actual: " +
                                        std::to_string(height()) +
                                        " and " +
                                        std::to_string(m.height()));

        // Push the columns of the second matrix
        for (size_t i = 0; i < m.width(); i++)
            push_col_back(m.columns_vec(i));
    }

    else
        throw std::invalid_argument("The axis must be 0 or 1. Actual: " + std::to_string(axis));
}
