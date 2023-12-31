/**
 * @file CMatrix.hpp
 * @brief File containing the main template class of the 'cmatrix' library.
 *
 * @author Manitas Bahri <https://github.com/b-manitas>
 * @date 2023
 * @license MIT License
 */

#ifndef CMATRIX_HPP
#define CMATRIX_HPP

// INCLUDES
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <omp.h>
#include <numeric>
#include <utility>
#include <vector>

#include "CBool.hpp"

/**
 * @brief The main template class that can work with any data type.
 * The cmatrix class is a matrix of any type except bool.
 * To use the bool type, use the cbool class instead. (see CBool.hpp)
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
     * @param size The vertical and horizontal dimensions.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     *
     * @ingroup check
     */
    void __check_size(const std::tuple<size_t, size_t> &size) const;
    /**
     * @brief Check if dimensions are equals to the dimensions of the matrix.
     *
     * @param m The matrix.
     * @throw std::invalid_argument If the dimensions are not equals to the dimensions of the matrix.
     *
     * @ingroup check
     */
    void __check_size(const cmatrix<T> &m) const;
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
     * @param n The row index to check.
     * @throw std::invalid_argument If the row is not a valid row index of the matrix.
     *
     * @ingroup check
     */
    void __check_valid_row_id(const size_t &n) const;
    /**
     * @brief Check if the column is a valid column index of the matrix.
     *
     * @param n The column index to check.
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
     * List of types not supported: bool (use cbool instead).
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
    cmatrix<float> __mean(const unsigned int &axis, std::true_type true_type) const;
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
    cmatrix<float> __mean(const unsigned int &axis, std::false_type false_type) const;
    /**
     * @brief Compute the std value for each row (axis: 0) or column (axis: 1) of the matrix.
     * This method is used when the type of the matrix is arithmetic.
     *
     * @param axis The axis to get the std value. 0 for the rows, 1 for the columns. (default: 0)
     * @param true_type The type of the matrix is arithmetic.
     * @return cmatrix<float> The std value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup statistic
     */
    cmatrix<float> __std(const unsigned int &axis, std::true_type true_type) const;
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
    cmatrix<float> __std(const unsigned int &axis, std::false_type false_type) const;
    /**
     * @brief Apply a operator to each cell of the matrix.
     *
     * @param f The operator to apply. f(T value, T value) -> T
     * @param m The matrix to apply.
     * @return cmatrix<T> The result of the operator.
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> __map_op_arithmetic(const std::function<T(T, T)> &f, const cmatrix<T> &m) const;
    /**
     * @brief Apply a operator to each cell of the matrix.
     *
     * @param f The operator to apply. f(T value, T value) -> T
     * @param val The value to apply.
     * @return cmatrix<T> The result of the operator.
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> __map_op_arithmetic(const std::function<T(T, T)> &f, const T &val) const;

    // GENERAL METHODS
    /**
     * @brief Convert the matrix to a matrix of another type.
     *
     * @tparam U The type of the matrix to convert.
     * @param true_type The type of the matrix is convertible.
     * @return cmatrix<U> The converted matrix.
     *
     * @ingroup general
     */
    template <class U>
    cmatrix<U> __cast(std::true_type true_type) const;
    /**
     * @brief Convert the matrix to a matrix of another type.
     *
     * @tparam U The type of the matrix to convert.
     * @param false_type The type of the matrix is not convertible.
     * @throw std::invalid_argument The type of the matrix is not convertible.
     *
     * @ingroup general
     */
    template <class U>
    cmatrix<U> __cast(std::false_type false_type) const;
    /**
     * @brief Convert the matrix to a string matrix.
     *
     * @param true_type The type of the matrix is convertible.
     * @return cmatrix<std::string> The converted matrix.
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    cmatrix<std::string> __to_string(std::true_type true_type) const;
    /**
     * @brief Convert the matrix to a string matrix.
     *
     * @param false_type The type of the matrix is not convertible.
     * @throw std::invalid_argument The type of the matrix is not convertible.
     *
     * @ingroup general
     */
    cmatrix<std::string> __to_string(std::false_type false_type) const;

public:
    // CONSTRUCTOR METHODS
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param m The matrix to copy.
     * @throw std::invalid_argument If the initializer list is not a matrix.
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * > [[1, 2], [3, 4]]
     * @endcode
     */
    cmatrix(const std::initializer_list<std::initializer_list<T>> &m);
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param m The vector matrix.
     * @throw std::invalid_argument If the vector is not a matrix.
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * > [[1, 2], [3, 4]]
     * @endcode
     */
    cmatrix(const std::vector<std::vector<T>> &m);
    /**
     * @brief Construct a new cmatrix object.
     *
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m;
     * > []
     * @endcode
     */
    cmatrix();
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param height The number of rows.
     * @param width The number of columns.
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m(2, 2);
     * > [[0, 0], [0, 0]]
     * @endcode
     */
    cmatrix(const size_t &height, const size_t &width);
    /**
     * @brief Construct a new cmatrix object.
     *
     * @param height The number of rows.
     * @param width The number of columns.
     * @param val The value to fill the matrix.
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m(2, 2, 1);
     * > [[1, 1], [1, 1]]
     * @endcode
     */
    cmatrix(const size_t &height, const size_t &width, const T &val);
    /**
     * @brief Cast a matrix to another type.
     *
     * @param m The matrix to copy.
     * @tparam U The type of the matrix to copy.
     * @throw std::invalid_argument If the type is bool.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<float> n(m);
     * > n = [[1.0, 2.0], [3.0, 4.0]]
     * @endcode
     */
    template <class U>
    cmatrix(const cmatrix<U> &m);
    /**
     * @brief Destroy the cmatrix object.
     */
    ~cmatrix();

    // GETTER METHODS
    /**
     * @brief Get a submatrix of the matrix.
     *
     * @param m The mask of the matrix. The dimensions of the mask must be:
     *          - The same size of the matrix. Then, get the cells where the mask is true. (return a row matrix)
     *          - The same WIDTH of the matrix. Then, get the whole rows where the mask is true.
     *          - The same HEIGHT of the matrix. Then, get the whole columns where the mask is true.
     * @return cmatrix<T> The submatrix of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true, false}, {false, true}};
     * > m.get(mask);
     * > [[1, 0], [0, 4]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true, false}}
     * $ m.get(mask);
     * > [[1], [3]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true}, {false}}
     * $ m.get(mask);
     * > [[1, 2]]
     * @endcode
     *
     * @ingroup getter
     */
    cmatrix<T> get(const cmatrix<cbool> &m) const;

    /**
     * @brief Get a row of the matrix.
     *
     * @param n The index of the row to get.
     * @return std::vector<T> The row.
     * @throw std::out_of_range If the index is out of range.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.rows_vec(0);
     * > [1, 2]
     * @endcode
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
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.columns_vec(0);
     * > [1, 3]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.rows(1);
     * > [[3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.rows({0, 1});
     * > [[1, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.rows({0, 1});
     * > [[1, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.columns(1);
     * > [[2], [4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.columns({0, 1});
     * > [[1, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.columns({0, 1});
     * > [[1, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cells(0, 0);
     * > [[1]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cells({{0, 0}, {1, 1}});
     * > [[1, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cells({{0, 0}, {1, 1}});
     * > [[1, 4]]
     * @endcode
     *
     * @ingroup getter
     */
    cmatrix<T> cells(const std::vector<std::pair<size_t, size_t>> &ids) const;
    /**
     * @brief Get the reference to a cell of the matrix.
     *
     * @param row The row of the cell to get.
     * @param col The column of the cell to get.
     * @return T The cell.
     * @throw std::out_of_range If the index is out of range.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cell(0, 0) = 5;
     * > [[5, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cell(0, 0);
     * > 1
     * @endcode
     *
     * @ingroup getter
     */
    T cell(const size_t &row, const size_t &col) const;
    /**
     * @brief Get the rows between two indexes.
     *
     * @param start The start index inclusive.
     * @param end The end index inclusive.
     * @return cmatrix<T> The rows between two indexes.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the start index is greater than the end index.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}, {5, 6}};
     * $ m.slice_rows(0, 1);
     * > [[1, 2], [3, 4]]
     * @endcode
     *
     * @ingroup getter
     */
    cmatrix<T> slice_rows(const size_t &start, const size_t &end) const;
    /**
     * @brief Get the columns between two indexes.
     *
     * @param start The start index inclusive.
     * @param end The end index inclusive.
     * @return cmatrix<T> The columns between two indexes.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the start index is greater than the end index.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}};
     * $ m.slice_columns(0, 1);
     * > [[1, 2], [4, 5]]
     * @endcode
     *
     * @ingroup getter
     */
    cmatrix<T> slice_columns(const size_t &start, const size_t &end) const;

    /**
     * @brief The number of columns of the matrix.
     *
     * @return size_t The number of columns.
     *
     * @code
     * $ cmatrix<int> m = {{1}, {2}};
     * $ m.width();
     * > 1
     * @endcode
     *
     * @ingroup getter
     */
    size_t width() const;
    /**
     * @brief The number of rows of the matrix.
     *
     * @return size_t The number of rows.
     *
     * @code
     * $ cmatrix<int> m = {{1}, {2}};
     * $ m.height();
     * > 2
     * @endcode
     *
     * @ingroup getter
     */
    size_t height() const;
    /**
     * @brief The dimensions of the matrix.
     *
     * @return std::pair<size_t, size_t> The number of rows and columns.
     *
     * @code
     * $ cmatrix<int> m = {{1}, {2}};
     * $ m.size();
     * > (2, 1)
     * @endcode
     *
     * @ingroup getter
     */
    std::pair<size_t, size_t> size() const;
    /**
     * @brief The number of columns of the matrix.
     *
     * @tparam U The type of the number.
     * @return size_t The number of columns.
     *
     * @code
     * $ cmatrix<int> m = {{1}, {2}};
     * $ m.width_t<float>();
     * > 1.0f
     * @endcode
     *
     * @ingroup getter
     */
    template <class U>
    U width_t() const;
    /**
     * @brief The number of rows of the matrix.
     *
     * @tparam U The type of the number.
     * @return size_t The number of rows.
     *
     * @code
     * $ cmatrix<int> m = {{1}, {2}};
     * $ m.height_t<float>();
     * > 1.0f
     * @endcode
     *
     * @ingroup getter
     */
    template <class U>
    U height_t() const;

    /**
     * @brief Get the transpose of the matrix.
     *
     * @return cmatrix<T> The transpose of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.transpose();
     * > [[1, 3], [2, 4]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup getter
     */
    cmatrix<T> transpose() const;
    /**
     * @brief Get the diagonal of the matrix.
     *
     * @return std::vector<T> The diagonal of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.diag();
     * > [1, 4]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.set_row(0, {5, 6});
     * > [[5, 6], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.set_column(0, {5, 6});
     * > [[5, 2], [6, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.set_cell(0, 0, 5);
     * > [[5, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.set_diag({5, 6});
     * > [[5, 2], [3, 6]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.insert_column(0, {5, 6});
     * > [[5, 1, 2], [6, 3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.insert_row(0, {5, 6});
     * > [[5, 6], [1, 2], [3, 4]]
     * @endcode
     *
     * @note The row must be a vector of the same type of the matrix.
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup manipulation
     */
    void insert_column(const size_t &pos, const std::vector<T> &val);
    /**
     * @brief Push a row in the front of the matrix.
     *
     * @param val The row to push.
     * @throw std::invalid_argument If the size of the vector `val` is not equal to the number of columns of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.push_row_front({5, 6});
     * > [[5, 6], [1, 2], [3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.push_row_back({5, 6});
     * > [[1, 2], [3, 4], [5, 6]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.push_col_front({5, 6});
     * > [[5, 1, 2], [6, 3, 4]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.push_col_back({5, 6});
     * > [[1, 2, 5], [3, 4, 6]]
     * @endcode
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    void push_col_back(const std::vector<T> &val);

    /**
     * @brief Find the first row matching the condition.
     *
     * @param f The condition to satisfy. f(std::vector<T> row) -> bool
     * @return int The first index of the row. -1 if not found.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_row([](std::vector<int> row) { return row[0] == 1; });
     * > 0
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_row({1, 2});
     * > 0
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_column([](std::vector<int> col) { return col[0] == 1; });
     * > 0
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_column({1, 2});
     * > 0
     * @endcode
     *
     * @note The column must be a vector of the same type of the matrix.
     * @ingroup manipulation
     */
    int find_column(const std::vector<T> &val) const;
    /**
     * @brief Find the first cell matching the condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return std::pair<int, int> The first index (row, column) of the cell. (-1, -1) if not found.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find([](int value) { return value == 1; });
     * > (0, 0)
     * @endcode
     *
     * @note The empty matrix always return (-1, -1).
     * @ingroup manipulation
     */
    std::pair<int, int> find(const std::function<bool(T)> &f) const;
    /**
     * @brief Find the first cell matching the given cell.
     *
     * @param val The cell to find.
     * @return std::pair<int, int> The first index (row, column) of the cell. (-1, -1) if not found.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find(1);
     * > (0, 0)
     * @endcode
     *
     * @note The cell must be of the same type of the matrix.
     * @ingroup manipulation
     */
    std::pair<int, int> find(const T &val) const;
    /**
     * @brief Find all cells matching the condition.
     *
     * @param val The value to find.
     * @return std::vector<std::pair<size_t, size_t>> The indexes (row, column) of the cells.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_all(1);
     * > [(0, 0)]
     * @endcode
     *
     * @note The empty matrix always return an empty vector.
     * @ingroup manipulation
     */
    std::vector<std::pair<size_t, size_t>> find_all(const T &val) const;
    /**
     * @brief Find all cells matching the mask of another matrix.
     *
     * @param m The mask of the matrix. The dimensions of the mask must be:
     *          - The same size of the matrix. Then, get the cells ids where the mask is true.
     *          - The same WIDTH of the matrix. Then, get the cells ids where the mask is true for each ROW.
     *          - The same HEIGHT of the matrix. Then, get the cells ids where the mask is true for each COLUMN.
     * @return std::vector<std::pair<size_t, size_t>> The indexes (row, column) of the cells.
     *
     * @throw std::invalid_argument If the dimensions of the matrices are invalid.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true, false}, {false, true}};
     * $ m.find_all(mask);
     * > [(0, 0), (1, 1)]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true, false}};
     * $ m.find_all(mask);
     * > [(0, 0), (0, 1)]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<bool> mask = {{true}, {false}};
     * $ m.find_all(mask);
     * > [(0, 0), (1, 0)]
     * @endcode
     *
     * @ingroup manipulation
     */
    std::vector<std::pair<size_t, size_t>> find_all(const cmatrix<cbool> &m) const;
    /**
     * @brief Find all cells matching the condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return std::vector<std::pair<size_t, size_t>> The indexes (row, column) of the cells.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.find_all([](int value) { return value == 1; });
     * > [(0, 0)]
     * @endcode
     *
     * @note The empty matrix always return an empty vector.
     * @ingroup manipulation
     */
    std::vector<std::pair<size_t, size_t>> find_all(const std::function<bool(T)> &f) const;
    /**
     * @brief Create a mask of the matrix matching the condition.
     *
     * @param f The condition to satisfy. f(T value) -> bool
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.mask([](int value) { return value == 1; });
     * > [[true, false], [false, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> mask(const std::function<bool(T)> &f) const;
    /**
     * @brief Create a mask of the matrix matching the mask of another matrix.
     *
     * @param f The condition to satisfy. f(T value, T value) -> bool
     * @param m The mask of the matrix.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ cmatrix<int> mask = {{1, 0}, {0, 1}};
     * $ m.mask([](int a, int b) { return a == b; }, mask);
     * > [[true, false], [false, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> mask(const std::function<bool(T, T)> &f, const cmatrix<T> &m) const;
    /**
     * @brief Negate the mask of the matrix.
     *
     * @return cmatrix<cbool> The negated mask of the matrix.
     *
     * @code
     * $ cmatrix<int> mask = {{true, false}, {false, true}};
     * $ mask.not_();
     * > [[false, true], [true, false]]
     * @endcode
     *
     * @note The type of the matrix must be cbool.
     * @ingroup manipulation
     */
    cmatrix<cbool> not_() const;
    /**
     * @brief Check if each cell of the matrix are equals to the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.eq({{1, 2}, {2, 4}});
     * > [[true, true], [false, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> eq(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are equals to a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.eq(1);
     * > [[true, false], [false, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> eq(const T &val) const;
    /**
     * @brief Check if each cell of the matrix are not equals to the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.neq({{1, 2}, {2, 4}});
     * > [[false, false], [true, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> neq(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are not equals to a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.neq(1);
     * > [[false, true], [true, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> neq(const T &val) const;
    /**
     * @brief Check if each cell of the matrix are less or equals to the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.leq({{1, 2}, {2, 4}});
     * > [[true, true], [true, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> leq(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are less or equals to a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.leq(1);
     * > [[true, false], [false, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> leq(const T &val) const;
    /**
     * @brief Check if each cell of the matrix are greater or equals to the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.geq({{1, 2}, {2, 4}});
     * > [[true, true], [true, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> geq(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are greater or equals to a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.geq(1);
     * > [[true, true], [true, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> geq(const T &val) const;
    /**
     * @brief Check if each cell of the matrix are less than the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.lt({{1, 2}, {2, 4}});
     * > [[false, false], [false, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> lt(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are less than a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.lt(1);
     * > [[false, false], [false, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> lt(const T &val) const;
    /**
     * @brief Check if each cell of the matrix are greater than the cells of another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     * @throw std::invalid_argument If the dimensions of the matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.gt({{1, 2}, {2, 4}});
     * > [[false, false], [true, false]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> gt(const cmatrix<T> &m) const;
    /**
     * @brief Check if each cell of the matrix are greater than a value.
     *
     * @param val The value to compare.
     * @return cmatrix<cbool> The mask of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.gt(1);
     * > [[false, true], [true, true]]
     * @endcode
     *
     * @ingroup manipulation
     */
    cmatrix<cbool> gt(const T &val) const;

    /**
     * @brief Remove a row of the matrix.
     *
     * @param n The index of the row to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.remove_row(0);
     * > [[3, 4]]
     * @endcode
     *
     * @ingroup manipulation
     */
    void remove_row(const size_t &n);
    /**
     * @brief Remove a column of the matrix.
     *
     * @param n The index of the column to remove.
     * @throw std::out_of_range If the index is out of range.
     * @throw std::invalid_argument If the matrix is empty.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.remove_column(0);
     * > [[2], [4]]
     * @endcode
     *
     * @ingroup manipulation
     */
    void remove_column(const size_t &n);
    /**
     * @brief Concatenate a matrix to the matrix.
     *
     * @param m The matrix to concatenate.
     * @param axis The axis to concatenate. 0 for the rows, 1 for the columns. (default: 0)
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::invalid_argument If the dimensions of matrices are not equals.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.concatenate({{5, 6}, {7, 8}});
     * > [[1, 2], [3, 4], [5, 6], [7, 8]]
     * @endcode
     *
     * @ingroup manipulation
     */
    void concatenate(const cmatrix<T> &m, const unsigned int &axis = 0);

    // CHECK METHODS
    /**
     * @brief Check if the matrix is empty.
     *
     * @return true If the matrix is empty.
     * @return false If the matrix is not empty.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_empty();
     * > false
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_square();
     * > true
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}, {5, 6}};
     * $ m.is_square();
     * > false
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_diag();
     * > false
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 0}, {0, 4}};
     * $ m.is_diag();
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_identity();
     * > false
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 0}, {0, 1}};
     * $ m.is_identity();
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_symetric();
     * > false
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {2, 4}};
     * $ m.is_symetric();
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_triangular_up();
     * > false
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {0, 4}};
     * $ m.is_triangular_up();
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.is_triangular_low();
     * > false
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 0}, {3, 4}};
     * $ m.is_triangular_low();
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.all([](int value) { return value == 1; });
     * > false
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.all(1);
     * > false
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.any([](int value) { return value == 1; });
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.any(1);
     * > true
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.min(0);
     * > [[1], [3]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.min(1);
     * > [[1, 2]]
     * @endcode
     *
     * @note The type of the matrix must implement the operator <.
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup statistic
     */
    cmatrix<T> min(const unsigned int &axis = 0) const;
    /**
     * @brief Get the minimum value of all the elements of the matrix.
     *
     * @return T The minimum value of all the elements of the matrix.
     * @throw std::invalid_argument If the matrix is empty.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.min_all();
     * > 1
     * @endcode
     *
     * @note The type of the matrix must implement the operator <.
     * @ingroup statistic
     */
    T min_all() const;
    /**
     * @brief Get the maximum value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the maximum value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<T> The maximum value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.max(0);
     * > [[3], [4]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.max(1);
     * > [[2, 4]]
     * @endcode
     *
     * @note The type of the matrix must implement the operator >.
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup statistic
     */
    cmatrix<T> max(const unsigned int &axis = 0) const;
    /**
     * @brief Get the maximum value of all the elements of the matrix.
     *
     * @return T The maximum value of all the elements of the matrix.
     * @throw std::invalid_argument If the matrix is empty.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.max_all();
     * > 4
     * @endcode
     *
     * @note The type of the matrix must implement the operator >.
     * @ingroup statistic
     */
    T max_all() const;
    /**
     * @brief Get the sum of the matrix for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the sum. 0 for the rows, 1 for the columns. (default: 0)
     * @param zero The zero value of the sum. (default: the value of the default constructor of the type T)
     * @return cmatrix<T> The sum of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.sum(0);
     * > [[4], [6]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.sum(1);
     * > [[3, 7]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup statistic
     */
    cmatrix<T> sum(const unsigned int &axis = 0, const T &zero = T()) const;
    /**
     * @brief Get the sum of all the elements of the matrix.
     *
     * @param zero The zero value of the sum. (default: the value of the default constructor of the type T)
     * @return T The sum of all the elements of the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.sum_all();
     * > 10
     * @endcode
     *
     * @ingroup statistic
     */
    T sum_all(const T &zero = T()) const;
    /**
     * @brief Get the mean value for each row (axis: 0) or column (axis: 1) of the matrix.
     *
     * @param axis The axis to get the mean value. 0 for the rows, 1 for the columns. (default: 0)
     * @return cmatrix<float> The mean value for each row or column of the matrix.
     * @throw std::invalid_argument If the axis is not 0 or 1.
     * @throw std::invalid_argument If the matrix is not arithmetic.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.mean(0);
     * > [[1.5], [3.5]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.mean(1);
     * > [[2, 3]]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.std(0);
     * > [[0.5], [0.5]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.std(1);
     * > [[1, 1]]
     * @endcode
     *
     * @note The matrix must be of arithmetic type.
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.median(0);
     * > [[1], [4]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.median(1);
     * > [[3, 4]]
     * @endcode
     *
     * @note The matrix must implement the operator <.
     * @note If the number of elements is even, the median is the smallest value of the two middle values.
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup statistic
     */
    cmatrix<T> median(const unsigned int &axis = 0) const;

    // MATH METHODS
    /**
     * @brief Test if the matrix is near another matrix.
     *
     * @param val The matrix to test.
     * @param tolerance The tolerance of the test. (default: 1e-5)
     * @return true If the matrix is near the matrix `val`.
     * @return false If the matrix is not near the matrix `val`.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.near({{1, 2}, {2, 4}});
     * > [[true, true], [false, true]]
     * @endcode
     *
     * @ingroup math
     */
    bool near(const cmatrix<T> &val, const T &tolerance = 1e-5) const;
    /**
     * @brief Test if the matrix is near a value.
     *
     * @param val The value to test.
     * @param tolerance The tolerance of the test. (default: 1e-5)
     * @return true If the matrix is near the value `val`.
     * @return false If the matrix is not near the value `val`.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.near(1);
     * > [[true, false], [false, false]]
     * @endcode
     *
     * @ingroup math
     */
    bool near(const T &val, const T &tolerance = 1e-5) const;
    /**
     * @brief Test if the matrix is not near another matrix.
     *
     * @param val The matrix to test.
     * @param tolerance The tolerance of the test. (default: 1e-5)
     * @return true If the matrix is not near the matrix `val`.
     * @return false If the matrix is near the matrix `val`.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.nearq({{1, 2}, {2, 4}});
     * > [[true, false], [false, true]]
     * @endcode
     *
     * @ingroup math
     */
    bool nearq(const cmatrix<T> &val, const T &tolerance = 1e-5) const;
    /**
     * @brief Test if the matrix is not near a value.
     *
     * @param val The value to test.
     * @param tolerance The tolerance of the test. (default: 1e-5)
     * @return true If the matrix is not near the value `val`.
     * @return false If the matrix is near the value `val`.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.nearq(1);
     * > [[false, true], [true, true]]
     * @endcode
     *
     * @ingroup math
     */
    bool nearq(const T &val, const T &tolerance = 1e-5) const;
    /**
     * @brief Get the product with another matrix.
     *
     * @param m The matrix to multiply.
     * @return cmatrix<T> The result of the product.
     * @throw std::invalid_argument If the number of columns of the matrix is not equal to the number of rows of the matrix `m`.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.matmul({{5, 6}, {7, 8}});
     * > [[19, 22], [43, 50]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> matmul(const cmatrix<T> &m) const;
    /**
     * @brief Get the power of the matrix.
     *
     * @param n The power.
     * @return cmatrix<T> The result of the power.
     * @throw std::invalid_argument If the matrix is not a square matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.matpow(2);
     * > [[7, 10], [15, 22]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> matpow(const unsigned int &n) const;
    /**
     * @brief Get the natural logarithm of the matrix.
     *
     * @return cmatrix<T> The result of the log.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.log();
     * > [[0, 0.693147], [1.09861, 1.38629]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> log() const;
    /**
     * @brief Get the log2 of the matrix.
     *
     * @return cmatrix<T> The result of the log.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.log2();
     * > [[0, 1], [1.58496, 2]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> log2() const;
    /**
     * @brief Get the log10 of the matrix.
     *
     * @return cmatrix<T> The result of the log.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.log10();
     * > [[0, 0.30103], [0.477121, 0.60206]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> log10() const;
    /**
     * @brief Get the exponential of the matrix.
     *
     * @return cmatrix<T> The result of the exponential.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.exp();
     * > [[2.71828, 7.38906], [20.0855, 54.5982]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> exp() const;
    /**
     * @brief Get the square root of the matrix.
     *
     * @return cmatrix<T> The result of the square root.
     *
     * @code
     * $ cmatrix<int> m = {{1, 4}, {9, 16}};
     * $ m.sqrt();
     * > [[1, 2], [3, 4]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> sqrt() const;
    /**
     * @brief Get the absolute value of the matrix.
     *
     * @return cmatrix<T> The result of the absolute value.
     *
     * @code
     * $ cmatrix<int> m = {{1, -2}, {-3, 4}};
     * $ m.abs();
     * > [[1, 2], [3, 4]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup math
     */
    cmatrix<T> abs() const;

    // OTHER METHODS
    /**
     * @brief Print the matrix in the standard output.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.print();
     * > [[1, 2], [3, 4]]
     * @endcode
     *
     * @ingroup general
     */
    void print() const;
    /**
     * @brief Clear the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.clear();
     * > []
     * @endcode
     *
     * @ingroup general
     */
    void clear();
    /**
     * @brief Copy the matrix.
     *
     * @return cmatrix<T> The copied matrix.
     *
     * @code
     * $ cmatrix<int> m1 = {{1, 2}, {3, 4}};
     * $ cmatrix<int> m2 = m1.copy();
     * $ m2[0][0] = 0;
     * > m1 = [[1, 2], [3, 4]]
     * > m2 = [[0, 2], [3, 4]]
     * @endcode
     *
     * @ingroup general
     */
    cmatrix<T> copy() const;
    /**
     * @brief Apply a function to each cell of the matrix.
     *
     * @param f The function to apply. f(T value, size_t id_row, size_t id_col) -> T
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.apply([](int value, size_t row, size_t col) { return value + 1; });
     * > [[2, 3], [4, 5]]
     * @endcode
     *
     * @ingroup general
     */
    void apply(const std::function<T(T, size_t, size_t)> &f);
    /**
     * @brief Apply a function to each cell of the matrix.
     *
     * @param f The function to apply. f(T value) -> T
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.apply([](int value) { return value + 1; });
     * > [[2, 3], [4, 5]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    void apply(const std::function<T(T)> &f);
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @param f The function to apply. f(T value, size_t id_row, size_t id_col) -> T
     * @return cmatrix<T> The result of the function.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.map([](int value, size_t row, size_t col) { return value + 1; });
     * > [[2, 3], [4, 5]]
     * @endcode
     *
     * @ingroup general
     */
    cmatrix<T> map(const std::function<T(T, size_t, size_t)> &f) const;
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @tparam U The type of the matrix.
     * @param f The function to apply. f(T value, size_t id_row, size_t id_col) -> U
     * @return cmatrix<U> The result of the function.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.map<float>([](int value, size_t row, size_t col) { return value + 0.5; });
     * > [[1.5, 2.5], [3.5, 4.5]]
     * @endcode
     *
     * @ingroup general
     */
    template <class U>
    cmatrix<U> map(const std::function<U(T, size_t, size_t)> &f) const;
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @param f The function to apply. f(T value) -> T
     * @return cmatrix<T> The result of the function.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.map<float>([](int value) { return value + 0.5; });
     * > [[1.5, 2.5], [3.5, 4.5]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    cmatrix<T> map(const std::function<T(T)> &f) const;
    /**
     * @brief Apply a function to each cell of the matrix and return the result.
     *
     * @tparam U The type of the matrix.
     * @param f The function to apply. f(T value) -> U
     * @return cmatrix<U> The result of the function.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.map<float>([](int value) { return value + 0.5; });
     * > [[1.5, 2.5], [3.5, 4.5]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    template <class U>
    cmatrix<U> map(const std::function<U(T)> &f) const;
    /**
     * @brief Fill the matrix with a value.
     *
     * @param val The value to fill the matrix.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.fill(0);
     * > [[0, 0], [0, 0]]
     * @endcode
     *
     * @ingroup general
     */
    void fill(const T &val);
    /**
     * @brief Convert the matrix to a vector.
     *
     * @return std::vector<T> The vector.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.to_vector();
     * > [1, 2, 3, 4]
     * @endcode
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
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.cast<float>();
     * > [[1.0, 2.0], [3.0, 4.0]]
     * @endcode
     *
     * @ingroup general
     */
    template <class U>
    cmatrix<U> cast() const;
    /**
     * @brief Convert the matrix to a matrix of integers.
     *
     * @return cmatrix<int> The matrix of integers.
     * @throw std::invalid_argument If the type T is not convertible to the type int.
     * @throw std::runtime_error If the value is out of range of the type int.
     *
     * @code
     * $ cmatrix<float> m = {{1.0, 2.0}, {3.0, 4.0}};
     * $ m.to_int();
     * > [[1, 2], [3, 4]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    cmatrix<int> to_int() const;
    /**
     * @brief Convert the matrix to a matrix of floats.
     *
     * @return cmatrix<float> The matrix of floats.
     * @throw std::invalid_argument If the type T is not convertible to the type float.
     * @throw std::runtime_error If the value is out of range of the type float.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.to_float();
     * > [[1.0, 2.0], [3.0, 4.0]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    cmatrix<float> to_float() const;
    /**
     * @brief Convert the matrix to a matrix of strings.
     *
     * @return cmatrix<std::string> The matrix of strings.
     * @throw std::invalid_argument If the type T is not a primitive type.
     *
     * @code
     * $ cmatrix<int> m = {{1, 2}, {3, 4}};
     * $ m.to_string();
     * > [["1", "2"], ["3", "4"]]
     * @endcode
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup general
     */
    cmatrix<std::string> to_string() const;

    // STATIC METHODS
    /**
     * @brief Check if a nested vector is a matrix. To be a matrix, all the rows and columns must have the same length.
     *
     * @param m The nested vector to check.
     * @return true If the nested vector is a matrix.
     * @return false If the nested vector is not a matrix.
     *
     * @code
     * $ std::vector<std::vector<int>> m = {{1, 2}, {3, 4}};
     * $ cmatrix<int>::is_matrix(m);
     * > true
     * @endcode
     *
     * @code
     * $ std::vector<std::vector<int>> m = {{1, 2}, {3, 4, 5}};
     * $ cmatrix<int>::is_matrix(m);
     * > false
     * @endcode
     *
     * @ingroup static
     */
    static bool is_matrix(const std::vector<std::vector<T>> &m);
    /**
     * @brief Generate a random matrix of integers.
     *
     * @param height The number of height.
     * @param width The number of columns.
     * @param min The minimum value of the matrix (included). (default: 0)
     * @param max The maximum value of the matrix (included). (default: 100)
     * @param seed The seed of the random generator. (default: time(nullptr))
     *
     * @return cmatrix<int> The random matrix of integers.
     *
     * @code
     * $ cmatrix<int>::randint(2, 3);
     * > [[1, 2], [3, 4], [5, 6]]
     * @endcode
     *
     * @ingroup static
     */
    static cmatrix<int> randint(const size_t &height, const size_t &width, const int &min = 0, const int &max = 100, const int &seed = time(nullptr));
    /**
     * @brief Generate a random matrix of floats.
     *
     * @param height The number of rows.
     * @param width The number of columns.
     * @param min The minimum value of the matrix (included). (default: 0)
     * @param max The maximum value of the matrix (included). (default: 1)
     * @param seed The seed of the random generator. (default: time(nullptr))
     *
     * @return cmatrix<float> The random matrix of floats.
     *
     * @code
     * $ cmatrix<float>::randfloat(2, 3);
     * > [[0.1, 0.2], [0.3, 0.4], [0.5, 0.6]]
     * @endcode
     *
     * @ingroup static
     */
    static cmatrix<float> randfloat(const size_t &height, const size_t &width, const float &min = 0, const float &max = 1, const int &seed = time(nullptr));
    /**
     * @brief Generate a matrix of zeros.
     *
     * @param width The number of columns.
     * @param height The number of rows.
     * @return cmatrix<int> The matrix of zeros.
     *
     * @code
     * $ cmatrix<int>::zeros(2, 3);
     * > [[0, 0], [0, 0], [0, 0]]
     * @endcode
     *
     * @ingroup static
     */
    static cmatrix<int> zeros(const size_t &width, const size_t &height);
    /**
     * @brief Generate the identity matrix.
     *
     * @param size The number of rows and columns.
     * @return cmatrix<int> The identity matrix.
     *
     * @code
     * $ cmatrix<int>::identity(3);
     * > [[1, 0, 0], [0, 1, 0], [0, 0, 1]]
     * @endcode
     *
     * @ingroup static
     */
    static cmatrix<int> identity(const size_t &size);
    /**
     * @brief Merge two matrices.
     *
     * @param m1 The first matrix.
     * @param m2 The second matrix.
     * @param axis The axis to merge. 0 for the rows, 1 for the columns. (default: 0)
     *
     * @return cmatrix<T> The merged matrix.
     *
     * @code
     * $ cmatrix<int> m1 = {{1, 2}, {3, 4}};
     * $ cmatrix<int> m2 = {{5, 6}, {7, 8}};
     * $ cmatrix<int>::merge(m1, m2, 0);
     * > [[1, 2], [3, 4], [5, 6], [7, 8]]
     * @endcode
     *
     * @code
     * $ cmatrix<int> m1 = {{1, 2}, {3, 4}};
     * $ cmatrix<int> m2 = {{5, 6}, {7, 8}};
     * $ cmatrix<int>::merge(m1, m2, 1);
     * > [[1, 2, 5, 6], [3, 4, 7, 8]]
     * @endcode
     *
     * @ingroup static
     */
    static cmatrix<T> merge(const cmatrix<T> &m1, const cmatrix<T> &m2, const unsigned int &axis = 0);

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
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator==(const T &n) const;
    /**
     * @brief The inequality operator comparing the matrix with a value.
     *
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator!=(const T &n) const;
    /**
     * @brief The strictly less than operator comparing the matrix with another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator<(const cmatrix<T> &m) const;
    /**
     * @brief The strictly less than operator comparing the matrix with a value.
     *
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator<(const T &n) const;
    /**
     * @brief The less than operator comparing the matrix with another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator<=(const cmatrix<T> &m) const;
    /**
     * @brief The less than operator comparing the matrix with a value.
     *
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator<=(const T &n) const;
    /**
     * @brief The strictly greater than operator comparing the matrix with another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator>(const cmatrix<T> &m) const;
    /**
     * @brief The strictly greater than operator comparing the matrix with a value.
     *
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator>(const T &n) const;
    /**
     * @brief The greater than operator comparing the matrix with another matrix.
     *
     * @param m The matrix to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator>=(const cmatrix<T> &m) const;
    /**
     * @brief The greater than operator comparing the matrix with a value.
     *
     * @param n The value to compare.
     * @return cmatrix<cbool> The matrix of booleans.
     *
     * @ingroup operator
     */
    cmatrix<cbool> operator>=(const T &n) const;

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
     * @brief The not operator.
     *
     * @return cmatrix<cbool> The negated matrix.
     *
     * @ingroup operator
     */
    cmatrix<T> operator!() const;
    /**
     * @brief The addition operator.
     *
     * @param m The matrix to add.
     * @return cmatrix<T> The sum of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> operator+(const cmatrix<T> &m) const;
    /**
     * @brief The addition operator.
     *
     * @param n The value to add.
     * @return cmatrix<T> The sum of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @note The matrix must be of the same type of the matrix.
     * @ingroup operator
     */
    cmatrix<T> operator-(const cmatrix<T> &m) const;
    /**
     * @brief The subtraction operator.
     *
     * @param val The value to subtract.
     * @return cmatrix<T> The difference of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    template <class U>
    friend cmatrix<U> operator-(const cmatrix<U> &m);
    /**
     * @brief The multiplication operator element-wise.
     *
     * @param m The matrix to multiply.
     * @return cmatrix<T> The product of the matrices.
     *
     * @note The matrix must be of the same type of the matrix.
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> operator/(const T &n) const;
    /**
     * @brief The power operator element-wise.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> &operator+=(const cmatrix<T> &m);
    /**
     * @brief The addition assignment operator.
     *
     * @param n The value to add.
     * @return cmatrix<T>& The sum of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> &operator-=(const cmatrix<T> &m);
    /**
     * @brief The subtraction assignment operator.
     *
     * @param n The value to subtract.
     * @return cmatrix<T>& The difference of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
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
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> &operator*=(const cmatrix<T> &m);
    /**
     * @brief The multiplication assignment operator.
     *
     * @param n The value to multiply.
     * @return cmatrix<T>& The product of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
     * @ingroup operator
     */
    cmatrix<T> &operator*=(const T &n);
    /**
     * @brief The division assignment operator.
     *
     * @param n The value to divide.
     * @return cmatrix<T>& The quotient of the matrices.
     *
     * @note PARALLELIZED METHOD with OpenMP.
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

#endif // CMATRIX_H

#include "../src/CMatrix.tpp"
#include "../src/CMatrixCheck.tpp"
#include "../src/CMatrixConstructor.tpp"
#include "../src/CMatrixGetter.tpp"
#include "../src/CMatrixManipulation.tpp"
#include "../src/CMatrixMath.tpp"
#include "../src/CMatrixOperator.tpp"
#include "../src/CMatrixSetter.tpp"
#include "../src/CMatrixStatic.tpp"
#include "../src/CMatrixStatistics.tpp"
