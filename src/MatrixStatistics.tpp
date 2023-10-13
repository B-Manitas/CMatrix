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
