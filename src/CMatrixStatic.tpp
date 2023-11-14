/**
 * @defgroup static CMatrixStatic
 * @file CMatrixStatic.tpp
 * @brief This file contains the implementation of static methods of the class.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_STATIC_TPP
#define CMATRIX_STATIC_TPP

// ==================================================
// GENERATOR METHODS

template <> inline
cmatrix<int> cmatrix<int>::randint(const size_t &height, const size_t &width, const int &min, const int &max, const int &seed)
{
    // Set the seed
    std::srand(seed);
    std::vector<std::vector<int>> m(height, std::vector<int>(width));

    // Generate a random number for each cell
    for (size_t r = 0; r < height; r++)
        for (size_t c = 0; c < width; c++)
            m[r][c] = rand() % max + min;

    return cmatrix<int>(m);
}

template <> inline
cmatrix<float> cmatrix<float>::randfloat(const size_t &height, const size_t &width, const float &min, const float &max, const int &seed)
{
    // Set the seed
    std::srand(seed);
    std::vector<std::vector<float>> m(height, std::vector<float>(width));

    // Generate a random number for each cell
    for (size_t r = 0; r < height; r++)
        for (size_t c = 0; c < width; c++)
            m[r][c] = (float)rand() / RAND_MAX * (max - min) + min;

    return cmatrix<float>(m);
}

template <> inline
cmatrix<int> cmatrix<int>::zeros(const size_t &width, const size_t &height)
{
    return cmatrix<int>(height, width, 0);
}

template <> inline
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

#endif // CMATRIX_STATIC_TPP
