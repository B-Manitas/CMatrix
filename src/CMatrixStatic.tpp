/**
 * @defgroup static CMatrixStatic
 * @file CMatrixStatic.tpp
 * @brief This file contains the implementation of static methods of the class.
 *
 * @see cmatrix
 */

// ==================================================
// GENERATOR METHODS

template <>
cmatrix<int> cmatrix<int>::randint(const size_t &height, const size_t &width, const int &min, const int &max, const int &seed)
{
    // Set the seed
    std::srand(seed);
    cmatrix<int> m;

    for (size_t r = 0; r < height; r++)
    {
        std::vector<int> row;

        // Generate a random number for each column
        for (size_t c = 0; c < width; c++)
            row.push_back(rand() % max + min);

        m.push_row_back(row);
    }

    return m;
}

template <>
cmatrix<float> cmatrix<float>::randfloat(const size_t &height, const size_t &width, const float &min, const float &max, const int &seed)
{
    // Set the seed
    std::srand(seed);
    cmatrix<float> m;

    for (size_t r = 0; r < height; r++)
    {
        std::vector<float> row;

        // Generate a random number for each column
        for (size_t c = 0; c < width; c++)
            row.push_back((float)rand() / RAND_MAX * (max - min) + min);

        m.push_row_back(row);
    }

    return m;
}

template <>
cmatrix<int> cmatrix<int>::zeros(const size_t &width, const size_t &height)
{
    return cmatrix<int>(height, width, 0);
}

template <>
cmatrix<int> cmatrix<int>::identity(const size_t &size)
{
    cmatrix<int> m = cmatrix<int>::zeros(size, size);
    m.set_diag(std::vector<int>(size, 1));
    return m;
}

// ==================================================
// OTHERS METHODS

template <class T>
bool cmatrix<T>::is_matrix(const std::vector<std::vector<T>> &m)
{
    size_t rowSize = 0;

    // Check if all the rows have the same size
    for (const std::vector<T> &row : m)
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
cmatrix<T> cmatrix<T>::merge(const cmatrix<T> &m1, const cmatrix<T> &m2, const unsigned int &axis)
{
    cmatrix<T> m = m1.copy();
    m.concatenate(m2, axis);
    return m;
}
