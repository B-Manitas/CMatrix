/**
 * @file MatrixGetter.tpp
 * @brief This file contains the implementation of getter methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// GET METHODS

template <class T>
std::vector<T> Matrix<T>::getRow(const size_t &n) const
{
    checkIdRow(n);
    return matrix.at(n);
}

template <class T>
std::vector<T> Matrix<T>::getFlatCol(const size_t &n) const
{
    checkIdCol(n);
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
        checkIdRow(id);
        m.pushRowBack(matrix.at(id));
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
        checkIdCol(id);
        std::vector<T> col;

        for (auto &&row : matrix)
            col.push_back(row.at(id));

        m.pushColBack(col);
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

    for (const std::pair<size_t, size_t> &id : ids)
        m.pushColBack({cell(id.first, id.second)});

    return m;
}

template <class T>
T &Matrix<T>::cell(const size_t &row, const size_t &col)
{
    checkIdRow(row);
    checkIdCol(col);
    return matrix.at(row).at(col);
}

template <class T>
T Matrix<T>::cell(const size_t &row, const size_t &col) const
{
    checkIdRow(row);
    checkIdCol(col);
    return matrix.at(row).at(col);
}

// ==================================================
// DIM METHODS

template <class T>
size_t Matrix<T>::dimH() const
{
    return dimV() == 0 ? 0 : matrix.at(0).size();
}

template <class T>
size_t Matrix<T>::dimV() const
{
    return matrix.size();
}

template <class T>
std::tuple<size_t, size_t> Matrix<T>::dim() const
{
    return std::tuple<size_t, size_t>(dimV(), dimH());
}

// ==================================================
// SIMILARS MATRIX

template <class T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> m(dimH(), dimV());

    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            m.cell(c, r) = cell(r, c);

    return m;
}

template <class T>
std::vector<T> Matrix<T>::diag() const
{
    std::vector<T> d;

    for (size_t i = 0; i < std::min(dimH(), dimV()); i++)
        d.push_back(cell(i, i));

    return d;
}
