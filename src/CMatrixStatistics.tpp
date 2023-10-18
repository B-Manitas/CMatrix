/**
 * @file CMatrixStatistics.tpp
 * @brief This file contains the implementation of methods to perform statistical operations on the matrix.
 *
 * @see cmatrix
 */

template <class T>
cmatrix<T> cmatrix<T>::min(const unsigned int &axis) const
{
    cmatrix<T> result;

    // Compute the minimum for each row
    if (axis == 0)
    {
        for (size_t r = 0; r < dim_v(); r++)
        {
            // Push the first element of the row to the result matrix
            result.push_row_back({cell(r, 0)});

            // Check if the current element is smaller than the stored one
            for (size_t c = 0; c < dim_h(); c++)
                if (cell(r, c) < result.cell(r, 0))
                    result.cell(0, r) = cell(r, c);
        }

        return result;
    }

    // Compute the minimum for each column
    else if (axis == 1)
    {
        for (size_t i = 0; i < dim_h(); i++)
        {
            // Push the first element of the column to the result matrix
            result.push_col_back({cell(0, i)});

            // Check if the current element is smaller than the stored one
            for (size_t j = 0; j < dim_v(); j++)
                if (cell(j, i) < result.cell(0, i))
                    result.cell(i, 0) = cell(j, i);
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
cmatrix<T> cmatrix<T>::max(const unsigned int &axis) const
{
    cmatrix<T> result;

    // Compute the maximum for each row
    if (axis == 0)
    {
        for (size_t r = 0; r < dim_v(); r++)
        {
            // Push the first element of the row to the result matrix
            result.push_row_back({cell(r, 0)});

            // Check if the current element is greater than the stored one
            for (size_t c = 0; c < dim_h(); c++)
            {
                T current = cell(r, c);
                T stored = result.cell(r, 0);

                if (current > stored)
                    result.cell(r, 0) = current;
            }
        }

        return result;
    }

    // Compute the maximum for each column
    else if (axis == 1)
    {
        for (size_t c = 0; c < dim_h(); c++)
        {
            // Push the first element of the column to the result matrix
            result.push_col_back({cell(0, c)});

            // Check if the current element is greater than the stored one
            for (size_t r = 0; r < dim_v(); r++)
            {
                T current = cell(r, c);
                T stored = result.cell(0, c);

                if (current > stored)
                    result.cell(0, c) = current;
            }
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
cmatrix<T> cmatrix<T>::sum(const unsigned int &axis, const T &zero) const
{
    cmatrix<T> result;

    // Compute the sum for each row
    if (axis == 0)
    {
        for (size_t i = 0; i < dim_v(); i++)
        {
            // Initialize the sum to zero
            T sum = zero;

            // Sum all the elements of the row
            for (size_t j = 0; j < dim_h(); j++)
                sum += cell(i, j);

            result.push_row_back({sum});
        }

        return result;
    }

    // Compute the sum for each column
    else if (axis == 1)
    {
        for (size_t i = 0; i < dim_h(); i++)
        {
            // Initialize the sum to zero
            T sum = zero;

            // Sum all the elements of the column
            for (size_t j = 0; j < dim_v(); j++)
                sum += cell(j, i);

            result.push_col_back({sum});
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
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
    result /= axis == 0 ? dim_h() : dim_v();

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
    cmatrix<float> result;

    // Compute the standard deviation for each row
    if (axis == 0)
    {
        // Cannot calculate the standard deviation of a single value
        if (dim_h() == 1)
            throw std::invalid_argument("The matrix must have more than one column.");

        // Calculate the mean of each row
        const cmatrix<float> &matrix_mean = this->mean(0);

        for (size_t r = 0; r < dim_v(); r++)
        {
            // Calculate the mean of the row
            const float &mean = matrix_mean.cell(r, 0);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean
            for (size_t c = 0; c < dim_h(); c++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix
            result.push_row_back({std::sqrt(sum / dim_h())});
        }

        return result;
    }

    // Compute the standard deviation for each column
    else if (axis == 1)
    {
        // Cannot calculate the standard deviation of a single value
        if (dim_v() == 1)
            throw std::invalid_argument("The matrix must have more than one row.");

        // Calculate the mean of each column
        const cmatrix<float> &matrix_mean = this->mean(1);

        for (size_t c = 0; c < dim_h(); c++)
        {
            // Calculate the mean of the column
            const float &mean = matrix_mean.cell(0, c);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean
            for (size_t r = 0; r < dim_v(); r++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix
            result.push_col_back({std::sqrt(sum / dim_v())});
        }

        return result;
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
    cmatrix<T> result;

    // Compute the median for each row.
    if (axis == 0)
    {
        for (size_t i = 0; i < dim_v(); i++)
        {
            // Get the row and sort it.
            std::vector<T> row = rows_vec(i);
            std::sort(row.begin(), row.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            result.push_row_back({row[row.size() / 2]});
        }

        return result;
    }

    // Compute the median for each column.
    else if (axis == 1)
    {
        for (size_t i = 0; i < dim_h(); i++)
        {
            // Get the column and sort it.
            std::vector<T> col = columns_vec(i);
            std::sort(col.begin(), col.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            result.push_col_back({col[col.size() / 2]});
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}
