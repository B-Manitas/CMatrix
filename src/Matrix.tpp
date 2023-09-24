/**
 * @file Matrix.tpp
 * @brief This file contains the implementation of global methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// GENERAL FUNCTIONS

template <class T>
void Matrix<T>::show() const
{
    for (auto &&row : matrix)
    {
        for (auto &&cell : row)
            std::cout << cell << " ";

        std::cout << std::endl;
    }
}

template <class T>
void Matrix<T>::clear()
{
    matrix = std::vector<std::vector<T>>();;
}
