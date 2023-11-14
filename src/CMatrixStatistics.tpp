/**
 * @defgroup statistic CMatrixStatistics
 * @file CMatrixStatistics.tpp
 * @brief This file contains the implementation of methods to perform statistical operations on the matrix.
 *
 * @see cmatrix
 */

#ifndef CMATRIX_STATISTICS_TPP
#define CMATRIX_STATISTICS_TPP

template <class T>
cmatrix<T> cmatrix<T>::min(const unsigned int &axis) const
{
    // Compute the minimum for each row
    if (axis == 0)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(height(), std::vector<T>(1));

#pragma omp parallel for
        for (size_t r = 0; r < height(); r++)
        {
            // Push the first element of the row to the result matrix
            m[r][0] = cell(r, 0);

            // Check if the current element is smaller than the stored one
            for (size_t c = 0; c < width(); c++)
                if (cell(r, c) < m[r][0])
                    m[r][0] = cell(r, c);
        }

        return cmatrix<T>(m);
    }

    // Compute the minimum for each column
    else if (axis == 1)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(1, std::vector<T>(width()));

#pragma omp parallel for
        for (size_t i = 0; i < width(); i++)
        {
            // Push the first element of the column to the result matrix
            m[0][i] = cell(0, i);

            // Check if the current element is smaller than the stored one
            for (size_t j = 0; j < height(); j++)
                if (cell(j, i) < m[0][i])
                    m[0][i] = cell(j, i);
        }

        return cmatrix<T>(m);
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
T cmatrix<T>::min_all() const
{
    // Precondition: the matrix must have at least one element
    if (is_empty())
        throw std::invalid_argument("The matrix must have at least one element.");

    // Initialize the minimum to the first element of the matrix
    T min = cell(0, 0);

    // Check if the current element is smaller than the stored one
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (cell(i, j) < min)
                min = cell(i, j);

    return min;
}

template <class T>
cmatrix<T> cmatrix<T>::max(const unsigned int &axis) const
{
    // Compute the maximum for each row
    if (axis == 0)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(height(), std::vector<T>(1));

#pragma omp parallel for
        for (size_t r = 0; r < height(); r++)
        {
            // Push the first element of the row to the result matrix
            m[r][0] = cell(r, 0);

            // Check if the current element is greater than the stored one
            for (size_t c = 0; c < width(); c++)
                if (cell(r, c) > m[r][0])
                    m[r][0] = cell(r, c);
        }

        return cmatrix<T>(m);
    }

    // Compute the maximum for each column
    else if (axis == 1)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(1, std::vector<T>(width()));

#pragma omp parallel for
        for (size_t c = 0; c < width(); c++)
        {
            // Push the first element of the column to the result matrix
            m[0][c] = cell(0, c);

            // Check if the current element is greater than the stored one
            for (size_t r = 0; r < height(); r++)
                if (cell(r, c) > m[0][c])
                    m[0][c] = cell(r, c);
        }

        return cmatrix<T>(m);
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
T cmatrix<T>::max_all() const
{
    // Precondition: the matrix must have at least one element
    if (is_empty())
        throw std::invalid_argument("The matrix must have at least one element.");

    // Initialize the maximum to the first element of the matrix
    T max = cell(0, 0);

    // Check if the current element is greather than the stored one
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            if (cell(i, j) > max)
                max = cell(i, j);

    return max;
}

template <class T>
cmatrix<T> cmatrix<T>::sum(const unsigned int &axis, const T &zero) const
{

    // Compute the sum for each row
    if (axis == 0)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(height(), std::vector<T>(1));

#pragma omp parallel for
        for (size_t i = 0; i < height(); i++)
        {
            // Initialize the sum to zero
            T sum = zero;

            // Sum all the elements of the row
            for (size_t j = 0; j < width(); j++)
                sum += cell(i, j);

            m[i][0] = sum;
        }

        return cmatrix<T>(m);
    }

    // Compute the sum for each column
    else if (axis == 1)
    {
        // Initialize the result matrix
        std::vector<std::vector<T>> m(1, std::vector<T>(width()));

#pragma omp parallel for
        for (size_t i = 0; i < width(); i++)
        {
            // Initialize the sum to zero
            T sum = zero;

            // Sum all the elements of the column
            for (size_t j = 0; j < height(); j++)
                sum += cell(j, i);

            m[0][i] = sum;
        }

        return cmatrix<T>(m);
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
T cmatrix<T>::sum_all(const T &zero) const
{
    // Initialize the sum to zero
    T sum = zero;

    // Sum all the elements of the matrix
    for (size_t i = 0; i < height(); i++)
        for (size_t j = 0; j < width(); j++)
            sum += cell(i, j);

    return sum;
}

template <typename T>
cmatrix<float> cmatrix<T>::__mean(const unsigned int &axis, std::true_type) const
{
    // Return an empty matrix if the matrix is empty
    if (is_empty())
        return cmatrix<float>();

    // Compute sum of the elements of each row
    cmatrix<float> result(sum(axis));

    // Divide the sum by the dimension of the matrix along the specified axis
    // (rows or columns) to get the mean
    result /= axis == 0 ? width() : height();

    return result;
}

template <typename T>
cmatrix<float> cmatrix<T>::__mean(const unsigned int &axis, std::false_type) const
{
    throw std::invalid_argument("The type of the matrix must be arithmetic.");
}

template <typename T>
cmatrix<float> cmatrix<T>::mean(const unsigned int &axis) const
{
    return __mean(axis, std::is_arithmetic<T>());
}

template <class T>
cmatrix<float> cmatrix<T>::__std(const unsigned int &axis, std::true_type) const
{
    // Compute the standard deviation for each row
    if (axis == 0)
    {
        // Cannot calculate the standard deviation of a single value
        if (width() == 1)
            throw std::invalid_argument("The matrix must have more than one column.");

        // Initialize the result matrix
        std::vector<std::vector<float>> m(height(), std::vector<float>(1));

        // Calculate the mean of each row
        const cmatrix<float> &matrix_mean = mean(0);

#pragma omp parallel for
        for (size_t r = 0; r < height(); r++)
        {
            // Calculate the mean of the row
            const float &mean = matrix_mean.cell(r, 0);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean
            for (size_t c = 0; c < width(); c++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix
            m[r][0] = std::sqrt(sum / width());
        }

        return cmatrix<float>(m);
    }

    // Compute the standard deviation for each column
    else if (axis == 1)
    {
        // Cannot calculate the standard deviation of a single value
        if (height() == 1)
            throw std::invalid_argument("The matrix must have more than one row.");

        // Initialize the result matrix
        std::vector<std::vector<float>> m(1, std::vector<float>(width()));

        // Calculate the mean of each column
        const cmatrix<float> &matrix_mean = this->mean(1);

#pragma omp parallel for
        for (size_t c = 0; c < width(); c++)
        {
            // Calculate the mean of the column
            const float &mean = matrix_mean.cell(0, c);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean
            for (size_t r = 0; r < height(); r++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix
            m[0][c] = std::sqrt(sum / height());
        }

        return cmatrix<float>(m);
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
cmatrix<float> cmatrix<T>::__std(const unsigned int &axis, std::false_type) const
{
    throw std::invalid_argument("The type of the matrix must be arithmetic.");
}

template <class T>
cmatrix<float> cmatrix<T>::std(const unsigned int &axis) const
{
    return __std(axis, std::is_arithmetic<T>());
}

template <class T>
cmatrix<T> cmatrix<T>::median(const unsigned int &axis) const
{
    // Compute the median for each row.
    if (axis == 0)
    {
        // Initialize the result matrix.
        std::vector<std::vector<T>> m(height(), std::vector<T>(1));

#pragma omp parallel for
        for (size_t i = 0; i < height(); i++)
        {
            // Get the row and sort it.
            std::vector<T> row = rows_vec(i);
            std::sort(row.begin(), row.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            m[i][0] = row[row.size() / 2];
        }

        return cmatrix<T>(m);
    }

    // Compute the median for each column.
    else if (axis == 1)
    {
        // Initialize the result matrix.
        std::vector<std::vector<T>> m(1, std::vector<T>(width()));

#pragma omp parallel for
        for (size_t i = 0; i < width(); i++)
        {
            // Get the column and sort it.
            std::vector<T> col = columns_vec(i);
            std::sort(col.begin(), col.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            m[0][i] = col[col.size() / 2];
        }

        return cmatrix<T>(m);
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

#endif // CMATRIX_STATISTICS_TPP
