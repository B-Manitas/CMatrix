template <class T>
std::vector<T> Matrix<T>::min(const unsigned int &axis) const
{
    return findCellsByCondOnAxis(axis, [&](T current, T prev)
                                 { return current < prev; });
}

template <class T>
std::vector<T> Matrix<T>::max(const unsigned int &axis) const
{
    return findCellsByCondOnAxis(axis, [&](T current, T prev)
                                 { return current > prev; });
}

template <class T>
std::vector<T> Matrix<T>::sum(const unsigned int &axis, const T &zero) const
{
    std::vector<T> result;

    if (axis == 0)
    {
        for (size_t i = 0; i < dimV(); i++)
        {
            const std::vector<T> &row = getRow(i);
            result.push_back(std::accumulate(row.begin(), row.end(), zero));
        }

        return result;
    }

    else if (axis == 1)
    {
        for (size_t i = 0; i < dimH(); i++)
        {
            const std::vector<T> &col = getFlatCol(i);
            result.push_back(std::accumulate(col.begin(), col.end(), zero));
        }

        return result;
    }

    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}
