/**
 * @file CMatrix.hpp
 * @brief File containing the main template class of the 'cmatrix' library.
 *
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

/**
 * @brief The main template class that can work with any data type except bool.
 *
 * @tparam T The type of elements in the cmatrix.
 */
template <class T>
class cmatrix
{
private:
    std::vector<std::vector<T>> matrix = std::vector<std::vector<T>>();

    // CHECK METHODS
    /**
     * @brief Check if dimensions are equals to the dimensions of the matrix.
     *
     * @param dim The vertical and horizontal dimensions.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     *
     * @ingroup check
     */
    void __check_dim(const std::tuple<size_t, size_t> &dim) const;
    /**
     * @brief Check if dimensions are equals to the dimensions of the matrix.
     *
     * @param m The matrix.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     *
     * @ingroup check
     */
    void __check_dim(const cmatrix<T> &m) const;
    /**
     * @brief Check if the vector is a valid row of the matrix.
     *
     * @param row The row to check.
     * @throw std::invalid_argument If the vector is not a valid row of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     * @ingroup check
     */
    void __check_valid_row(const std::vector<T> &row) const;
    /**
     * @brief Check if the vector is a valid column of the matrix.

     * @param col The column to check.
     * @throw std::invalid_argument If the vector is not a valid column of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup check
     */
    void __check_valid_col(const std::vector<T> &col) const;
    /**
     * @brief Check if the diagonal is a valid diagonal of the matrix.
     *
     * @param diag The diagonal to check.
     * @throw std::invalid_argument If the vector is not a valid diagonal of the matrix.
     *
     * @ingroup check
     */
    void __check_valid_diag(const std::vector<T> &diag) const;
    /**
     * @brief Check if the row is a valid row index of the matrix.
     *
     * @param row The row index to check.
     * @throw std::invalid_argument If the row is not a valid row index of the matrix.
     *
     * @ingroup check
     */
    void __check_valid_row_id(const size_t &n) const;
    /**
     * @brief Check if the column is a valid column index of the matrix.
     *
     * @param col The column index to check.
     * @throw std::invalid_argument If the column is not a valid column index of the matrix.
     *
     * @ingroup check
     */
    void __check_valid_col_id(const size_t &n) const;
    /**
     * @brief Check if the index is expected.
     *
     * @param n The index to check.
     * @param expected The expected index.
     * @throw std::invalid_argument If the index is not the expected index.
     *
     * @ingroup check
     */
    void __check_expected_id(const size_t &n, const size_t &expected) const;
    /**
     * @brief Check if the index is expected.
     *
     * @param n The index to check.
     * @param expectedBegin The expected begin index inclusive.
     * @param exepectedEnd The expected end index inlusive.
     * @throw std::invalid_argument If the index is not the expected index.
     *
     * @ingroup check
     */
    void __check_expected_id(const size_t &n, const size_t &expectedBegin, const size_t &exepectedEnd) const;
    /**
     * @brief Check if the type of the matrix is valid.
     * List of types not supported: bool.
     *
     * @throw std::invalid_argument If the type is invalid.
     *
     * @ingroup check
     */
    void __check_valid_type() const;

    // STATISTIC METHODS
    /**
     * @brief Compute the mean value for each row (axis: 0) or column (axis: 1) of the matrix.
     * This method is used when the type of the matrix is arithmetic.
     *
     * @param axis The axis to get the mean value. 0 for the rows, 1 for the columns. (default: 0)
     * @param true_type The type of the matrix is arithmetic.
     * @return cmatrix<float> The mean value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @ingroup statistic
     */
    cmatrix<float> __mean(const unsigned int &axis, std::true_type) const;
    /**
     * @brief Compute the mean value for each row (axis: 0) or column (axis: 1) of the matrix.
     * This method is used when the type of the matrix is not arithmetic.
     *
     * @param axis The axis to get the mean value. 0 for the rows, 1 for the columns. (default: 0)
     * @param false_type The type of the matrix is not arithmetic.
     * @throw std::invalid_argument If the matrix is not arithmetic.
     *
     * @ingroup statistic
     *
     */
    cmatrix<float> __mean(const unsigned int &axis, std::false_type) const;
    /**
     * @brief Compute the std value for each row (axis: 0) or column (axis: 1) of the matrix.
     * This method is used when the type of the matrix is arithmetic.
     *
     * @param axis The axis to get the std value. 0 for the rows, 1 for the columns. (default: 0)
     * @param true_type The type of the matrix is arithmetic.
     * @return cmatrix<float> The std value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @ingroup statistic
     */
    cmatrix<float> __std(const unsigned int &axis, std::true_type) const;
    /**
     * @brief Compute the std value for each row (axis: 0) or column (axis: 1) of the matrix.
     * This method is used when the type of the matrix is not arithmetic.
     *
     * @param axis The axis to get the std value. 0 for the rows, 1 for the columns. (default: 0)
     * @param false_type The type of the matrix is not arithmetic.
     * @throw std::invalid_argument If the matrix is not arithmetic.
     *
     * @ingroup statistic
     */
    cmatrix<float> __std(const unsigned int &axis, std::false_type) const;
    /**
     * @brief Apply a operator to each cell of the matrix.
     *
     * @param f The operator to apply. f(T value, T value) -> T
     * @param m The matrix to apply.
     * @return cmatrix<T> The result of the operator.
     *
     * @ingroup operator
     */
    cmatrix<T> __map_op_arithmetic(const std::function<T(T, T)> &f, const cmatrix<T> &m) const;
    /**
     * @brief Map a comparison operator to each cell of the matrix and return a matrix of boolean.
     *
     * @param f The comparison operator to apply. f(T value, T value) -> bool
     * @param n The number to compare.
     * @return cmatrix<short unsigned int> The result of the comparison.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> __map_op_comparaison_val(const std::function<T(T, T)> &f, const T &n) const;

public:
    // CONSTRUCTOR METHODS
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param m The matrix to copy.
     * @throw std::invalid_argument If the initializer list is not a matrix.
     * @throw std::invalid_argument If the type is bool.
     */
    cmatrix(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief Construct a new cmatrix object.
     *
     * @throw std::invalid_argument If the type is bool.
     */
    cmatrix();
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param dim_v The number of rows.
     * @param dim_h The number of columns.
     * @throw std::invalid_argument If the type is bool.
     */
    cmatrix(const size_t &dim_v, const size_t &dim_h);
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param dim_v The number of rows.
     * @param dim_h The number of columns.
     * @param val The value to fill the matrix.
     * @throw std::invalid_argument If the type is bool.
     */
    cmatrix(const size_t &dim_v, const size_t &dim_h, const T &val);
    /**
     * @brief Cast a matrix to another type.
     *
     * @param m The matrix to copy.
     * @tparam U The type of the matrix to copy.
     * @throw std::invalid_argument If the type is bool.
     */
    template <class U>
    cmatrix(const cmatrix<U> &m);
    ~cmatrix();

    // GETTER METHODS
    /**
     * @brief Get a row of the matrix.
     *
     * @param n The index of the row to get.
     * @return std::vector<T> The row.
     * @throw std::out_of_range If the index is out of range.
     * @deprecated Use `rows` instead.
     *
     * @ingroup getter
     */
    std::vector<T> rows_vec(const size_t &n) const;
    /**
     * @brief Get a column of the matrix as a flattened vector.
     *
     * @param n The index of the column to get.
     * @return std::vector<T> The column as a flattened vector.
     * @throw std::out_of_range If the index is out of range.
     * @deprecated Use `columns` instead.
     *
     * @ingroup getter
     */
    std::vector<T> columns_vec(const size_t &n) const;

    /**
     * @brief Get the rows of the matrix.
     *
     * @param ids The indexes of the rows to get.
     * @return cmatrix<T> The rows of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const size_t &ids) const;
    /**
     * @brief Get the rows of the matrix.
     *
     * @param ids The indexes of the rows to get.
     * @return cmatrix<T> The rows of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const std::initializer_list<size_t> &ids) const;
    /**
     * @brief Get the rows of the matrix.
     *
     * @param ids The indexes of the rows to get.
     * @return cmatrix<T> The rows of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> rows(const std::vector<size_t> &ids) const;
    /**
     * @brief Get the columns of the matrix.
     *
     * @param ids The indexes of the columns to get.
     * @return cmatrix<T> The columns of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const size_t &ids) const;
    /**
     * @brief Get the columns of the matrix.
     *
     * @param ids The indexes of the columns to get.
     * @return cmatrix<T> The columns of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const std::initializer_list<size_t> &ids) const;
    /**
     * @brief Get the columns of the matrix.
     *
     * @param ids The indexes of the columns to get.
     * @return cmatrix<T> The columns of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> columns(const std::vector<size_t> &ids) const;
    /**
     * @brief Get the cells of the matrix.
     *
     * @param row The row of the cell to get.
     * @param col The column of the cell to get.
     * @return cmatrix<T> The cells of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> cells(const size_t &row, const size_t &col) const;
    /**
     * @brief Get the cells of the matrix.
     *
     * @param ids The indexes of the cells to get. (row, column)
     * @return cmatrix<T> The cells of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> cells(const std::initializer_list<std::pair<size_t, size_t>> &ids) const;
    /**
     * @brief Get the cells of the matrix.
     *
     * @param ids The indexes of the cells to get. (row, column)
     * @return cmatrix<T> The cells of the matrix.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    cmatrix<T> cells(const std::vector<std::pair<size_t, size_t>> &ids) const;
    /**
     * @brief Get the reference to a cell of the matrix.
     *
     * @param row The row of the cell to get.
     * @param col The column of the cell to get.
     * @return T The reference of the cell.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    T &cell(const size_t &row, const size_t &col);
    /**
     * @brief Get a cell of the matrix.
     *
     * @param row The row of the cell to get.
     * @param col The column of the cell to get.
     * @return T The cell.
     * @throw std::out_of_range If the index is out of range.
     *
     * @ingroup getter
     */
    T cell(const size_t &row, const size_t &col) const;

    /**
     * @brief The number of columns of the matrix.
     *
     * @return size_t The number of columns.
     *
     * @ingroup getter
     */
    size_t dim_h() const;
    /**
     * @brief The number of rows of the matrix.
     *
     * @return size_t The number of rows.
     *
     * @ingroup getter
     */
    size_t dim_v() const;
    /**
     * @brief The dimensions of the matrix.
     *
     * @return std::pair<size_t, size_t> The number of rows and columns.
     *
     * @ingroup getter
     */
    std::pair<size_t, size_t> dim() const;

    /**
     * @brief Get the transpose of the matrix.
     *
     * @return cmatrix<T> The transpose of the matrix.
     *
     * @ingroup getter
     */
    cmatrix<T> transpose() const;
    /**
     * @brief Get the diagonal of the matrix.
     *
     * @return std::vector<T> The diagonal of the matrix.
     *
     * @ingroup getter
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
     * @ingroup setter
     */
    void set_row(const size_t &n, const std::vector<T> &val);
    /**
     * @brief Set a column of the matrix.
     *
     * @param n The index of the column to set.
     * @param val The value to set.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup setter
     */
    void set_column(const size_t &n, const std::vector<T> &val);
    /**
     * @brief Set a cell of the matrix.
     *
     * @param row The row of the cell to set.
     * @param col The column of the cell to set.
     * @param val The value to set.
     * @throw std::out_of_range If the index is out of range.
     *
     * @note The cell must be of the same type of the matrix.
     * @ingroup setter
     */
    void set_cell(const size_t &row, const size_t &col, const T &val);
    /**
     * @brief Set the diagonal of the matrix.
     *
     * @param val The diagonal to set.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the minimum of the number of rows and columns of the matrix.
     *
     * @note The diagonal must be a vector of the same type of the matrix.
     * @ingroup setter
     */
    void set_diag(const std::vector<T> &val);

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
     * @ingroup manipulation
     */
    void insert_row(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Insert a row in the matrix.
     *
     * @param pos The index of the row to insert.
     * @param val The value to insert.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void insert_column(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Push a row in the front of the matrix.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void push_row_front(const std::vector<T> &val);
    /**
     * @brief Push a row in the back of the matrix.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @note The row must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void push_row_back(const std::vector<T> &val);

    /**
     * @brief Push a column in the front of the matrix.
     *
     * @param val The column to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void push_col_front(const std::vector<T> &val);
    /**
     * @brief Push a column in the back of the matrix.
     *
     * @param val The column to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of rows of the matrix.
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void push_col_back(const std::vector<T> &val);

    /**
     * @bried Find the first row matching the condition.
     *
     * @param f The condition to satisfy. f(std::vector<T> row) -> bool
     * @return int The first index of the row. -1 if not found.
     *
     * @note The empty matrix always return -1.
     * @ingroup manipulation
     */
    int find_row(const std::function<bool(std::vector<T>)> &f) const;
    /**
     * @brief Find the first row matching the given row.
     *
     * @param val The row to find.
     * @return int The first index of the row. -1 if not found.
     *
     * @note The row must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    int find_row(const std::vector<T> &val) const;
    /**
     * @brief Find the first column matching the condition.
     *
     * @param f The condition to satisfy. f(std::vector<T> col) -> bool
     * @return int The first index of the column. -1 if not found.
     *
     * @note The empty matrix always return -1.
     * @ingroup manipulation
     */
    int find_column(const std::function<bool(std::vector<T>)> &f) const;
    /**
     * @brief Find the first column matching the given column.
     *
     * @param val The column to find.
     * @return int The first index of the row. -1 if not found.
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    int find_column(const std::vector<T> &val) const;
    /**
     * @brief Find the first cell matching the condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return std::tuple<int, int> The first index of the cell. (-1, -1) if not found.
     *
     * @note The empty matrix always return (-1, -1).
     * @ingroup manipulation
     */
    std::tuple<int, int> find(const std::function<bool(T)> &f) const;
    /**
     * @brief Find the first cell matching the given cell.
     *
     * @param val The cell to find.
     * @return std::tuple<int, int> The first index of the cell. (-1, -1) if not found.
     *
     * @note The cell must be of the same type of the matrix.
     * @ingroup manipulation
     */
    std::tuple<int, int> find(const T &val) const;

    /**
     * @brief Remove a row of the matrix.
     *
     * @param n The index of the row to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     * @ingroup manipulation
     */
    void remove_row(const size_t &n);
    /**
     * @brief Remove a column of the matrix.
     *
     * @param n The index of the column to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     * @ingroup manipulation
     */
    void remove_column(const size_t &n);

    // CHECK METHODS
    /**
     * @brief Check if the matrix is empty.
     *
     * @return true If the matrix is empty.
     * @return false If the matrix is not empty.
     *
     * @ingroup check
     */
    bool is_empty() const;
    /**
     * @brief Check if the matrix is a square matrix.
     *
     * @return true If the matrix is a square matrix.
     * @return false If the matrix is not a square matrix.
     *
     * @ingroup check
     */
    bool is_square() const;
    /**
     * @brief Check if the matrix is a diagonal matrix.
     *
     * @return true If the matrix is a diagonal matrix.
     * @return false If the matrix is not a diagonal matrix.
     *
     * @ingroup check
     */
    bool is_diag() const;
    /**
     * @brief Check if the matrix is the identity matrix.
     *
     * @return true If the matrix is the identity matrix.
     * @return false If the matrix is not the identity matrix.
     *
     * @ingroup check
     */
    bool is_identity() const;
    /**
     * @brief Check if the matrix is a symmetric matrix.
     *
     * @return true If the matrix is a symmetric matrix.
     * @return false If the matrix is not a symmetric matrix.
     *
     * @ingroup check
     */
    bool is_symetric() const;
    /**
     * @brief Check if the matrix is an upper triangular matrix.
     *
     * @return true If the matrix is an upper triangular matrix.
     * @return false If the matrix is not an upper triangular matrix.
     *
     * @ingroup check
     */
    bool is_triangular_up() const;
    /**
     * @brief Check if the matrix is a lower triangular matrix.
     *
     * @return true If the matrix is a lower triangular matrix.
     * @return false If the matrix is not a lower triangular matrix.
     *
     * @ingroup check
     */
    bool is_triangular_low() const;
    /**
     * @brief Check if all the cells of the matrix satisfy a condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return true If all the cells satisfy the condition.
     * @return false If at least one cell does not satisfy the condition.
     *
     * @note The empty matrix always return true.
     * @ingroup check
     */
    bool all(const std::function<bool(T)> &f) const;
    /**
     * @brief Check if all the cells of the matrix are equal to a value.
     *
     * @param val The value to check.
     * @return true If all the cells are equal to the value.
     * @return false If at least one cell is not equal to the value.
     *
     * @note The empty matrix always return true.
     * @ingroup check
     */
    bool all(const T &val) const;
    /**
     * @brief Check if at least one cell of the matrix satisfy a condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return true If at least one cell satisfy the condition.
     * @return false If all the cells does not satisfy the condition.
     *
     * @note The empty matrix always return false.
     * @ingroup check
     */
    bool any(const std::function<bool(T)> &f) const;
    /**
     * @brief Check if at least one cell of the matrix is equal to a value.
     *
     * @param val The value to check.
     * @return true If at least one cell is equal to the value.
     * @return false If all the cells are not equal to the value.
     *
     * @note The empty matrix always return false.
     * @ingroup check
     */
    bool any(const T &val) const;

    // STATISTICS METHODS
    /**
     * @brief Get the minimum value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the minimum value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<T> The minimum value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note The type of the matrix must implement the operator <.
     * @ingroup statistic
     */
    cmatrix<T> min(const unsigned int &axis = 0) const;
    /**
     * @brief Get the maximum value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the maximum value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<T> The maximum value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note The type of the matrix must implement the operator >.
     * @ingroup statistic
     */
    cmatrix<T> max(const unsigned int &axis = 0) const;
    /**
     * @brief Get the sum of the matrix for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the sum. 0 for the rows, 1 for the columns. (default: 0)
     * @param zero The zero value of the sum. (default: the value of the default constructor of the type T)
     * @return cmatrix<T> The sum of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @ingroup statistic
     */
    cmatrix<T> sum(const unsigned int &axis = 0, const T &zero = T()) const;
    /**
     * @brief Get the mean value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the mean value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<float> The mean value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::invalid_argument If the matrix is not arithmetic.
     *
     * @note The matrix must be of arithmetic type.
     * @ingroup statistic
     */
    cmatrix<float> mean(const unsigned int &axis = 0) const;
    /**
     * @brief Get the standard deviation value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the standard deviation. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<float> The standard deviation for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::invalid_argument If the matrix is not arithmetic.
     * @throw std::invalid_argument If the number of elements is less than 2 for the axis.
     *
     * @note The matrix must be of arithmetic type.
     * @ingroup statistic
     */
    cmatrix<float> std(const unsigned int &axis = 0) const;
    /**
     * @brief Get the median value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the median value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<T> The median value of the matrix for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note The matrix must implement the operator <.
     * @note If the number of elements is even, the median is the smallest value of the two middle values.
     * @ingroup statistic
     */
    cmatrix<T> median(const unsigned int &axis = 0) const;

    // OTHER METHODS
    /**
     * @brief Print the matrix in the standard output.
     *
     * @ingroup general
     */
    void print() const;
    /**
     * @brief Clear the matrix.
     *
     * @ingroup general
     */
    void clear();
    /**
     * @brief Copy the matrix.
     *
     * @return cmatrix<T> The copied matrix.
     *
     * @ingroup general
     */
    cmatrix<T> copy() const;
    /**
     * @brief Apply a function to each cell of the matrix.
     *
     * @param f The function to apply. f(T value, size_t *id_col, size_t *id_row) -> T
     * @param col The pointer to the column index. (default: nullptr)
     * @param row The pointer to the row index. (default: nullptr)
     *
     * @ingroup general
     */
    void apply(const std::function<T(T, size_t *, size_t *)> &f, size_t *col = nullptr, size_t *row = nullptr);
    /**
     * @brief Apply a function to each cell of the matrix.
     *
     * @param f The function to apply. f(T value) -> T
     *
     * @ingroup general
     */
    void apply(const std::function<T(T)> &f);
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @param f The function to apply. f(T value, size_t *id_col, size_t *id_row) -> T
     * @param col The pointer to the column index. (default: nullptr)
     * @param row The pointer to the row index. (default: nullptr)
     * @return cmatrix<T> The result of the function.
     *
     * @ingroup general
     */
    cmatrix<T> map(const std::function<T(T, size_t *, size_t *)> &f, size_t *col = nullptr, size_t *row = nullptr) const;
    template <class U>
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @tparam U The type of the matrix.
     * @param f The function to apply. f(T value, size_t *id_col, size_t *id_row) -> U
     * @param col The pointer to the column index. (default: nullptr)
     * @param row The pointer to the row index. (default: nullptr)
     * @return cmatrix<U> The result of the function.
     *
     * @ingroup general
     */
    cmatrix<U> map(const std::function<U(T, size_t *, size_t *)> &f, size_t *col = nullptr, size_t *row = nullptr) const;
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @param f The function to apply. f(T value) -> T
     * @return cmatrix<T> The result of the function.
     *
     * @ingroup general
     */
    cmatrix<T> map(const std::function<T(T)> &f) const;
    template <class U>
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @tparam U The type of the matrix.
     * @param f The function to apply. f(T value) -> U
     * @return cmatrix<U> The result of the function.
     *
     * @ingroup general
     */
    cmatrix<U> map(const std::function<U(T)> &f) const;
    /**
     * @brief Fill the matrix with a value.
     *
     * @param val The value to fill the matrix.
     *
     * @ingroup general
     */
    void fill(const T &val);
    /**
     * @brief Convert the matrix to a vector.
     *
     * @return std::vector<T> The vector.
     *
     * @ingroup general
     */
    std::vector<std::vector<T>> to_vector() const;
    /**
     * @brief Convert the matrix to a matrix of another type.
     *
     * @tparam U The type of the matrix.
     * @return cmatrix<U> The matrix of another type.
     * @throw std::invalid_argument If the type T is not convertible to the type U.
     *
     * @ingroup general
     */
    template <class U>
    cmatrix<U> cast() const;

    // STATIC METHODS
    /**
     * @brief Check if a nested vector is a matrix. To be a matrix, all the rows and columns must have the same length.
     *
     * @param m The nested vector to check.
     * @return true If the nested vector is a matrix.
     * @return false If the nested vector is not a matrix.
     *
     * @ingroup static
     */
    static bool is_matrix(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief Flatten a nested vector.
     *
     * @param vec The nested vector to flatten.
     * @return std::vector<T> The flattened vector.
     *
     * @ingroup static
     */
    static std::vector<T> flatten_vector(const std::vector<std::vector<T>> &vec);
    /**
     * @brief Generate a random matrix of integers.
     *
     * @param dim_h The number of rows.
     * @param dim_v The number of columns.
     * @param min The minimum value of the matrix.
     * @param max The maximum value of the matrix.
     * @param seed The seed of the random generator. (default: time(nullptr))
     *
     * @return cmatrix<int> The random matrix of integers.
     *
     * @ingroup static
     */
    static cmatrix<int> randint(const size_t &dim_v, const size_t &dim_h, const int &min, const int &max, const int &seed = time(nullptr));
    /**
     * @brief Generate a matrix of zeros.
     *
     * @param dim_h The number of columns.
     * @param dim_v The number of rows.
     * @return cmatrix<int> The matrix of zeros.
     */
    static cmatrix<int> zeros(const size_t &dim_h, const size_t &dim_v);
    /**
     * @brief Generate the identity matrix.
     *
     * @param dim The number of rows and columns.
     * @return cmatrix<int> The identity matrix.
     *
     * @ingroup static
     */
    static cmatrix<int> identity(const size_t &dim);

    // OPERATOR METHODS
    /**
     * @brief The assignment operator.
     *
     * @param m The matrix to copy.
     * @return cmatrix<T>& The copied matrix.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> &operator=(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief The assignment operator.
     *
     * @param m The matrix to copy.
     * @return cmatrix<T>& The copied matrix.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> &operator=(const cmatrix<T> &m);
    /**
     * @brief The equality operator.
     *
     * @param m The matrix to compare.
     * @return true If the matrices are equal.
     * @return false If the matrices are not equal.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    bool operator==(const cmatrix<T> &m) const;
    /**
     * @brief The inequality operator.
     *
     * @param m The matrix to compare.
     * @return true If the matrices are not equal.
     * @return false If the matrices are equal.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    bool operator!=(const cmatrix<T> &m) const;
    /**
     * @brief The equality operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator==(const T &n) const;
    /**
     * @brief The inequality operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator!=(const T &n) const;
    /**
     * @brief The strictly less than operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator<(const T &n) const;
    /**
     * @brief The less than operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator<=(const T &n) const;
    /**
     * @brief The strictly greater than operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator>(const T &n) const;
    /**
     * @brief The greater than operator comparing the matrix with a value.
     *
     * @param val The value to compare.
     * @return cmatrix<short unsigned int> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<short unsigned int> operator>=(const T &n) const;

    /**
     * @brief The output operator.
     *
     * @param out The output stream.
     * @param m The matrix to print.
     * @return std::ostream& The output stream.
     *
     * @ingroup operator
     */
    template <class U>
    friend std::ostream &operator<<(std::ostream &out, const cmatrix<U> &m);
    /**
     * @brief The addition operator.
     *
     * @param m The matrix to add.
     * @return cmatrix<T> The sum of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> operator+(const cmatrix<T> &m) const;
    /**
     * @brief The addition operator.
     *
     * @param n The value to add.
     * @return cmatrix<T> The sum of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> operator+(const T &n) const;
    /**
     * @brief The addition operator.
     *
     * @param n The value to add.
     * @param m The matrix to add.
     * @return cmatrix<T> The sum of the matrices.
     *
     * @ingroup operator
     */
    template <class U>
    friend cmatrix<U> operator+(const U &n, const cmatrix<U> &m);
    /**
     * @brief The subtraction operator.
     *
     * @param m The matrix to subtract.
     * @return cmatrix<T> The difference of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> operator-(const cmatrix<T> &m) const;
    /**
     * @brief The subtraction operator.
     *
     * @param n The value to subtract.
     * @return cmatrix<T> The difference of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> operator-(const T &val) const;
    /**
     * @brief The subtraction operator.
     *
     * @param n The value to subtract.
     * @param m The matrix to subtract.
     * @return cmatrix<T> The difference of the matrices.
     *
     * @ingroup operator
     */
    template <class U>
    friend cmatrix<U> operator-(const U &n, const cmatrix<U> &m);
    /**
     * @brief The negation operator.
     *
     * @param m The matrix to negate.
     * @return cmatrix<T> The negated matrix.
     *
     * @ingroup operator
     */
    template <class U>
    friend cmatrix<U> operator-(const cmatrix<U> &m);
    /**
     * @brief The multiplication operator.
     *
     * @param m The matrix to multiply.
     * @return cmatrix<T> The product of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> operator*(const cmatrix<T> &m) const;
    /**
     * @brief The multiplication operator.
     *
     * @param n The value to multiply.
     * @return cmatrix<T> The product of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> operator*(const T &n) const;
    /**
     * @brief The multiplication operator.
     *
     * @param n The value to multiply.
     * @param m The matrix to multiply.
     * @return cmatrix<T> The product of the matrices.
     *
     * @ingroup operator
     */
    template <class U>
    friend cmatrix<U> operator*(const U &n, const cmatrix<U> &m);
    /**
     * @brief The division operator.
     *
     * @param n The value to divide.
     * @return cmatrix<T> The quotient of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> operator/(const T &n) const;
    /**
     * @brief The power operator.
     *
     * @param m The power. Must be a positive integer.
     * @return cmatrix<T> The powered matrix.
     * @throw std::invalid_argument If the matrix is not a square matrix.
     *
     * @ingroup operator
     */
    cmatrix<T> operator^(const unsigned int &m) const;
    /**
     * @brief The addition assignment operator.
     *
     * @param m The matrix to add.
     * @return cmatrix<T>& The sum of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> &operator+=(const cmatrix<T> &m);
    /**
     * @brief The addition assignment operator.
     *
     * @param n The value to add.
     * @return cmatrix<T>& The sum of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> &operator+=(const T &n);
    /**
     * @brief The subtraction assignment operator.
     *
     * @param m The matrix to subtract.
     * @return cmatrix<T>& The difference of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> &operator-=(const cmatrix<T> &m);
    /**
     * @brief The subtraction assignment operator.
     *
     * @param n The value to subtract.
     * @return cmatrix<T>& The difference of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> &operator-=(const T &n);
    /**
     * @brief The multiplication assignment operator.
     *
     * @param m The matrix to multiply.
     * @return cmatrix<T>& The product of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> &operator*=(const cmatrix<T> &m);
    /**
     * @brief The multiplication assignment operator.
     *
     * @param n The value to multiply.
     * @return cmatrix<T>& The product of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> &operator*=(const T &n);
    /**
     * @brief The division assignment operator.
     *
     * @param n The value to divide.
     * @return cmatrix<T>& The quotient of the matrices.
     *
     * @ingroup operator
     */
    cmatrix<T> &operator/=(const T &n);
    /**
     * @brief The power assignment operator.
     *
     * @param m The power. Must be a positive integer.
     * @return cmatrix<T>& The powered matrix.
     * @throw std::invalid_argument If the matrix is not a square matrix.
     *
     * @ingroup operator
     */
    cmatrix<T> &operator^=(const unsigned int &m);
};

#include "../src/CMatrix.tpp"
#include "../src/CMatrixCheck.tpp"
#include "../src/CMatrixConstructor.tpp"
#include "../src/CMatrixGetter.tpp"
#include "../src/CMatrixManipulation.tpp"
#include "../src/CMatrixOperator.tpp"
#include "../src/CMatrixSetter.tpp"
#include "../src/CMatrixStatic.tpp"
#include "../src/CMatrixStatistics.tpp"
