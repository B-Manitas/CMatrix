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
    return matrix.at(n);
}

template <class T>
std::vector<std::vector<T>> Matrix<T>::getCol(const size_t &n) const
{
    std::vector<std::vector<T>> col;

    for (auto &&row : matrix)
        col.push_back(std::vector<T>{row.at(n)});

    return col;
}

template <class T>
std::vector<T> Matrix<T>::getFlatCol(const size_t &n) const
{
    std::vector<T> col;

    for (auto &&row : matrix)
        col.push_back(row.at(n));

    return col;
}

template <class T>
T Matrix<T>::getCell(const size_t &col, const size_t &row) const
{
    return matrix.at(row).at(col);
}

// ==================================================
// SLICING METHODS

template <class T>
Matrix<T> Matrix<T>::at(const size_t &y) const
{
    if ((size_t)y < 0 || (size_t)y >= dimV())
        throw std::out_of_range("Invalid row index");

    Matrix<T> m;
    m.pushRowFront(getRow(y));
    return m;
}

template <class T>
Matrix<T> Matrix<T>::iloc(const size_t &x) const
{
    if ((size_t)x < 0 || (size_t)x >= dimH())
        throw std::out_of_range("Invalid column index");

    Matrix<T> m;
    m.pushColFront(Matrix<T>::flattenVector(getCol(x)));
    return m;
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
    Matrix<T> m(dimV(), dimH());

    for (size_t r = 0; r < dimV(); r++)
        for (size_t c = 0; c < dimH(); c++)
            m.setCell(r, c, getCell(c, r));

    return m;
}

template <class T>
std::vector<T> Matrix<T>::diag() const
{
    std::vector<T> d;

    for (size_t i = 0; i < std::min(dimH(), dimV()); i++)
        d.push_back(getCell(i, i));

    return d;
}
