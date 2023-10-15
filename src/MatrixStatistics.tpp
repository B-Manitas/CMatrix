template <class T>
Matrix<T> Matrix<T>::min(const unsigned int &axis) const
{
    Matrix<T> result;

    if (axis == 0)
    {
        for (size_t i = 0; i < dimV(); i++)
        {
            result.pushRowBack({cell(i, 0)});

            for (size_t j = 0; j < dimH(); j++)
                if (cell(i, j) < result.cell(i, 0))
                    result.cell(0, i) = cell(i, j);
        }

        return result;
    }

    else if (axis == 1)
    {
        for (size_t i = 0; i < dimH(); i++)
        {
            result.pushColBack({cell(0, i)});

            for (size_t j = 0; j < dimV(); j++)
                if (cell(j, i) < result.cell(0, i))
                    result.cell(i, 0) = cell(j, i);
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
Matrix<T> Matrix<T>::max(const unsigned int &axis) const
{
    Matrix<T> result;

    if (axis == 0)
    {
        for (size_t r = 0; r < dimV(); r++)
        {
            result.pushRowBack({cell(r, 0)});

            for (size_t c = 0; c < dimH(); c++)
            {
                T current = cell(r, c);
                T stored = result.cell(r, 0);

                if (current > stored)
                    result.cell(r, 0) = current;
            }
        }

        return result;
    }

    else if (axis == 1)
    {
        for (size_t c = 0; c < dimH(); c++)
        {
            result.pushColBack({cell(0, c)});

            for (size_t r = 0; r < dimV(); r++)
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
Matrix<T> Matrix<T>::sum(const unsigned int &axis, const T &zero) const
{
    Matrix<T> result;

    if (axis == 0)
    {
        for (size_t i = 0; i < dimV(); i++)
        {

            T sum = zero;

            for (size_t j = 0; j < dimH(); j++)
                sum += cell(i, j);

            result.pushRowBack({sum});
        }

        return result;
    }

    else if (axis == 1)
    {
        for (size_t i = 0; i < dimH(); i++)
        {

            T sum = zero;

            for (size_t j = 0; j < dimV(); j++)
                sum += cell(j, i);

            result.pushColBack({sum});
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <typename T>
Matrix<float> Matrix<T>::__mean(const unsigned int &axis, std::true_type) const
{
    if (isEmpty())
        return Matrix<float>();

    Matrix<float> result(sum(axis));
    result /= axis == 0 ? dimH() : dimV();
    return result;
}

template <typename T>
Matrix<float> Matrix<T>::__mean(const unsigned int &axis, std::false_type) const
{
    throw std::invalid_argument("The type of the matrix must be arithmetic.");
}

template <typename T>
Matrix<float> Matrix<T>::mean(const unsigned int &axis) const
{
    return __mean(axis, std::is_arithmetic<T>());
}

template <class T>
Matrix<float> Matrix<T>::__std(const unsigned int &axis, std::true_type) const
{
    Matrix<float> result;

    // Compute the standard deviation for each row.
    if (axis == 0)
    {
        // Cannot calculate the standard deviation of a single value.
        if (dimH() == 1)
            throw std::invalid_argument("The matrix must have more than one column.");

        // Calculate the mean of each row.
        const Matrix<float> &meanMat = this->mean(0);

        for (size_t r = 0; r < dimV(); r++)
        {
            const float &mean = meanMat.cell(r, 0);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean.
            for (size_t c = 0; c < dimH(); c++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix.
            result.pushRowBack({std::sqrt(sum / dimH())});
        }

        return result;
    }

    // Compute the standard deviation for each column.
    else if (axis == 1)
    {
        // Cannot calculate the standard deviation of a single value.
        if (dimV() == 1)
            throw std::invalid_argument("The matrix must have more than one row.");

        // Calculate the mean of each column.
        const Matrix<float> &meanMat = this->mean(1);

        for (size_t c = 0; c < dimH(); c++)
        {
            // Calculate the mean of the column.
            const float &mean = meanMat.cell(0, c);
            float sum = 0;

            // Calculate the sum of the squares of the differences between the values and the mean.
            for (size_t r = 0; r < dimV(); r++)
                sum += std::pow(cell(r, c) - mean, 2);

            // Calculate the standard deviation and push it to the result matrix.
            result.pushColBack({std::sqrt(sum / dimV())});
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
Matrix<float> Matrix<T>::__std(const unsigned int &axis, std::false_type) const
{
    throw std::invalid_argument("The type of the matrix must be arithmetic.");
}

template <class T>
Matrix<float> Matrix<T>::std(const unsigned int &axis) const
{
    return __std(axis, std::is_arithmetic<T>());
}

template <class T>
Matrix<T> Matrix<T>::median(const unsigned int &axis) const
{
    Matrix<T> result;

    // Compute the median for each row.
    if (axis == 0)
    {
        for (size_t i = 0; i < dimV(); i++)
        {
            // Get the row and sort it.
            std::vector<T> row = getRow(i);
            std::sort(row.begin(), row.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            result.pushRowBack({row[row.size() / 2]});
        }

        return result;
    }

    // Compute the median for each column.
    else if (axis == 1)
    {
        for (size_t i = 0; i < dimH(); i++)
        {
            // Get the column and sort it.
            std::vector<T> col = getFlatCol(i);
            std::sort(col.begin(), col.end());

            // Push the median ( middle value -> row.size() / 2 ) to the result matrix.
            result.pushColBack({col[col.size() / 2]});
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}
