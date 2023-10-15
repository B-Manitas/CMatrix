/**
 * @file MatrixStatic.tpp
 * @brief This file contains the implementation of static methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// GENERATOR METHODS

template <>
Matrix<int> Matrix<int>::randint(const size_t &dimH, const size_t &dimV, const int &min, const int &max, const int &seed)
{
    std::srand(seed);
    Matrix<int> m;

    for (size_t r = 0; r < dimV; r++)
    {
        std::vector<int> row;

        for (size_t c = 0; c < dimH; c++)
            row.push_back(rand() % max + min);

        m.pushRowBack(row);
    }

    return m;
}

template <>
Matrix<int> Matrix<int>::zeros(const size_t &dimH, const size_t &dimV)
{
    return Matrix<int>(dimV, dimH, 0);
}

template <>
Matrix<int> Matrix<int>::identity(const size_t &dim)
{
    Matrix<int> m = Matrix<int>::zeros(dim, dim);
    m.setDiag(std::vector<int>(dim, 1));
    return m;
}

// ==================================================
// OTHERS METHODS

template <class T>
bool Matrix<T>::isMatrix(const std::initializer_list<std::initializer_list<T>> &m)
{
    size_t rowSize = 0;
    for (auto &&row : m)
    {
        if (rowSize == 0)
            rowSize = row.size();

        else if (row.size() != rowSize)
            return false;
    }
    return true;
}

template <class T>
std::vector<T> Matrix<T>::flattenVector(const std::vector<std::vector<T>> &vec)
{
    std::vector<T> r;

    for (auto &&row : vec)
        for (auto &&e : row)
            r.push_back(e);

    return r;
}
