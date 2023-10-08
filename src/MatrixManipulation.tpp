/**
 * @file MatrixManipulation.tpp
 * @brief This file contains the implementation of manipulation methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// INSERT FUNCTIONS

template <class T>
void Matrix<T>::insertRow(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the row of any size.
    if (isEmpty())
        checkIdExpected(pos, 0);

    else
    {
        checkIdExpected(pos, 0, dimV());
        checkValidRow(val);
    }

    matrix.insert(matrix.begin() + pos, val);
}

template <class T>
void Matrix<T>::insertCol(const size_t &pos, const std::vector<T> &val)
{
    // If the matrix is empty, we can insert the column of any size.
    if (isEmpty())
    {
        checkIdExpected(pos, 0);

        for (size_t i = 0; i < val.size(); i++)
            matrix.push_back(std::vector<T>{val.at(i)});
    }

    else
    {
        checkIdExpected(pos, 0, dimH());
        checkValidCol(val);

        for (size_t i = 0; i < dimV(); i++)
            matrix.at(i).insert(matrix.at(i).begin() + pos, val.at(i));
    }
}

// ==================================================
// PUSH FUNCTIONS

template <class T>
void Matrix<T>::pushRowFront(const std::vector<T> &val)
{
    insertRow(0, val);
}

template <class T>
void Matrix<T>::pushRowBack(const std::vector<T> &val)
{
    insertRow(dimV(), val);
}

template <class T>
void Matrix<T>::pushColFront(const std::vector<T> &val)
{
    insertCol(0, val);
}

template <class T>
void Matrix<T>::pushColBack(const std::vector<T> &val)
{
    insertCol(dimH(), val);
}

// ==================================================
// FIND FUNCTIONS

template <class T>
int Matrix<T>::findRow(const std::function<bool(std::vector<T>)> &f) const
{
    for (size_t row = 0; row < dimV(); row++)
        if (f(getRow(row)))
            return row;

    return -1;
}

template <class T>
int Matrix<T>::findRow(const std::vector<T> &val) const
{
    return findRow([&](std::vector<T> row)
                   { return row == val; });
}

template <class T>
int Matrix<T>::findCol(const std::function<bool(std::vector<T>)> &f) const
{
    for (size_t col = 0; col < dimH(); col++)
        if (f(getFlatCol(col)))
            return col;

    return -1;
}

template <class T>
int Matrix<T>::findCol(const std::vector<T> &val) const
{
    return findCol([&](std::vector<T> col)
                   { return col == val; });
}

template <class T>
std::vector<T> Matrix<T>::findCellsByCondOnAxis(const unsigned int &axis, const std::function<bool(T, T)> &f) const
{
    std::vector<T> vecOfCell;

    // Find the cell by condition of each row
    if (axis == 0)
    {
        for (size_t r = 0; r < dimV(); r++)
        {
            vecOfCell.push_back(cell(r, 0));

            for (size_t c = 0; c < dimH(); c++)
            {
                const T &current = cell(r, c);

                if (f(current, vecOfCell.at(r)))
                    vecOfCell.at(r) = current;
            }
        }

        return vecOfCell;
    }

    // Find the cell by condition of each column
    else if (axis == 1)
    {
        for (size_t c = 0; c < dimH(); c++)
        {
            vecOfCell.push_back(cell(0, c));

            for (size_t r = 0; r < dimV(); r++)
            {
                const T &current = cell(r, c);

                if (f(current, vecOfCell.at(c)))
                    vecOfCell.at(c) = current;
            }
        }

        return vecOfCell;
    }
    else
        throw std::invalid_argument("The axis must be 0: horizontal, or 1: vertical. Actual: " + std::to_string(axis) + ".");
}

template <class T>
std::tuple<int, int> Matrix<T>::find(const std::function<bool(T)> &f) const
{
    for (size_t row = 0; row < dimV(); row++)
        for (size_t col = 0; col < dimH(); col++)
            if (f(cell(row, col)))
                return std::tuple<int, int>(int(col), int(row));

    return std::tuple<int, int>(-1, -1);
}

template <class T>
std::tuple<int, int> Matrix<T>::find(const T &val) const
{
    return find([&](T e)
                { return e == val; });
}

// ==================================================
// ERASE FUNCTIONS

template <class T>
void Matrix<T>::removeRow(const size_t &pos)
{
    checkIdRow(pos);
    matrix.erase(matrix.begin() + pos);
}

template <class T>
void Matrix<T>::removeCol(const size_t &pos)
{
    checkIdCol(pos);

    if (dimH() == 1)
        matrix.clear();

    else
        for (size_t i = 0; i < dimV(); i++)
            matrix.at(i).erase(matrix.at(i).begin() + pos);
}