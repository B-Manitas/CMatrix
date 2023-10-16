/**
 * @file MatrixStatic.tpp
 * @brief This file contains the implementation of static methods of the cmatrix class.
 * @see cmatrix
 */

// ==================================================
// GENERATOR METHODS

template <>
cmatrix<int> cmatrix<int>::randint(const size_t &dim_h, const size_t &dim_v, const int &min, const int &max, const int &seed)
{
    // Set the seed
    std::srand(seed);
    cmatrix<int> m;

    for (size_t r = 0; r < dim_v; r++)
    {
        std::vector<int> row;

        // Generate a random number for each column
        for (size_t c = 0; c < dim_h; c++)
            row.push_back(rand() % max + min);

        m.push_row_back(row);
    }

    return m;
}

template <>
cmatrix<int> cmatrix<int>::zeros(const size_t &dim_h, const size_t &dim_v)
{
    return cmatrix<int>(dim_v, dim_h, 0);
}

template <>
cmatrix<int> cmatrix<int>::identity(const size_t &dim)
{
    cmatrix<int> m = cmatrix<int>::zeros(dim, dim);
    m.set_diag(std::vector<int>(dim, 1));
    return m;
}

// ==================================================
// OTHERS METHODS

template <class T>
bool cmatrix<T>::is_matrix(const std::initializer_list<std::initializer_list<T>> &m)
{
    size_t rowSize = 0;

    // Check if all the rows have the same size
    for (const std::initializer_list<T> &row : m)
    {
        // If it's the first row, set the size
        if (rowSize == 0)
            rowSize = row.size();

        // If the size is different, return false
        else if (row.size() != rowSize)
            return false;
    }

    return true;
}

template <class T>
std::vector<T> cmatrix<T>::flatten_vector(const std::vector<std::vector<T>> &vec)
{
    std::vector<T> r;

    for (auto &&row : vec)
        for (auto &&e : row)
            r.push_back(e);

    return r;
}
