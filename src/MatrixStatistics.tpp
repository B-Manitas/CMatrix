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
