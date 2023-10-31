/**
 * @defgroup getter CMatrixGetter
 * @file CMatrixGetter.tpp
 * @brief This file contains the implementation of methods to retrieve information from the matrix and get its elements.
 *
 * @see cmatrix
 */

// ==================================================
// GET METHODS

template <class T>
std::vector<T> cmatrix<T>::rows_vec(const size_t &n) const
{
    __check_valid_row_id(n);
    return matrix.at(n);
}

template <class T>
std::vector<T> cmatrix<T>::columns_vec(const size_t &n) const
{
    __check_valid_col_id(n);
    std::vector<T> col;

    for (auto &&row : matrix)
        col.push_back(row.at(n));

    return col;
}

// ==================================================
// GET SUBMATRIX METHODS

template <class T>
cmatrix<T> cmatrix<T>::rows(const size_t &ids) const
{
    return rows({ids});
}

template <class T>
cmatrix<T> cmatrix<T>::rows(const std::initializer_list<size_t> &ids) const
{
    return rows(std::vector<size_t>(ids));
}

template <class T>
cmatrix<T> cmatrix<T>::rows(const std::vector<size_t> &ids) const
{
    cmatrix<T> m;

    for (const size_t &id : ids)
    {
        __check_valid_row_id(id);
        m.push_row_back(matrix.at(id));
    }

    return m;
}

template <class T>
cmatrix<T> cmatrix<T>::columns(const size_t &ids) const
{
    return columns({ids});
}

template <class T>
cmatrix<T> cmatrix<T>::columns(const std::initializer_list<size_t> &ids) const
{
    return columns(std::vector<size_t>(ids));
}

template <class T>
cmatrix<T> cmatrix<T>::columns(const std::vector<size_t> &ids) const
{
    cmatrix<T> m;

    for (const size_t &id : ids)
    {
        __check_valid_col_id(id);
        std::vector<T> col;

        // Get the id-th column
        for (const std::vector<T> &row : matrix)
            col.push_back(row.at(id));

        m.push_col_back(col);
    }

    return m;
}

template <class T>
cmatrix<T> cmatrix<T>::cells(const size_t &row, const size_t &col) const
{
    return cells({{row, col}});
}

template <class T>
cmatrix<T> cmatrix<T>::cells(const std::initializer_list<std::pair<size_t, size_t>> &ids) const
{
    return cells(std::vector<std::pair<size_t, size_t>>(ids));
}

template <class T>
cmatrix<T> cmatrix<T>::cells(const std::vector<std::pair<size_t, size_t>> &ids) const
{
    cmatrix<T> m;

    // Get the id-th cell and push it into the matrix
    for (const std::pair<size_t, size_t> &id : ids)
        m.push_col_back({cell(id.first, id.second)});

    return m;
}

template <class T>
T &cmatrix<T>::cell(const size_t &row, const size_t &col)
{
    __check_valid_row_id(row);
    __check_valid_col_id(col);
    return matrix.at(row).at(col);
}

template <class T>
T cmatrix<T>::cell(const size_t &row, const size_t &col) const
{
    __check_valid_row_id(row);
    __check_valid_col_id(col);
    return matrix.at(row).at(col);
}

template <class T>
cmatrix<T> cmatrix<T>::slice_rows(const size_t &start, const size_t &end) const
{
    __check_valid_row_id(start);
    __check_valid_row_id(end);

    if (start > end)
        throw std::invalid_argument("The start index must be less than or equal to the end index");

    // Create a vector of vectors from start to end containing the rows
    std::vector<std::vector<T>> submatrix(matrix.begin() + start, matrix.begin() + end + 1);

    return cmatrix<T>(submatrix);
}

template <class T>
cmatrix<T> cmatrix<T>::slice_columns(const size_t &start, const size_t &end) const
{
    __check_valid_col_id(start);
    __check_valid_col_id(end);

    if (start > end)
        throw std::invalid_argument("The start index must be less than or equal to the end index");

    // Create a vector of ids from start to end
    std::vector<size_t> ids(end - start + 1);
    std::iota(ids.begin(), ids.end(), start);

    return columns(ids);
}

// ==================================================
// DIM METHODS

template <class T>
size_t cmatrix<T>::width() const
{
    return height() == 0 ? 0 : matrix.at(0).size();
}

template <class T>
size_t cmatrix<T>::height() const
{
    return matrix.size();
}

template <class T>
std::pair<size_t, size_t> cmatrix<T>::size() const
{
    return std::pair<size_t, size_t>(height(), width());
}

// ==================================================
// SIMILARS MATRIX

template <class T>
cmatrix<T> cmatrix<T>::transpose() const
{
    // Create a new matrix with the inverted dimensions
    cmatrix<T> m(width(), height());

    // Swap the rows and the columns
    for (size_t r = 0; r < height(); r++)
        for (size_t c = 0; c < width(); c++)
            m.cell(c, r) = cell(r, c);

    return m;
}

template <class T>
std::vector<T> cmatrix<T>::diag() const
{
    std::vector<T> d;

    // Iterate over the diagonal of a matrix potentially not square
    for (size_t i = 0; i < std::min(width(), height()); i++)
        d.push_back(cell(i, i));

    return d;
}
