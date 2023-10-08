#pragma once

#include <vector>
#include <tuple>
#include <iostream>
#include <functional>
#include <numeric>

/**
 * @brief Matrix class.
 *
 * @tparam T The type of elements in the Matrix.
 */
template <class T>
class Matrix
{
private:
    std::vector<std::vector<T>> matrix = std::vector<std::vector<T>>();

public:
    // CONSTRUCTOR METHODS
    /**
     * @brief Construct a new Matrix object.
     *
     * @param m The matrix to copy.
     */
    Matrix(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief Construct a new Matrix object.
     */
    Matrix();
    /**
     * @brief Construct a new Matrix object.
     *
     * @param dimH The number of columns.
     * @param dimV The number of rows.
     */
    Matrix(const size_t &dimH, const size_t &dimV);
    /**
     * @brief Construct a new Matrix object.
     *
     * @param dimH The number of columns.
     * @param dimV The number of rows.
     * @param val The value to fill the matrix.
     */
    Matrix(const size_t &dimH, const size_t &dimV, const T &val);
    ~Matrix();

    // GETTER METHODS
    /**
     * @brief Get a row of the matrix.
     *
     * @param n The index of the row to get.
     * @return std::vector<T> The row.
     * @throw std::out_of_range If the index is out of range.
     * @deprecated Use `rows` instead.
     */
    std::vector<T> getRow(const size_t &n) const;
    /**
     * @brief Get a column of the matrix.
     *
     * @param n The index of the column to get.
     * @return std::vector<T> The column.
     * @throw std::out_of_range If the index is out of range.
     * @deprecated Use `columns` instead.
     */
    std::vector<std::vector<T>> getCol(const size_t &n) const;
    /**
     * @brief Get a column of the matrix as a flattened vector.
     *
     * @param n The index of the column to get.
     * @return std::vector<T> The column as a flattened vector.
     * @throw std::out_of_range If the index is out of range.
     * @deprecated Use `columns` instead.
     */
    std::vector<T> getFlatCol(const size_t &n) const;

    /**
     * @brief Get the rows of the matrix.
     *
     * @param ids The indexes of the rows to get.
     * @return Matrix<T> The rows of the matrix.
     * @throw std::out_of_range If the index is out of range.
     */
    Matrix<T> rows(const std::initializer_list<size_t> ids) const;
    /**
     * @brief Get the columns of the matrix.
     *
     * @param ids The indexes of the columns to get.
     * @return Matrix<T> The columns of the matrix.
     * @throw std::out_of_range If the index is out of range.
     */
    Matrix<T> columns(const std::initializer_list<size_t> ids) const;
    /**
     * @brief Get the cells of the matrix.
     *
     * @param ids The indexes of the cells to get. (row, column)
     * @return Matrix<T> The cells of the matrix.
     * @throw std::out_of_range If the index is out of range.
     */
    Matrix<T> cells(const std::initializer_list<std::pair<size_t, size_t>> ids) const;
    /**
     * @brief Get a cell of the matrix.
     * 
     * @param row The row of the cell to get.
     * @param col The column of the cell to get.
     * @return T The cell.
     * @throw std::out_of_range If the index is out of range.
     */
    T cell(const size_t &row, const size_t &col) const;

    /**
     * @brief The number of columns of the matrix.
     *
     * @return size_t The number of columns.
     */
    size_t dimH() const;
    /**
     * @brief The number of rows of the matrix.
     *
     * @return size_t The number of rows.
     */
    size_t dimV() const;
    /**
     * @brief The dimensions of the matrix.
     *
     * @return std::tuple<size_t, size_t> The number of rows and columns.
     */
    std::tuple<size_t, size_t> dim() const;

    /**
     * @brief Get the transpose of the matrix.
     *
     * @return Matrix<T> The transpose of the matrix.
     */
    Matrix<T> transpose() const;
    /**
     * @brief Get the diagonal of the matrix.
     *
     * @return std::vector<T> The diagonal of the matrix.
     */
    std::vector<T> diag() const;
    // SETTER METHODS
    /**
     * @brief Set a row of the matrix.
     *
     * @param n The index of the row to set.
     * @param val The value to set.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    void setRow(const size_t &n, const std::vector<T> &val);
    /**
     * @brief Set a column of the matrix.
     *
     * @param n The index of the column to set.
     * @param val The value to set.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    void setCol(const size_t &n, const std::vector<T> &val);
    /**
     * @brief Set a cell of the matrix.
     *
     * @param col The column of the cell to set.
     * @param row The row of the cell to set.
     * @param val The value to set.
     * @throw std::out_of_range If the index is out of range.
     *
     * @note The cell must be of the same type of the matrix.
     */
    void setCell(const size_t &col, const size_t &row, const T &val);
    /**
     * @brief Set the diagonal of the matrix.
     *
     * @param val The diagonal to set.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the minimum of the number of rows and columns of the matrix.
     *
     * @note The diagonal must be a vector of the same type of the matrix.
     */
    void setDiag(const std::vector<T> &val);

    // MANIPULATION METHODS
    /**
     * @brief Insert a column in the matrix.
     *
     * @param pos The index of the column to insert.
     * @param val The value to insert.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    void insertRow(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Insert a row in the matrix.
     *
     * @param pos The index of the row to insert.
     * @param val The value to insert.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    void insertCol(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Push a row in the front of the matrix.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    void pushRowFront(const std::vector<T> &val);
    /**
     * @brief Push a row in the back of the matrix.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    void pushRowBack(const std::vector<T> &val);

    /**
     * @brief Push a column in the front of the matrix.
     *
     * @param val The column to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    void pushColFront(const std::vector<T> &val);
    /**
     * @brief Push a column in the back of the matrix.
     *
     * @param val The column to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    void pushColBack(const std::vector<T> &val);

    /**
     * @bried Find the first row matching the condition.
     *
     * @param f The condition to satisfy. f(std::vector<T> row) -> bool
     * @return int The first index of the row. -1 if not found.
     *
     * @note The empty matrix always return -1.
     */
    int findRow(const std::function<bool(std::vector<T>)> &f) const;
    /**
     * @brief Find the first row matching the given row.
     *
     * @param val The row to find.
     * @return int The first index of the row. -1 if not found.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    int findRow(const std::vector<T> &val) const;
    /**
     * @brief Find the first column matching the condition.
     *
     * @param f The condition to satisfy. f(std::vector<T> col) -> bool
     * @return int The first index of the column. -1 if not found.
     *
     * @note The empty matrix always return -1.
     */
    int findCol(const std::function<bool(std::vector<T>)> &f) const;
    /**
     * @brief Find the first column matching the given column.
     *
     * @param val The column to find.
     * @return int The first index of the row. -1 if not found.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    int findCol(const std::vector<T> &val) const;
    /**
     * @brief Find the cell matching the condition on an axis (0: rows, 1: columns).
     *
     * @param axis The axis to find the cells. 0 for the rows, 1 for the columns.
     * @param f The condition to satisfy. f(T current, T prev) -> bool
     * @return std::vector<T> The cells matching the condition.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     */
    std::vector<T> findCellsByCondOnAxis(const unsigned int &axis, const std::function<bool(T, T)> &f) const;
    /**
     * @brief Find the first cell matching the condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return std::tuple<int, int> The first index of the cell. (-1, -1) if not found.
     *
     * @note The empty matrix always return (-1, -1).
     */
    std::tuple<int, int> find(const std::function<bool(T)> &f) const;
    /**
     * @brief Find the first cell matching the given cell.
     *
     * @param val The cell to find.
     * @return std::tuple<int, int> The first index of the cell. (-1, -1) if not found.
     *
     * @note The cell must be of the same type of the matrix.
     */
    std::tuple<int, int> find(const T &val) const;

    /**
     * @brief Remove a row of the matrix.
     *
     * @param n The index of the row to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     */
    void removeRow(const size_t &n);
    /**
     * @brief Remove a column of the matrix.
     *
     * @param n The index of the column to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     */
    void removeCol(const size_t &n);

    // CHECK METHODS
    /**
     * @brief Check if the matrix is empty.
     *
     * @return true If the matrix is empty.
     * @return false If the matrix is not empty.
     */
    bool isEmpty() const;
    /**
     * @brief Check if the matrix is a square matrix.
     *
     * @return true If the matrix is a square matrix.
     * @return false If the matrix is not a square matrix.
     */
    bool isSquare() const;
    /**
     * @brief Check if the matrix is a diagonal matrix.
     *
     * @return true If the matrix is a diagonal matrix.
     * @return false If the matrix is not a diagonal matrix.
     */
    bool isDiagonal() const;
    /**
     * @brief Check if the matrix is the identity matrix.
     *
     * @return true If the matrix is the identity matrix.
     * @return false If the matrix is not the identity matrix.
     */
    bool isIdentity() const;
    /**
     * @brief Check if the matrix is a symmetric matrix.
     *
     * @return true If the matrix is a symmetric matrix.
     * @return false If the matrix is not a symmetric matrix.
     */
    bool isSymmetric() const;
    /**
     * @brief Check if the matrix is an upper triangular matrix.
     *
     * @return true If the matrix is an upper triangular matrix.
     * @return false If the matrix is not an upper triangular matrix.
     */
    bool isUpperTriangular() const;
    /**
     * @brief Check if the matrix is a lower triangular matrix.
     *
     * @return true If the matrix is a lower triangular matrix.
     * @return false If the matrix is not a lower triangular matrix.
     */
    bool isLowerTriangular() const;
    /**
     * @brief Check if all the cells of the matrix satisfy a condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return true If all the cells satisfy the condition.
     * @return false If at least one cell does not satisfy the condition.
     *
     * @note The empty matrix always return true.
     */
    bool isAll(const std::function<bool(T)> &f) const;
    /**
     * @brief Check if all the cells of the matrix are equal to a value.
     *
     * @param val The value to check.
     * @return true If all the cells are equal to the value.
     * @return false If at least one cell is not equal to the value.
     *
     * @note The empty matrix always return true.
     */
    bool isAll(const T &val) const;
    /**
     * @brief Check if at least one cell of the matrix satisfy a condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return true If at least one cell satisfy the condition.
     * @return false If all the cells does not satisfy the condition.
     *
     * @note The empty matrix always return false.
     */
    bool isAny(const std::function<bool(T)> &f) const;
    /**
     * @brief Check if at least one cell of the matrix is equal to a value.
     *
     * @param val The value to check.
     * @return true If at least one cell is equal to the value.
     * @return false If all the cells are not equal to the value.
     *
     * @note The empty matrix always return false.
     */
    bool isAny(const T &val) const;

    /**
     * @brief Check if dimensions are equals to the dimensions of the matrix.
     *
     * @param dim The vertical and horizontal dimensions.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     */
    void checkDim(const std::tuple<size_t, size_t> &dim) const;
    /**
     * @brief Check if dimensions are equals to the dimensions of the matrix.
     *
     * @param m The matrix.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     */
    void checkDim(const Matrix<T> &m) const;
    /**
     * @brief Check if the vector is a valid row of the matrix.
     *
     * @param row The row to check.
     * @throw std::invalid_argument If the vector is not a valid row of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     */
    void checkValidRow(const std::vector<T> &row) const;
    /**
     * @brief Check if the vector is a valid column of the matrix.

     * @param col The column to check.
     * @throw std::invalid_argument If the vector is not a valid column of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     */
    void checkValidCol(const std::vector<T> &col) const;
    /**
     * @brief Check if the diagonal is a valid diagonal of the matrix.
     *
     * @param diag The diagonal to check.
     * @throw std::invalid_argument If the vector is not a valid diagonal of the matrix.
     */
    void checkValidDiag(const std::vector<T> &diag) const;
    /**
     * @brief Check if the row is a valid row index of the matrix.
     *
     * @param row The row index to check.
     * @throw std::invalid_argument If the row is not a valid row index of the matrix.
     */
    void checkIdRow(const size_t &n) const;
    /**
     * @brief Check if the column is a valid column index of the matrix.
     *
     * @param col The column index to check.
     * @throw std::invalid_argument If the column is not a valid column index of the matrix.
     */
    void checkIdCol(const size_t &n) const;
    /**
     * @brief Check if the index is expected.
     *
     * @param n The index to check.
     * @param expected The expected index.
     * @throw std::invalid_argument If the index is not the expected index.
     */
    void checkIdExpected(const size_t &n, const size_t &expected) const;
    /**
     * @brief Check if the index is expected.
     *
     * @param n The index to check.
     * @param expectedBegin The expected begin index inclusive.
     * @param exepectedEnd The expected end index inlusive.
     * @throw std::invalid_argument If the index is not the expected index.
     */
    void checkIdExpected(const size_t &n, const size_t &expectedBegin, const size_t &exepectedEnd) const;

    // STATISTICS METHODS
    /**
     * @brief Get the minimum value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the minimum value. 0 for the rows, 1 for the columns. (default: 0)
     * @return T The minimum value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note The type of the matrix must implement the operator <.
     */
    std::vector<T> min(const unsigned int &axis = 0) const;
    /**
     * @brief Get the maximum value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the maximum value. 0 for the rows, 1 for the columns. (default: 0)
     * @return T The maximum value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note The type of the matrix must implement the operator >.
     */
    std::vector<T> max(const unsigned int &axis = 0) const;
    /**
    /**
     * @brief Get the sum of the matrix for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the sum. 0 for the rows, 1 for the columns. (default: 0)
     * @param zero The zero value of the sum. (default: the value of the default constructor of the type T)
     * @return T The sum of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     */
    std::vector<T> sum(const unsigned int &axis = 0, const T &zero = T()) const;
    // OTHER METHODS
    /**
     * @brief Print the matrix in the standard output.
     */
    void print() const;
    /**
     * @brief Clear the matrix.
     */
    void clear();
    /**
     * @brief Copy the matrix.
     *
     * @return Matrix<T> The copied matrix.
     */
    Matrix<T> copy() const;
    /**
     * @brief Apply a function to each cell of the matrix.
     *
     * @param f The function to apply. f(T value, size_t *id_col, size_t *id_row) -> T
     * @param col The pointer to the column index. (default: nullptr)
     * @param row The pointer to the row index. (default: nullptr)
     */
    void apply(const std::function<T(T, size_t *, size_t *)> &f, size_t *col = nullptr, size_t *row = nullptr);
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @param f The function to apply. f(T value, size_t *id_col, size_t *id_row) -> T
     * @param col The pointer to the column index. (default: nullptr)
     * @param row The pointer to the row index. (default: nullptr)
     * @return Matrix<T> The result of the function.
     */
    Matrix<T> map(const std::function<T(T, size_t *, size_t *)> &f, size_t *col = nullptr, size_t *row = nullptr) const;
    /**
     * @brief Fill the matrix with a value.
     *
     * @param val The value to fill the matrix.
     */
    void fill(const T &val);

    // STATIC METHODS
    /**
     * @brief Check if a nested vector is a matrix. To be a matrix, all the rows and columns must have the same length.
     *
     * @param m The nested vector to check.
     * @return true If the nested vector is a matrix.
     * @return false If the nested vector is not a matrix.
     */
    static bool isMatrix(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief Flatten a nested vector.
     *
     * @param vec The nested vector to flatten.
     * @return std::vector<T> The flattened vector.
     */
    static std::vector<T> flattenVector(const std::vector<std::vector<T>> &vec);
    /**
     * @brief Generate a random matrix of integers.
     *
     * @param dimH The number of rows.
     * @param dimV The number of columns.
     * @param min The minimum value of the matrix.
     * @param max The maximum value of the matrix.
     * @param seed The seed of the random generator. (default: time(nullptr))
     *
     * @return Matrix<int> The random matrix of integers.
     */
    static Matrix<int> randint(const size_t &dimH, const size_t &dimV, const int &min, const int &max, const int &seed = time(nullptr));
    /**
     * @brief Generate a matrix of zeros.
     *
     * @param dimH The number of columns.
     * @param dimV The number of rows.
     * @return Matrix<int> The matrix of zeros.
     */
    static Matrix<int> zeros(const size_t &dimH, const size_t &dimV);
    /**
     * @brief Generate the identity matrix.
     *
     * @param dim The number of rows and columns.
     * @return Matrix<int> The identity matrix.
     *
     */
    static Matrix<int> identity(const size_t &dim);

    // OPERATOR METHODS
    /**
     * @brief The assignment operator.
     *
     * @param m The matrix to copy.
     * @return Matrix<T>& The copied matrix.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> &operator=(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief The assignment operator.
     *
     * @param m The matrix to copy.
     * @return Matrix<T>& The copied matrix.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> &operator=(const Matrix<T> &m);
    /**
     * @brief The equality operator.
     *
     * @param m The matrix to compare.
     * @return true If the matrices are equal.
     * @return false If the matrices are not equal.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    bool operator==(const Matrix<T> &m) const;
    /**
     * @brief The inequality operator.
     *
     * @param m The matrix to compare.
     * @return true If the matrices are not equal.
     * @return false If the matrices are equal.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    bool operator!=(const Matrix<T> &m) const;
    /**
     * @brief The output operator.
     *
     * @param out The output stream.
     * @param m The matrix to print.
     * @return std::ostream& The output stream.
     */
    template <class U>
    friend std::ostream &operator<<(std::ostream &out, const Matrix<U> &m);
    /**
     * @brief The addition operator.
     *
     * @param m The matrix to add.
     * @return Matrix<T> The sum of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> operator+(const Matrix<T> &m) const;
    /**
     * @brief The subtraction operator.
     *
     * @param m The matrix to subtract.
     * @return Matrix<T> The difference of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> operator-(const Matrix<T> &m) const;
    /**
     * @brief The multiplication operator.
     *
     * @param m The matrix to multiply.
     * @return Matrix<T> The product of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> operator*(const Matrix<T> &m) const;
    /**
     * @brief The power operator.
     *
     * @param m The power. Must be a positive integer.
     * @return Matrix<T> The powered matrix.
     * @throw std::invalid_argument If the matrix is not a square matrix.
     */
    Matrix<T> operator^(const unsigned int &m) const;
    /**
     * @brief The addition assignment operator.
     *
     * @param m The matrix to add.
     * @return Matrix<T>& The sum of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> &operator+=(const Matrix<T> &m);
    /**
     * @brief The subtraction assignment operator.
     *
     * @param m The matrix to subtract.
     * @return Matrix<T>& The difference of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> &operator-=(const Matrix<T> &m);
    /**
     * @brief The multiplication assignment operator.
     *
     * @param m The matrix to multiply.
     * @return Matrix<T>& The product of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     */
    Matrix<T> &operator*=(const Matrix<T> &m);
    /**
     * @brief The power assignment operator.
     *
     * @param m The power. Must be a positive integer.
     * @return Matrix<T>& The powered matrix.
     * @throw std::invalid_argument If the matrix is not a square matrix.
     */
    Matrix<T> &operator^=(const unsigned int &m);
    /**
     * @brief Apply a operator to each cell of the matrix.
     *
     * @param f The operator to apply. f(T value, T value) -> T
     * @param m The matrix to apply.
     * @return Matrix<T> The result of the operator.
     */
    Matrix<T> operatorMap(const std::function<T(T, T)> &f, const Matrix<T> &m) const;
};

#include "Matrix.tpp"
#include "MatrixCheck.tpp"
#include "MatrixConstructor.tpp"
#include "MatrixGetter.tpp"
#include "MatrixManipulation.tpp"
#include "MatrixOperator.tpp"
#include "MatrixSetter.tpp"
#include "MatrixStatic.tpp"
#include "MatrixStatistics.tpp"
