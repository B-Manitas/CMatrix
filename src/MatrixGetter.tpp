/**
 * @file MatrixGetter.tpp
 * @brief This file contains the implementation of getter methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// GET METHODS

template <class T>
std::vector<T> Matrix<T>::rows_vec(const size_t &n) const
{
    check_valid_row_id(n);
    return matrix.at(n);
}

template <class T>
std::vector<T> Matrix<T>::columns_vec(const size_t &n) const
{
    check_valid_col_id(n);
    std::vector<T> col;

    for (auto &&row : matrix)
        col.push_back(row.at(n));

    return col;
}

// ==================================================
// GET SUBMATRIX METHODS

template <class T>
Matrix<T> Matrix<T>::rows(const size_t &ids) const
{
    return rows({ids});
}

template <class T>
Matrix<T> Matrix<T>::rows(const std::initializer_list<size_t> &ids) const
{
    Matrix<T> m;

    for (const size_t &id : ids)
    {
        check_valid_row_id(id);
        m.push_row_back(matrix.at(id));
    }

    return m;
}

template <class T>
Matrix<T> Matrix<T>::columns(const size_t &ids) const
{
    return columns({ids});
}

template <class T>
Matrix<T> Matrix<T>::columns(const std::initializer_list<size_t> &ids) const
{
    Matrix<T> m;

    for (const size_t &id : ids)
    {
        check_valid_col_id(id);
        std::vector<T> col;

        // Get the id-th column
            col.push_back(row.at(id));

        m.push_col_back(col);
    }

    return m;
}

template <class T>
Matrix<T> Matrix<T>::cells(const size_t &row, const size_t &col) const
{
    return cells({{row, col}});
}

template <class T>
Matrix<T> Matrix<T>::cells(const std::initializer_list<std::pair<size_t, size_t>> &ids) const
{
    Matrix<T> m;

    // Get the id-th cell and push it into the matrix
    for (const std::pair<size_t, size_t> &id : ids)
        m.push_col_back({cell(id.first, id.second)});

    return m;
}

template <class T>
T &Matrix<T>::cell(const size_t &row, const size_t &col)
{
    check_valid_row_id(row);
    check_valid_col_id(col);
    return matrix.at(row).at(col);
}

template <class T>
T Matrix<T>::cell(const size_t &row, const size_t &col) const
{
    check_valid_row_id(row);
    check_valid_col_id(col);
    return matrix.at(row).at(col);
}

// ==================================================
// DIM METHODS

template <class T>
size_t Matrix<T>::dim_h() const
{
    return dim_v() == 0 ? 0 : matrix.at(0).size();
}

template <class T>
size_t Matrix<T>::dim_v() const
{
    return matrix.size();
}

template <class T>
std::tuple<size_t, size_t> Matrix<T>::dim() const
{
    return std::tuple<size_t, size_t>(dim_v(), dim_h());
}

// ==================================================
// SIMILARS MATRIX

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    // Create a new matrix with the inverted dimensions
    Matrix<T> m(dim_h(), dim_v());

    // Swap the rows and the columns
    for (size_t r = 0; r < dim_v(); r++)
        for (size_t c = 0; c < dim_h(); c++)
            m.cell(c, r) = cell(r, c);

    return m;
}

template <class T>
std::vector<T> Matrix<T>::diag() const
{
    std::vector<T> d;

    // Iterate over the diagonal of a matrix potentially not square
    for (size_t i = 0; i < std::min(dim_h(), dim_v()); i++)
        d.push_back(cell(i, i));

    return d;
}
