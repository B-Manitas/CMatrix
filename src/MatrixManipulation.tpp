/**
 * @file MatrixManipulation.tpp
 * @brief This file contains the implementation of manipulation methods of the Matrix class.
 * @see Matrix
 */

// ==================================================
// INSERT FUNCTIONS

template <class T>
void Matrix<T>::insertRow(const int pos, const std::vector<T> val)
{
    if (isEmpty())
    {
        if (pos != 0)
            throw std::invalid_argument("pos must be equal to 0");
    }

    else
    {
        if (val.size() != dimH())
            throw std::invalid_argument("val must be the same length than matrix");

        if (not(0 <= (size_t)pos and (size_t) pos <= dimV()))
            throw std::invalid_argument("pos must be between 0 and dimV");
    }

    matrix.insert(matrix.begin() + pos, val);
}

template <class T>
void Matrix<T>::insertCol(const int pos, const std::vector<T> val)
{
    if (isEmpty())
    {
        if (pos != 0)
            throw std::invalid_argument("pos must be equal to 0");

        for (size_t i = 0; i < val.size(); i++)
            matrix.push_back(std::vector<T>{val.at(i)});
    }

    else
    {
        if (val.size() != dimV())
            throw std::invalid_argument("val must be the same length than matrix");

        if (not(0 <= (size_t)pos and (size_t) pos <= dimH()))
            throw std::invalid_argument("pos must be between 0 and dimH");

        for (size_t i = 0; i < dimV(); i++)
            matrix.at(i).insert(matrix.at(i).begin() + pos, val.at(i));
    }
}

// ==================================================
// PUSH FUNCTIONS

template <class T>
void Matrix<T>::pushRowFront(const std::vector<T> val)
{
    insertRow(0, val);
}

template <class T>
void Matrix<T>::pushRowBack(const std::vector<T> val)
{
    insertRow(dimV(), val);
}

template <class T>
void Matrix<T>::pushColFront(const std::vector<T> val)
{
    insertCol(0, val);
}

template <class T>
void Matrix<T>::pushColBack(const std::vector<T> val)
{
    insertCol(dimH(), val);
}

// ==================================================
// FIND FUNCTIONS

template <class T>
int Matrix<T>::findRow(const std::vector<T> val) const
{
    if (val.size() != dimH())
        throw std::invalid_argument("val must be the same length than matrix");

    for (size_t row = 0; row < dimV(); row++)
        if (getRow(row) == val)
            return row;

    return -1;
}

template <class T>
int Matrix<T>::findCol(const std::vector<T> val) const
{
    if (val.size() != dimV())
        throw std::invalid_argument("val must be the same length than matrix");

    for (size_t col = 0; col < dimH(); col++)
        if (flattenVector(getCol(col)) == val)
            return col;

    return -1;
}

template <class T>
std::tuple<int, int> Matrix<T>::find(const T val) const
{

    for (size_t row = 0; row < dimV(); row++)
        for (size_t col = 0; col < dimH(); col++)
            if (getCell(col, row) == val)
                return std::tuple<int, int>(int(col), int(row));

    return std::tuple<int, int>(-1, -1);
}
