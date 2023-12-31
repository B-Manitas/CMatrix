/**
 * @defgroup manipulation CMatrixManipulation
 * @file CMatrixManipulation.tpp
 * @brief This file contains the implementation of methods to find elements and to perform manipulations on the matrix.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_MANIPULATION_TPP
#define CMATRIX_MANIPULATION_TPP

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
std::pair<int, int> cmatrix<T>::find(const std::function<bool(T)> &f) const
{
    // For each cell, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        for (size_t col = 0; col < width(); col++)
            if (f(cell(row, col)))
                return std::pair<int, int>(int(row), int(col));

    return std::pair<int, int>(-1, -1);
}

template <class T>
std::pair<int, int> cmatrix<T>::find(const T &val) const
{
    return find([&](T e)
                { return e == val; });
}

template <class T>
std::vector<std::pair<size_t, size_t>> cmatrix<T>::find_all(const std::function<bool(T)> &f) const
{
    std::vector<std::pair<size_t, size_t>> res;

    // For each cell, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        for (size_t col = 0; col < width(); col++)
            if (f(cell(row, col)))
                res.push_back(std::pair<size_t, size_t>(row, col));

    return res;
}

template <class T>
std::vector<std::pair<size_t, size_t>> cmatrix<T>::find_all(const cmatrix<cbool> &m) const
{
    // To select indexes of the mask that are true in the mask
    const bool &select_cells = m.height() == height() and m.width() == width();

    // To select indexes of the rows that are true in the mask
    const bool &select_rows = m.height() == height() and m.width() == 1;

    // To select indexes of the columns that are true in the mask
    const bool &select_cols = m.height() == 1 and m.width() == width();

    if (select_cells or select_rows or select_cols)
    {
        std::vector<std::pair<size_t, size_t>> ids;
        ids.reserve(m.sum_all());

        // For each cell, check if the condition is satisfied
        for (size_t row = 0; row < height(); row++)
            for (size_t col = 0; col < width(); col++)
            {
                // Check if the current INDEX is true in the mask
                const bool &cells = select_cells && m.cell(row, col);
                
                // Check if the current ROW is true in the mask
                const bool &rows = select_rows && m.cell(row, 0);
                
                // Check if the current COLUMN is true in the mask
                const bool &cols = select_cols && m.cell(0, col);

                if (cells or rows or cols)
                    ids.push_back(std::pair<size_t, size_t>(row, col));
            }

        return ids;
    }

    else
        throw std::invalid_argument("The matrix must have the same size or one of the two dimensions must be 1. Actual: " +
                                    std::to_string(height()) +
                                    "x" +
                                    std::to_string(width()) +
                                    " and " +
                                    std::to_string(m.height()) +
                                    "x" +
                                    std::to_string(m.width()));
}

template <class T>
std::vector<std::pair<size_t, size_t>> cmatrix<T>::find_all(const T &val) const
{
    return find_all([&](T e)
                    { return e == val; });
}

// ==================================================
// MASK FUNCTIONS

template <class T>
cmatrix<cbool> cmatrix<T>::mask(const std::function<bool(T)> &f) const
{
    cmatrix<cbool> res(height(), width(), false);

    // For each cell, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        for (size_t col = 0; col < width(); col++)
            res.set_cell(row, col, f(cell(row, col)));

    return res;
}

template <class T>
cmatrix<cbool> cmatrix<T>::mask(const std::function<bool(T, T)> &f, const cmatrix<T> &m) const
{
    // Check if the matrices have the same size
    __check_size(m);

    // Create the result matrix
    cmatrix<cbool> res(height(), width(), false);

    // For each cell, check if the condition is satisfied
    for (size_t row = 0; row < height(); row++)
        for (size_t col = 0; col < width(); col++)
            res.set_cell(row, col, f(cell(row, col), m.cell(row, col)));

    return res;
}

template <> inline
cmatrix<cbool> cmatrix<cbool>::not_() const
{
    return map([](cbool e)
               { return not e; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::eq(const cmatrix<T> &m) const
{
    return mask(std::equal_to<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::eq(const T &val) const
{
    return mask([val](T e)
                { return e == val; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::neq(const cmatrix<T> &m) const
{
    return mask(std::not_equal_to<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::neq(const T &val) const
{
    return mask([val](T e)
                { return e != val; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::leq(const cmatrix<T> &m) const
{
    return mask(std::less_equal<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::leq(const T &val) const
{
    return mask([val](T e)
                { return e <= val; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::geq(const cmatrix<T> &m) const
{
    return mask(std::greater_equal<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::geq(const T &val) const
{
    return mask([val](T e)
                { return e >= val; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::lt(const cmatrix<T> &m) const
{
    return mask(std::less<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::lt(const T &val) const
{
    return mask([val](T e)
                { return e < val; });
}

template <class T>
cmatrix<cbool> cmatrix<T>::gt(const cmatrix<T> &m) const
{
    return mask(std::greater<T>(), m);
}

template <class T>
cmatrix<cbool> cmatrix<T>::gt(const T &val) const
{
    return mask([val](T e)
                { return e > val; });
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

#endif // CMATRIX_MANIPULATION_TPP
