/**
 * Unit tests for CMatrix class
 * @file CMatrixTest.cpp
 * @see CMatrix.hpp
 */

#include <gtest/gtest.h>
#include "CMatrix.hpp"

// ==================================================
// CONSTRUCTOR
/** Test Constuctor of cmatrix class */
TEST(MatrixTest, Constructor)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.dim_h(), 0);
    EXPECT_EQ(m_1.dim_v(), 0);

    // 3X3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m_2.dim_h(), 3);
    EXPECT_EQ(m_2.dim_v(), 3);
    EXPECT_EQ(m_2.rows(0), cmatrix<int>({{1, 2, 3}}));
    EXPECT_EQ(m_2.rows(1), cmatrix<int>({{4, 5, 6}}));
    EXPECT_EQ(m_2.rows(2), cmatrix<int>({{7, 8, 9}}));

    // 1X3 MATRIX
    cmatrix<int> m_3 = {{1}, {4}, {7}};
    EXPECT_EQ(m_3.dim_h(), 1);
    EXPECT_EQ(m_3.dim_v(), 3);
    EXPECT_EQ(m_3.rows(0), cmatrix<int>({{1}}));
    EXPECT_EQ(m_3.rows(1), cmatrix<int>({{4}}));
    EXPECT_EQ(m_3.rows(2), cmatrix<int>({{7}}));

    // 3X1 MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    EXPECT_EQ(m_4.rows_vec(0), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(m_4.dim_h(), 3);
    EXPECT_EQ(m_4.dim_v(), 1);

    // CREATE MATRIX FROM DIMENSIONS
    cmatrix<std::string> m_5(3, 2);
    EXPECT_EQ(m_5.dim_h(), 2);
    EXPECT_EQ(m_5.dim_v(), 3);

    // CREATE MATRIX FROM DIMENSIONS AND VALUE
    cmatrix<std::string> m_6(3, 2, "a");
    EXPECT_EQ(m_6.dim_h(), 2);
    EXPECT_EQ(m_6.dim_v(), 3);
    for (size_t r = 0; r < m_6.dim_v(); r++)
        for (size_t c = 0; c < m_6.dim_h(); c++)
            EXPECT_EQ(m_6.cell(r, c), "a");

    // INVALID MATRIX - NOT RECTANGULAR
    EXPECT_THROW(cmatrix<int> m_6({{1, 2}, {3, 4, 5}}), std::invalid_argument);

    // CONVERSION FROM OTHER TYPES
    cmatrix<int> m_7 = {{1, 2, 3}};
    cmatrix<float> m_8(m_7);
    EXPECT_EQ(m_8.dim_h(), 3);
    EXPECT_EQ(m_8.dim_v(), 1);
    EXPECT_EQ(m_8.cell(0, 0), 1.0f);
    EXPECT_EQ(m_8.cell(0, 1), 2.0f);
    EXPECT_EQ(m_8.cell(0, 2), 3.0f);

    // CONVERSION FROM OTHER TYPES - INVALID
    EXPECT_THROW(cmatrix<bool> m_9(m_7), std::invalid_argument);
}

// ==================================================
// GETTER METHODS
/** Test rows_vec method of cmatrix class */
TEST(MatrixTest, rows_vec)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.rows_vec(0), std::vector<int>({1, 2, 3}));

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.rows_vec(0), std::vector<int>({1, 2, 3}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.rows_vec(0), std::vector<int>({1}));
    EXPECT_EQ(m_3.rows_vec(1), std::vector<int>({2}));
    EXPECT_EQ(m_3.rows_vec(2), std::vector<int>({3}));

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.rows_vec(3), std::out_of_range);
}

/** Test columns_vec method of cmatrix class */
TEST(MatrixTest, columns_vec)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.columns_vec(0), std::vector<int>({1, 4, 7}));
    EXPECT_EQ(m.columns_vec(1), std::vector<int>({2, 5, 8}));
    EXPECT_EQ(m.columns_vec(2), std::vector<int>({3, 6, 9}));

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.columns_vec(0), std::vector<int>({1}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.columns_vec(0), std::vector<int>({1, 2, 3}));

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.columns_vec(3), std::out_of_range);
}

/** Test rows method of cmatrix class */
TEST(MatrixTest, rows)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> expected = {{1, 2, 3}, {7, 8, 9}};
    EXPECT_EQ(m.rows({0, 2}).dim_h(), 3);
    EXPECT_EQ(m.rows({0, 2}).dim_v(), 2);
    EXPECT_EQ(m.rows({0, 2}), expected);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.rows(0).dim_h(), 3);
    EXPECT_EQ(m_2.rows(0).dim_v(), 1);
    EXPECT_EQ(m_2.rows(0), m_2);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.rows({0, 2}).dim_h(), 1);
    EXPECT_EQ(m_3.rows({0, 2}).dim_v(), 2);
    EXPECT_EQ(m_3.rows({0, 2}), cmatrix<int>({{1}, {3}}));

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.rows({0, 3}), std::out_of_range);
}

/** Test columns method of cmatrix class */
TEST(MatrixTest, columns)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> expected = {{1, 3}, {4, 6}, {7, 9}};
    EXPECT_EQ(m.columns({0, 2}).dim_h(), 2);
    EXPECT_EQ(m.columns({0, 2}).dim_v(), 3);
    EXPECT_EQ(m.columns({0, 2}), expected);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.columns({0, 2}).dim_h(), 2);
    EXPECT_EQ(m_2.columns({0, 2}).dim_v(), 1);
    EXPECT_EQ(m_2.columns({0, 2}), cmatrix<int>({{1, 3}}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.columns(0).dim_h(), 1);
    EXPECT_EQ(m_3.columns(0).dim_v(), 3);
    EXPECT_EQ(m_3.columns(0), m_3);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.columns({0, 3}), std::out_of_range);
}

/** Test cells method of cmatrix class */
TEST(MatrixTest, cells)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9}};
    cmatrix<int> expected = {{1, 2, 5}};
    EXPECT_EQ(m.cells({{0, 0}, {0, 1}, {1, 1}}).dim_h(), 3);
    EXPECT_EQ(m.cells({{0, 0}, {0, 1}, {1, 1}}).dim_v(), 1);
    EXPECT_EQ(m.cells({{0, 0}, {0, 1}, {1, 1}}), expected);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.cells({{0, 0}, {0, 1}}).dim_h(), 2);
    EXPECT_EQ(m_2.cells({{0, 0}, {0, 1}}).dim_v(), 1);
    EXPECT_EQ(m_2.cells({{0, 0}, {0, 1}}), cmatrix<int>({{1, 2}}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.cells({{0, 0}, {1, 0}}).dim_h(), 2);
    EXPECT_EQ(m_3.cells({{0, 0}, {1, 0}}).dim_v(), 1);
    EXPECT_EQ(m_3.cells({{0, 0}, {1, 0}}), cmatrix<int>({{1, 2}}));
    EXPECT_EQ(m_3.cells(0, 0), cmatrix<int>({{1}}));

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.cells({{0, 0}, {3, 0}}), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.cells({{0, 0}, {0, 3}}), std::out_of_range);
}

/** Test cell method of cmatrix class */
TEST(MatrixTest, cell)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.cell(0, 0), 1);
    EXPECT_EQ(m.cell(1, 1), 5);
    EXPECT_EQ(m.cell(2, 2), 9);
    EXPECT_EQ(m.cell(0, 1), 2);
    EXPECT_EQ(m.cell(1, 0), 4);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.cell(3, 0), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.cell(0, 3), std::out_of_range);
}

/** Test dim_h method of cmatrix class */
TEST(MatrixTest, dim_h)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m_1.dim_h(), 3);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.dim_h(), 3);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_1.dim_h(), 3);

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_EQ(m_4.dim_h(), 0);
}

/** Test dim_v method of cmatrix class */
TEST(MatrixTest, dim_v)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m_1.dim_v(), 3);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.dim_v(), 1);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.dim_v(), 3);

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_EQ(m_4.dim_v(), 0);
}

/** Test dim method of cmatrix class */
TEST(MatrixTest, dim)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.dim(), (std::pair<size_t, size_t>(3, 3)));

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.dim(), (std::pair<size_t, size_t>(1, 3)));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.dim(), (std::pair<size_t, size_t>(3, 1)));

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_EQ(m_4.dim(), (std::pair<size_t, size_t>(0, 0)));
}

/** Test transpose method of cmatrix class */
TEST(MatrixTest, transpose)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    EXPECT_EQ(m_1.transpose(), m_2);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.transpose(), m_4);

    // 3x1 MATRIX
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<int> m_6 = {{1, 2, 3}};
    EXPECT_EQ(m_5.transpose(), m_6);

    // EMPTY MATRIX
    cmatrix<std::string> m_7;
    EXPECT_EQ(m_7.transpose(), cmatrix<std::string>());
}

/** Test diag method of cmatrix class */
TEST(MatrixTest, diag)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m_1.diag(), std::vector<int>({1, 5, 9}));

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    EXPECT_EQ(m_2.diag(), std::vector<int>({1}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_EQ(m_3.diag(), std::vector<int>({1}));

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_EQ(m_4.diag(), std::vector<std::string>());
}

// ==================================================
// SETTER METHODS
/** Test set_row method of cmatrix class */
TEST(MatrixTest, set_row)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_1.set_row(0, {10, 11, 12});
    EXPECT_EQ(m_1.rows_vec(0), std::vector<int>({10, 11, 12}));

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    m_2.set_row(0, {10, 11, 12});
    EXPECT_EQ(m_2.rows_vec(0), std::vector<int>({10, 11, 12}));

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    m_3.set_row(0, {10});
    EXPECT_EQ(m_3.rows_vec(0), std::vector<int>({10}));

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_THROW(m_4.set_row(0, {"a", "b", "c"}), std::out_of_range);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m_1.set_row(3, {10, 11, 12}), std::out_of_range);
}

/** Test set_column method of cmatrix class */
TEST(MatrixTest, set_column)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m.set_column(0, {10, 11, 12});
    EXPECT_EQ(m.cell(0, 0), 10);
    EXPECT_EQ(m.cell(1, 0), 11);
    EXPECT_EQ(m.cell(2, 0), 12);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    m_2.set_column(0, {10});
    EXPECT_EQ(m_2.cell(0, 0), 10);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    m_3.set_column(0, {10, 11, 12});
    EXPECT_EQ(m_3.cell(0, 0), 10);
    EXPECT_EQ(m_3.cell(1, 0), 11);
    EXPECT_EQ(m_3.cell(2, 0), 12);

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_THROW(m_4.set_column(0, {"a", "b", "c"}), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.set_column(3, {10, 11, 12}), std::out_of_range);
}

/** Test set_cell method of cmatrix class */
TEST(MatrixTest, set_cell)
{
    // 3x3 MATRIX
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m.set_cell(0, 0, 10);
    EXPECT_EQ(m.cell(0, 0), 10);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    m_2.set_cell(0, 1, 10);
    EXPECT_EQ(m_2.cell(0, 1), 10);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    m_3.set_cell(1, 0, 10);
    EXPECT_EQ(m_3.cell(1, 0), 10);

    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_THROW(m_4.set_cell(0, 0, "a"), std::out_of_range);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.set_cell(0, 3, 10), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.set_cell(3, 0, 10), std::out_of_range);
}

/** Test set_diag method of cmatrix class */
TEST(MatrixTest, set_diag)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_1.set_diag({10, 11, 12});
    EXPECT_EQ(m_1.cell(0, 0), 10);
    EXPECT_EQ(m_1.cell(1, 1), 11);
    EXPECT_EQ(m_1.cell(2, 2), 12);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    m_2.set_diag({10});
    EXPECT_EQ(m_2.cell(0, 0), 10);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    m_3.set_diag({10});
    EXPECT_EQ(m_3.cell(0, 0), 10);
    // EMPTY MATRIX
    cmatrix<std::string> m_4;
    EXPECT_THROW(m_4.set_diag({"a", "b", "c"}), std::invalid_argument);

    // INVALID SIZE
    EXPECT_THROW(m_1.set_diag({10, 11, 12, 13}), std::invalid_argument);
}

// ==================================================
// MANIPULATION METHODS
/** Test insert_row method of cmatrix class */
TEST(MatrixTest, insert_row)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_1.insert_row(1, {10, 11, 12});
    EXPECT_EQ(m_1.rows_vec(1), std::vector<int>({10, 11, 12}));

    // EMPTY MATRIX
    cmatrix<int> m_2;
    m_2.insert_row(0, {10, 11, 12});
    EXPECT_EQ(m_2.rows_vec(0), std::vector<int>({10, 11, 12}));

    // OUT OF RANGE - EMPTY MATRIX
    cmatrix<int> m_3;
    EXPECT_THROW(m_3.insert_row(1, {10, 11, 12}), std::out_of_range);

    // OUT OF RANGE - 1x3 MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    EXPECT_THROW(m_4.insert_row(2, {10, 11, 12}), std::out_of_range);

    // INVALID SIZE
    EXPECT_THROW(m_4.insert_row(0, {10, 11, 12, 13}), std::invalid_argument);
}

/** Test insert_column method of cmatrix class */
TEST(MatrixTest, insert_column)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_1.insert_column(1, {10, 11, 12});
    EXPECT_EQ(m_1.dim_h(), 4);
    EXPECT_EQ(m_1.dim_v(), 3);
    EXPECT_EQ(m_1.cell(0, 1), 10);
    EXPECT_EQ(m_1.cell(1, 1), 11);
    EXPECT_EQ(m_1.cell(2, 1), 12);

    // EMPTY MATRIX
    cmatrix<int> m_2;
    m_2.insert_column(0, {10, 11, 12});
    EXPECT_EQ(m_2.dim_h(), 1);
    EXPECT_EQ(m_2.dim_v(), 3);
    EXPECT_EQ(m_2.cell(0, 0), 10);
    EXPECT_EQ(m_2.cell(1, 0), 11);
    EXPECT_EQ(m_2.cell(2, 0), 12);

    // OUT OF RANGE - EMPTY MATRIX
    cmatrix<int> m_3;
    EXPECT_THROW(m_3.insert_column(1, {10, 11, 12}), std::out_of_range);

    // OUT OF RANGE - 1x3 MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    EXPECT_THROW(m_4.insert_column(4, {10}), std::out_of_range);

    // INVALID SIZE
    EXPECT_THROW(m_4.insert_column(0, {10, 11, 12, 13}), std::invalid_argument);
}

/** Test push_row_front method of cmatrix class */
TEST(MatrixTest, push_row_front)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    m_1.push_row_front({1, 2, 3});
    EXPECT_EQ(m_1.rows_vec(0), std::vector<int>({1, 2, 3}));

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{4, 5, 6}, {7, 8, 9}};
    m_2.push_row_front({1, 2, 3});
    EXPECT_EQ(m_2.rows_vec(0), std::vector<int>({1, 2, 3}));
}

/** Test push_row_back method of cmatrix class */
TEST(MatrixTest, push_row_back)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    m_1.push_row_back({1, 2, 3});
    EXPECT_EQ(m_1.rows_vec(0), std::vector<int>({1, 2, 3}));

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{4, 5, 6}, {7, 8, 9}};
    m_2.push_row_back({1, 2, 3});
    EXPECT_EQ(m_2.rows_vec(2), std::vector<int>({1, 2, 3}));
}

/** Test push_col_front method of cmatrix class */
TEST(MatrixTest, push_col_front)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    m_1.push_col_front({1, 2, 3});
    EXPECT_EQ(m_1.cell(0, 0), 1);
    EXPECT_EQ(m_1.cell(1, 0), 2);
    EXPECT_EQ(m_1.cell(2, 0), 3);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{4, 5, 6}, {7, 8, 9}};
    m_2.push_col_front({1, 2});
    EXPECT_EQ(m_2.cell(0, 0), 1);
    EXPECT_EQ(m_2.cell(1, 0), 2);
}

/** Test push_col_back method of cmatrix class */
TEST(MatrixTest, push_col_back)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    m_1.push_col_back({1, 2, 3});
    EXPECT_EQ(m_1.cell(0, 0), 1);
    EXPECT_EQ(m_1.cell(1, 0), 2);
    EXPECT_EQ(m_1.cell(2, 0), 3);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{4, 5, 6}, {7, 8, 9}};
    m_2.push_col_back({1, 2});
    EXPECT_EQ(m_2.cell(0, 3), 1);
    EXPECT_EQ(m_2.cell(1, 3), 2);
}

TEST(MatrixTest, find_row)
{
    // 3x3 MATRIX - FIND
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.find_row({4, 5, 6}), 1);
    EXPECT_EQ(m.find_row([](std::vector<int> row)
                         { return row.at(0) == row.at(1) - 1 && row.at(1) == row.at(2) - 1; }),
              0);

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.find_row({10, 11, 12}), -1);
    EXPECT_EQ(m.find_row({10, 11, 12, 13}), -1);

    // 3x1 MATRIX - FIND
    cmatrix<int> m_2 = {{1}, {2}, {3}};
    EXPECT_EQ(m_2.find_row({2}), 1);
    EXPECT_EQ(m_2.find_row([](std::vector<int> row)
                           { return row.at(0) == 2; }),
              1);

    // 3x1 MATRIX - NOT FIND
    EXPECT_EQ(m_2.find_row({10}), -1);

    // 1x3 MATRIX - FIND
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_EQ(m_3.find_row({1, 2, 3}), 0);
    EXPECT_EQ(m_3.find_row([](std::vector<int> row)
                           { return row.at(2) == 3; }),
              0);

    // 1x3 MATRIX - NOT FIND
    EXPECT_EQ(m_3.find_row({10, 11, 12}), -1);

    // EMPTY MATRIX
    cmatrix<int> m_4;
    EXPECT_EQ(m_4.find_row({1, 2, 3}), -1);
}

/** Test find_column method of cmatrix class */
TEST(MatrixTest, find_column)
{
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 3x3 MATRIX - FIND
    EXPECT_EQ(m.find_column({2, 5, 8}), 1);

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.find_column({10, 11, 12}), -1);
    EXPECT_EQ(m.find_column({10, 11, 12, 13}), -1);

    // 3x1 MATRIX - FIND
    cmatrix<int> m_2 = {{1}, {2}, {3}};
    EXPECT_EQ(m_2.find_column({1, 2, 3}), 0);

    // 3x1 MATRIX - NOT FIND
    EXPECT_EQ(m_2.find_column({10}), -1);

    // 1x3 MATRIX - FIND
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_EQ(m_3.find_column({2}), 1);

    // 1x3 MATRIX - NOT FIND
    EXPECT_EQ(m_3.find_column({10, 11, 12}), -1);

    // EMPTY MATRIX
    cmatrix<int> m_4;
    EXPECT_EQ(m_4.find_column({1, 2, 3}), -1);
}

/** Test find method of cmatrix class */
TEST(MatrixTest, find)
{
    cmatrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 3x3 MATRIX - FIND
    EXPECT_EQ(m.find(5), std::make_tuple(1, 1));

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.find(10), std::make_tuple(-1, -1));
}

/** Test remove_row method of cmatrix class */
TEST(MatrixTest, remove_row)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // REMOVE FIRST ROW
    m_1.remove_row(0);
    EXPECT_EQ(m_1.rows_vec(0), std::vector<int>({4, 5, 6}));
    EXPECT_EQ(m_1.rows_vec(1), std::vector<int>({7, 8, 9}));

    // REMOVE LAST ROW
    m_1.remove_row(1);
    EXPECT_EQ(m_1.rows_vec(0), std::vector<int>({4, 5, 6}));

    // REMOVE ONLY ROW
    m_1.remove_row(0);
    EXPECT_TRUE(m_1.is_empty());

    // EMPTY MATRIX
    cmatrix<int> m_2;
    EXPECT_THROW(m_2.remove_row(0), std::out_of_range);

    // OUT OF RANGE
    EXPECT_THROW(m_1.remove_row(0), std::out_of_range);
}

/** Test remove_column method of cmatrix class */
TEST(MatrixTest, remove_column)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // REMOVE FIRST COLUMN
    m_1.remove_column(0);
    EXPECT_EQ(m_1.dim_h(), 2);
    EXPECT_EQ(m_1.dim_v(), 3);
    EXPECT_EQ(m_1.columns_vec(0), std::vector<int>({2, 5, 8}));
    EXPECT_EQ(m_1.columns_vec(1), std::vector<int>({3, 6, 9}));

    // REMOVE LAST COLUMN
    m_1.remove_column(1);
    EXPECT_EQ(m_1.dim_h(), 1);
    EXPECT_EQ(m_1.dim_v(), 3);
    EXPECT_EQ(m_1.columns_vec(0), std::vector<int>({2, 5, 8}));

    // REMOVE ONLY COLUMN
    m_1.remove_column(0);
    EXPECT_TRUE(m_1.is_empty());

    // EMPTY MATRIX
    cmatrix<int> m_2;
    EXPECT_THROW(m_2.remove_column(0), std::out_of_range);

    // OUT OF RANGE
    EXPECT_THROW(m_1.remove_column(0), std::out_of_range);
}

// ==================================================
// CHECK METHODS
/** Test is_empty method of cmatrix class */
TEST(MatrixTest, is_empty)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_empty());

    // NON-EMPTY 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_FALSE(m_2.is_empty());

    // NON-EMPTY 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_3.is_empty());

    // NON-EMPTY 1x3 MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    EXPECT_FALSE(m_4.is_empty());
}

/** Test is_square method of cmatrix class */
TEST(MatrixTest, is_square)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_square());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(m_2.is_square());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_square());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_square());
}

/** Test is_diag method of cmatrix class */
TEST(MatrixTest, is_diag)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_diag());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};
    EXPECT_TRUE(m_2.is_diag());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_diag());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_diag());
}

/** Test is_identity method of cmatrix class */
TEST(MatrixTest, is_identity)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_identity());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    EXPECT_TRUE(m_2.is_identity());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_identity());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_identity());
}

TEST(MatrixTest, is_symetric)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_symetric());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_TRUE(m_2.is_symetric());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_symetric());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_symetric());
}

/** Test is_triangular_up method of cmatrix class */
TEST(MatrixTest, is_triangular_up)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_triangular_up());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {0, 5, 6}, {0, 0, 9}};
    EXPECT_TRUE(m_2.is_triangular_up());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_triangular_up());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_triangular_up());
}

/** Test is_triangular_low method of cmatrix class */
TEST(MatrixTest, is_triangular_low)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.is_triangular_low());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 0, 0}, {4, 5, 0}, {7, 8, 9}};
    EXPECT_TRUE(m_2.is_triangular_low());

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.is_triangular_low());

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.is_triangular_low());
}

/** Test all method of cmatrix class */
TEST(MatrixTest, all)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_TRUE(m_1.all([](int x)
                        { return x == 0; }));

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_FALSE(m_2.all(0));
    EXPECT_FALSE(m_2.all([](int x)
                         { return x == 0; }));
    EXPECT_TRUE(m_2.all([](int x)
                        { return x > 0; }));

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.all([](int x)
                         { return x == 0; }));

    EXPECT_TRUE(m_3.all([](int x)
                        { return x > 0; }));

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_4.all([](int x)
                         { return x == 0; }));

    EXPECT_TRUE(m_4.all([](int x)
                        { return x > 0; }));

    // FILL MATRIX WITH 4
    cmatrix<int> m_5(3, 3, 4);
    EXPECT_TRUE(m_5.all(4));
    EXPECT_FALSE(m_5.all(2));
}

/** Test any method of cmatrix class */
TEST(MatrixTest, any)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_FALSE(m_1.any([](int x)
                         { return x == 0; }));

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_FALSE(m_2.any([](int x)
                         { return x == 0; }));

    EXPECT_TRUE(m_2.any(1));
    EXPECT_TRUE(m_2.any([](int x)
                        { return x == 5; }));

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_FALSE(m_3.any(5));
    EXPECT_FALSE(m_3.any([](int x)
                         { return x == 0; }));

    EXPECT_TRUE(m_3.any(3));
    EXPECT_TRUE(m_3.any([](int x)
                        { return x == 2; }));

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m_3.any(5));
    EXPECT_FALSE(m_4.any([](int x)
                         { return x == 0; }));

    EXPECT_TRUE(m_3.any(2));
    EXPECT_TRUE(m_4.any([](int x)
                        { return x == 2; }));
}

/** Test check_dim method of cmatrix class */
TEST(MatrixTest, check_dim)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_NO_THROW(m_1.check_dim(std::tuple<size_t, size_t>(0, 0)));
    EXPECT_THROW(m_1.check_dim(std::tuple<size_t, size_t>(1, 1)), std::invalid_argument);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    cmatrix<int> m_3 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_dim(std::tuple<size_t, size_t>(2, 3)));
    EXPECT_NO_THROW(m_2.check_dim(m_3));
    EXPECT_THROW(m_2.check_dim(std::tuple<size_t, size_t>(3, 1)), std::invalid_argument);
    EXPECT_THROW(m_2.check_dim(m_1), std::invalid_argument);
}

/** Test check_valid_row method of cmatrix class */
TEST(MatrixTest, check_valid_row)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_THROW(m_1.check_valid_row({0}), std::invalid_argument);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_valid_row({0, 1, 2}));
    EXPECT_THROW(m_2.check_valid_row({1}), std::invalid_argument);
}

/** Test check_valid_col method of cmatrix class */
TEST(MatrixTest, check_valid_col)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_THROW(m_1.check_valid_col({0}), std::invalid_argument);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_valid_col({0, 1}));
    EXPECT_THROW(m_2.check_valid_col({3, 3, 4}), std::invalid_argument);
}

/** Test check_valid_row_id method of cmatrix class */
TEST(MatrixTest, check_valid_row_id)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_THROW(m_1.check_valid_row_id(0), std::out_of_range);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_valid_row_id(0));
    EXPECT_THROW(m_2.check_valid_row_id(3), std::out_of_range);
}

/** Test check_valid_col_id method of cmatrix class */
TEST(MatrixTest, check_valid_col_id)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_THROW(m_1.check_valid_col_id(0), std::out_of_range);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_valid_col_id(0));
    EXPECT_THROW(m_2.check_valid_col_id(3), std::out_of_range);
}

/** Test check_expected_id method of cmatrix class */
TEST(MatrixTest, check_expected_id)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_NO_THROW(m_1.check_expected_id(0, 0));
    EXPECT_THROW(m_1.check_expected_id(1, 0), std::out_of_range);

    // 2x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m_2.check_expected_id(2, 0, 3));
    EXPECT_NO_THROW(m_2.check_expected_id(2, 0, 2));
    EXPECT_NO_THROW(m_2.check_expected_id(3, 3));
}

// ==================================================
// STATISTICS METHODS
/** Test min method of cmatrix class */
TEST(MatrixTest, min)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.min(), cmatrix<int>(0, 0));

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, -2, 3}, {3, 6, 9}, {-2, 4, 6}};
    cmatrix<int> expected2Row = {{-2}, {3}, {-2}};
    cmatrix<int> expected2Col = {{-2, -2, 3}};
    EXPECT_EQ(m_2.min(0), expected2Row);
    EXPECT_EQ(m_2.min(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> expected3Row = {{1}};
    cmatrix<int> expected3Col = {{1, 2, 3}};
    EXPECT_EQ(m_3.min(0), expected3Row);
    EXPECT_EQ(m_3.min(1), expected3Col);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<int> expected4Row = {{1}, {2}, {3}};
    cmatrix<int> expected4Col = {{1}};
    EXPECT_EQ(m_4.min(0), expected4Row);
    EXPECT_EQ(m_4.min(1), expected4Col);

    // 1x3 STRING MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    cmatrix<std::string> expected5Row = {{"a"}};
    cmatrix<std::string> expected5Col = {{"a", "b", "c"}};
    EXPECT_EQ(m_5.min(0), expected5Row);
    EXPECT_EQ(m_5.min(1), expected5Col);

    // INVALID AXIS
    EXPECT_THROW(m_5.min(2), std::invalid_argument);
}

/** Test max method of cmatrix class */
TEST(MatrixTest, max)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.max(), cmatrix<int>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, -2, 3}, {3, 6, 9}, {-2, 4, 6}};
    cmatrix<int> expected2Row = {{3}, {9}, {6}};
    cmatrix<int> expected2Col = {{3, 6, 9}};
    EXPECT_EQ(m_2.max(0), expected2Row);
    EXPECT_EQ(m_2.max(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> expected3Row = {{3}};
    cmatrix<int> expected3Col = {{1, 2, 3}};
    EXPECT_EQ(m_3.max(0), expected3Row);
    EXPECT_EQ(m_3.max(1), expected3Col);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<int> expected4Row = {{1}, {2}, {3}};
    cmatrix<int> expected4Col = {{3}};
    EXPECT_EQ(m_4.max(0), expected4Row);
    EXPECT_EQ(m_4.max(1), expected4Col);

    // 1x3 STRING MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    cmatrix<std::string> expected5Row = {{"c"}};
    cmatrix<std::string> expected5Col = {{"a", "b", "c"}};
    EXPECT_EQ(m_5.max(0), expected5Row);
    EXPECT_EQ(m_5.max(1), expected5Col);

    // INVALID AXIS
    EXPECT_THROW(m_5.max(2), std::invalid_argument);
}

/** Test sum method of cmatrix class */
TEST(MatrixTest, sum)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.sum(), cmatrix<int>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, -2, 3}, {3, 6, 9}, {-2, 4, 6}};
    cmatrix<int> expected2Row = {{2}, {18}, {8}};
    cmatrix<int> expected2Col = {{2, 8, 18}};
    EXPECT_EQ(m_2.sum(0), expected2Row);
    EXPECT_EQ(m_2.sum(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> expected3Row = {{6}};
    cmatrix<int> expected3Col = {{1, 2, 3}};
    EXPECT_EQ(m_3.sum(0), expected3Row);
    EXPECT_EQ(m_3.sum(1), expected3Col);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<int> expected4Row = {{1}, {2}, {3}};
    cmatrix<int> expected4Col = {{6}};
    EXPECT_EQ(m_4.sum(0), expected4Row);
    EXPECT_EQ(m_4.sum(1), expected4Col);

    // 1x3 STRING MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    cmatrix<std::string> expected5Row = {{"abc"}};
    cmatrix<std::string> expected5Col = {{"a", "b", "c"}};
    EXPECT_EQ(m_5.sum(0), expected5Row);
    EXPECT_EQ(m_5.sum(1), expected5Col);

    // 2x3 MATRIX OF MATRICES
    cmatrix<cmatrix<int>> m_6;
    cmatrix<int> m_7 = {{1, 2, 3}, {4, 5, 6}};
    cmatrix<int> m_8 = {{7, 8, 9}, {10, 11, 12}};
    m_6.push_row_back({m_7, m_8});

    cmatrix<cmatrix<int>> expected6Row = {{{{8, 10, 12}, {14, 16, 18}}}};

    EXPECT_EQ(m_6.sum(0, cmatrix<int>(2, 3)), expected6Row);
    EXPECT_EQ(m_6.sum(1, cmatrix<int>(2, 3)), m_6);

    // INVALID AXIS
    EXPECT_THROW(m_5.sum(2), std::invalid_argument);
}

/** Test mean method of cmatrix class */
TEST(MatrixTest, mean)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.mean(), cmatrix<float>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{6, 12, 6}, {12, 6, 12}, {6, 12, 6}};
    cmatrix<float> expected2Row = {{8}, {10}, {8}};
    cmatrix<float> expected2Col = {{8, 10, 8}};
    EXPECT_EQ(m_2.mean(0), expected2Row);
    EXPECT_EQ(m_2.mean(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<float> expected3Row = {{2}};
    cmatrix<float> expected3Col = {{1, 2, 3}};
    EXPECT_EQ(m_3.mean(0), expected3Row);
    EXPECT_EQ(m_3.mean(1), expected3Col);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<float> expected4Row = {{1}, {2}, {3}};
    cmatrix<float> expected4Col = {{2}};
    EXPECT_EQ(m_4.mean(0), expected4Row);
    EXPECT_EQ(m_4.mean(1), expected4Col);

    // 1x3 NON NUMERIC MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    EXPECT_THROW(m_5.mean(), std::invalid_argument);
}

/** Test std method of cmatrix class */
TEST(MatrixTest, std)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.std(), cmatrix<float>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{6, 12, 6}, {12, 6, 12}, {6, 12, 6}};
    cmatrix<float> expected2Row = {{2.828427125}, {2.828427125}, {2.828427125}};
    cmatrix<float> expected2Col = {{2.828427125, 2.828427125, 2.828427125}};
    EXPECT_EQ(m_2.std(0), expected2Row);
    EXPECT_EQ(m_2.std(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<float> expected3 = {{0.8164965809}};
    EXPECT_EQ(m_3.std(0), expected3);
    EXPECT_THROW(m_3.std(1), std::invalid_argument);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<float> expected4 = {{0.8164965809}};
    EXPECT_EQ(m_4.std(1), expected4);
    EXPECT_THROW(m_4.std(0), std::invalid_argument);

    // 1x3 NON NUMERIC MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    EXPECT_THROW(m_5.std(), std::invalid_argument);
}

/** Test median method of cmatrix class */
TEST(MatrixTest, median)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.median(), cmatrix<float>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{6, 12, 6}, {12, 6, 12}, {6, 12, 6}};
    cmatrix<float> expected2Row = {{6}, {12}, {6}};
    cmatrix<float> expected2Col = {{6, 12, 6}};
    EXPECT_EQ(m_2.median(0), expected2Row);
    EXPECT_EQ(m_2.median(1), expected2Col);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<float> expected3Row = {{2}};
    cmatrix<float> expected3Col = {{1, 2, 3}};
    EXPECT_EQ(m_3.median(0), expected3Row);
    EXPECT_EQ(m_3.median(1), expected3Col);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<float> expected4Row = {{1}, {2}, {3}};
    cmatrix<float> expected4Col = {{2}};
    EXPECT_EQ(m_4.median(0), expected4Row);
    EXPECT_EQ(m_4.median(1), expected4Col);

    // 1x3 NON NUMERIC MATRIX
    cmatrix<std::string> m_5 = {{"a", "b", "c"}};
    EXPECT_EQ(m_5.median(), cmatrix<std::string>(1, 1, "b"));
}

// ==================================================
// OTHER METHODS
/** Test clear method of cmatrix class */
TEST(MatrixTest, clear)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    m_1.clear();
    EXPECT_TRUE(m_1.is_empty());

    // NON-EMPTY 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_2.clear();
    EXPECT_TRUE(m_2.is_empty());

    // NON-EMPTY 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    m_3.clear();
    EXPECT_TRUE(m_3.is_empty());

    // NON-EMPTY 1x3 MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    m_4.clear();
    EXPECT_TRUE(m_4.is_empty());
}

/** Test copy method of cmatrix class */
TEST(MatrixTest, copy)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    cmatrix<int> m1Copy = m_1.copy();
    EXPECT_EQ(m_1, m1Copy);

    // NON-EMPTY 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m2Copy = m_2.copy();
    EXPECT_EQ(m_2, m2Copy);

    // NON-EMPTY 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    cmatrix<int> m3Copy = m_3.copy();
    EXPECT_EQ(m_3, m3Copy);

    // AFTER COPY, CHANGE ORIGINAL MATRIX
    cmatrix<int> m_4 = {{1, 2, 3}};
    cmatrix<int> m4Copy = m_4.copy();
    m_4.set_cell(0, 0, 10);
    EXPECT_NE(m_4, m4Copy);
}

/** Test apply method of cmatrix class */
TEST(MatrixTest, apply)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m1Copy = m_1.copy();
    cmatrix<int> expected = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    m_1.apply([](int x, size_t *i, size_t *j)
              { return x * 2; });
    EXPECT_EQ(m_1, expected);
    m_1.apply([](int x)
              { return x / 2; });
    EXPECT_EQ(m_1, m1Copy);

    // 1x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}};
    cmatrix<int> m2Copy = m_2.copy();
    cmatrix<int> expected2 = {{2, 3, 4}};
    m_2.apply([](int x, size_t *i, size_t *j)
              { return x + 1; });
    EXPECT_EQ(m_2, expected2);
    m_2.apply([](int x)
              { return x - 1; });
    EXPECT_EQ(m_2, m2Copy);

    // 3x1 MATRIX
    cmatrix<int> m_3 = {{1}, {2}, {3}};
    cmatrix<int> m3Copy = m_3.copy();
    cmatrix<int> expected3 = {{2}, {3}, {4}};
    m_3.apply([](int x, size_t *i, size_t *j)
              { return x + 1; });
    EXPECT_EQ(m_3, expected3);
    m_3.apply([](int x)
              { return x - 1; });
    EXPECT_EQ(m_3, m3Copy);
}

/** Test map method of cmatrix class */
TEST(MatrixTest, map)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> expected = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    cmatrix<int> m_2 = m_1.map([](int x, size_t *i, size_t *j)
                               { return x * 2; });
    EXPECT_EQ(m_2, expected);
    m_2 = m_1.map([](int x)
                  { return x * 2; });
    EXPECT_EQ(m_2, expected);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> expected2 = {{2, 3, 4}};
    cmatrix<int> m_4 = m_3.map([](int x, size_t *i, size_t *j)
                               { return x + 1; });
    EXPECT_EQ(m_4, expected2);
    m_4 = m_3.map([](int x)
                  { return x + 1; });
    EXPECT_EQ(m_4, expected2);
}

/** Test fill method of cmatrix class */
TEST(MatrixTest, fill)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = cmatrix<int>::zeros(3, 3);
    cmatrix<int> expected = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    m_1.fill(1);
    EXPECT_EQ(m_1, expected);

    // 1x3 MATRIX
    cmatrix<int> m_2 = cmatrix<int>::zeros(3, 1);
    cmatrix<int> expected2 = {{1, 1, 1}};
    m_2.fill(1);
    EXPECT_EQ(m_2, expected2);

    // 3x1 MATRIX
    cmatrix<int> m_3 = cmatrix<int>::zeros(1, 3);
    cmatrix<int> expected3 = {{1}, {1}, {1}};
    m_3.fill(1);
    EXPECT_EQ(m_3, expected3);
}

/** Test to_vector method of cmatrix class */
TEST(MatrixTest, to_vector)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    EXPECT_EQ(m_1.to_vector(), std::vector<std::vector<int>>());

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m_2.to_vector(), std::vector<std::vector<int>>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_EQ(m_3.to_vector(), std::vector<std::vector<int>>({{1, 2, 3}}));

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_EQ(m_4.to_vector(), std::vector<std::vector<int>>({{1}, {2}, {3}}));
}

/** Test cast method of cmatrix class */
TEST(MatrixTest, cast)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    cmatrix<float> m1Cast = m_1.cast<float>();
    EXPECT_EQ(m1Cast, cmatrix<float>());

    // 3x1 MATRIX INT TO FLOAT
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    cmatrix<float> m4Cast = m_4.cast<float>();
    cmatrix<float> expected4 = {{1}, {2}, {3}};
    EXPECT_EQ(m4Cast, expected4);

    // 3x1 MATRIX FLOAT TO INT
    cmatrix<float> m_5 = {{1.1}, {2.2}, {3.3}};
    cmatrix<int> m5Cast = m_5.cast<int>();
    cmatrix<int> expected5 = {{1}, {2}, {3}};
    EXPECT_EQ(m5Cast, expected5);
}

// ==================================================
// STATIC METHODS
/** Test is_matrix method of cmatrix class */
TEST(MatrixTest, is_matrix)
{
    // EMPTY MATRIX
    EXPECT_TRUE(cmatrix<int>::is_matrix({}));

    // 3x3 MATRIX
    EXPECT_TRUE(cmatrix<int>::is_matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    // 1x3 MATRIX
    EXPECT_TRUE(cmatrix<int>::is_matrix({{1, 2, 3}}));

    // 3x1 MATRIX
    EXPECT_TRUE(cmatrix<int>::is_matrix({{1}, {2}, {3}}));

    // INVALID MATRIX - NOT RECTANGULAR
    EXPECT_FALSE(cmatrix<int>::is_matrix({{1, 2}, {3, 4, 5}}));
}

/** Test flatten_vector method of cmatrix class */
TEST(MatrixTest, flatten_vector)
{
    // EMPTY VECTOR
    EXPECT_EQ(cmatrix<int>::flatten_vector({}), std::vector<int>());

    // 2D VECTOR
    EXPECT_EQ(cmatrix<int>::flatten_vector({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

/** Test randint method of cmatrix class */
TEST(MatrixTest, randint)
{
    // 3x1 MATRIX
    cmatrix<int> m_1 = cmatrix<int>::randint(3, 1, 0, 10);
    EXPECT_EQ(m_1.dim_h(), 1);
    EXPECT_EQ(m_1.dim_v(), 3);

    for (size_t i = 0; i < m_1.dim_h(); i++)
        for (size_t j = 0; j < m_1.dim_v(); j++)
        {
            EXPECT_GE(m_1.cell(j, i), 0);
            EXPECT_LE(m_1.cell(j, i), 10);
        }

    // 1x3 MATRIX
    cmatrix<int> m_2 = cmatrix<int>::randint(1, 3, 0, 10);
    EXPECT_EQ(m_2.dim_h(), 3);
    EXPECT_EQ(m_2.dim_v(), 1);

    for (size_t i = 0; i < m_2.dim_h(); i++)
        for (size_t j = 0; j < m_2.dim_v(); j++)
        {
            EXPECT_GE(m_2.cell(j, i), 0);
            EXPECT_LE(m_2.cell(j, i), 10);
        }

    // 3x3 MATRIX
    cmatrix<int> m_3 = cmatrix<int>::randint(3, 3, 0, 10);
    EXPECT_EQ(m_3.dim_h(), 3);
    EXPECT_EQ(m_3.dim_v(), 3);

    for (size_t i = 0; i < m_3.dim_h(); i++)
        for (size_t j = 0; j < m_3.dim_v(); j++)
        {
            EXPECT_GE(m_3.cell(j, i), 0);
            EXPECT_LE(m_3.cell(j, i), 10);
        }
}

/** Test zeros method of cmatrix class */
TEST(MatrixTest, zeros)
{
    // 1x3 MATRIX
    cmatrix<int> m_1 = cmatrix<int>::zeros(1, 3);
    EXPECT_EQ(m_1.dim_h(), 1);
    EXPECT_EQ(m_1.dim_v(), 3);
    for (size_t i = 0; i < m_1.dim_h(); i++)
        for (size_t j = 0; j < m_1.dim_v(); j++)
            EXPECT_EQ(m_1.cell(j, i), 0);

    // 3x1 MATRIX
    cmatrix<int> m_2 = cmatrix<int>::zeros(3, 1);
    EXPECT_EQ(m_2.dim_h(), 3);
    EXPECT_EQ(m_2.dim_v(), 1);
    for (size_t i = 0; i < m_2.dim_h(); i++)
        for (size_t j = 0; j < m_2.dim_v(); j++)
            EXPECT_EQ(m_2.cell(j, i), 0);

    // 3x3 MATRIX
    cmatrix<int> m_3 = cmatrix<int>::zeros(3, 3);
    EXPECT_EQ(m_3.dim_h(), 3);
    EXPECT_EQ(m_3.dim_v(), 3);
    for (size_t i = 0; i < m_3.dim_h(); i++)
        for (size_t j = 0; j < m_3.dim_v(); j++)
            EXPECT_EQ(m_3.cell(j, i), 0);
}

/** Test identity method of cmatrix class */
TEST(MatrixTest, identity)
{
    // EMPTY MATRIX
    cmatrix<int> m = cmatrix<int>::identity(0);
    EXPECT_TRUE(m.is_empty());

    // 1x3 MATRIX
    cmatrix<int> m_1 = cmatrix<int>::identity(1);
    EXPECT_EQ(m_1.dim_h(), 1);
    EXPECT_EQ(m_1.dim_v(), 1);
    EXPECT_EQ(m_1.cell(0, 0), 1);

    // 2x2 MATRIX
    cmatrix<int> m_2 = cmatrix<int>::identity(2);
    EXPECT_EQ(m_2.dim_h(), 2);
    EXPECT_EQ(m_2.dim_v(), 2);
    EXPECT_EQ(m_2.cell(0, 0), 1);
    EXPECT_EQ(m_2.cell(1, 0), 0);
    EXPECT_EQ(m_2.cell(0, 1), 0);
    EXPECT_EQ(m_2.cell(1, 1), 1);
}

// ==================================================
// OPERATOR METHODS
/** Test operatorEquals method of cmatrix class */
TEST(MatrixTest, op_equals)
{
    // EQUAL 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<short unsigned int> m1Bool = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_TRUE(m_1 == m_2);
    EXPECT_EQ(m_1 == 1, m1Bool);

    // EQUAL 1x3 MATRICES
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<int> m_4 = {{1, 2, 3}};
    cmatrix<short unsigned int> m3Bool = {{0, 1, 0}};
    EXPECT_TRUE(m_3 == m_4);
    EXPECT_EQ(m_3 == 2, m3Bool);

    // EQUAL 3x1 MATRICES
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<int> m_6 = {{1}, {2}, {3}};
    cmatrix<short unsigned int> m5Bool = {{0}, {0}, {1}};
    EXPECT_TRUE(m_5 == m_6);
    EXPECT_EQ(m_5 == 3, m5Bool);

    // EQUAL EMPTY MATRICES
    EXPECT_TRUE(cmatrix<int>() == cmatrix<int>());
    EXPECT_EQ(cmatrix<int>() == 1, cmatrix<int>());

    // NOT EQUAL 3x3 MATRICES
    cmatrix<int> m_7 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_8 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    cmatrix<short unsigned int> m7Bool = {{0, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    EXPECT_TRUE(m_7 != m_8);
    EXPECT_EQ(m_7 != 1, m7Bool);
}

/** Test operatorLess method of cmatrix class */
TEST(MatrixTest, op_less)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<short unsigned int> m1Bool = {{1, 1, 1}, {1, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(m_1 < 5, m1Bool);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<short unsigned int> m3Bool = {{1, 0, 0}};
    EXPECT_EQ(m_3 < 2, m3Bool);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<short unsigned int> m5Bool = {{0}, {0}, {0}};
    EXPECT_EQ(m_5 < -1, m5Bool);

    // EMPTY MATRICES
    EXPECT_EQ(cmatrix<int>() < 0, cmatrix<short unsigned int>());
}

/** Test operatorLessEqual method of cmatrix class */
TEST(MatrixTest, op_leq)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<short unsigned int> m1Bool = {{1, 1, 1}, {1, 1, 1}, {0, 0, 0}};
    EXPECT_EQ(m_1 <= 6, m1Bool);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{1, 2, 3}};
    cmatrix<short unsigned int> m3Bool = {{1, 1, 1}};
    EXPECT_EQ(m_3 <= 3, m3Bool);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<short unsigned int> m5Bool = {{1}, {0}, {0}};
    EXPECT_EQ(m_5 <= 1, m5Bool);

    // EMPTY MATRICES
    EXPECT_EQ(cmatrix<int>() <= -6, cmatrix<short unsigned int>());
}

/** Test op_greater method of cmatrix class */
TEST(MatrixTest, op_greater)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    cmatrix<short unsigned int> m1Bool = {{1, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    EXPECT_EQ(m_1 > 8, m1Bool);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{3, 2, 1}};
    cmatrix<short unsigned int> m3Bool = {{1, 0, 0}};
    EXPECT_EQ(m_3 > 2, m3Bool);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{3}, {2}, {1}};
    cmatrix<short unsigned int> m5Bool = {{0}, {0}, {0}};
    EXPECT_EQ(m_5 > 6, m5Bool);

    // EMPTY MATRICES
    EXPECT_EQ(cmatrix<int>() > 2, cmatrix<short unsigned int>());
}

/** Test op_geq method of cmatrix class */
TEST(MatrixTest, op_geq)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    cmatrix<short unsigned int> m1Bool = {{1, 1, 1}, {1, 1, 1}, {1, 1, 0}};
    EXPECT_EQ(m_1 >= 2, m1Bool);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{3, 2, 1}};
    cmatrix<short unsigned int> m3Bool = {{1, 1, 0}};
    EXPECT_EQ(m_3 >= 2, m3Bool);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{3}, {2}, {1}};
    cmatrix<short unsigned int> m5Bool = {{0}, {0}, {0}};
    EXPECT_EQ(m_5 >= 6, m5Bool);

    // EMPTY MATRICES
    EXPECT_EQ(cmatrix<int>() >= 1, cmatrix<short unsigned int>());
}

/** Test op_stream method of cmatrix class */
TEST(MatrixTest, op_stream)
{
    // EMPTY MATRIX
    cmatrix<int> m_1;
    std::stringstream ss1;
    ss1 << m_1;
    EXPECT_EQ(ss1.str(), "[]");

    // 3x3 MATRIX
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::stringstream ss2;
    ss2 << m_2;
    EXPECT_EQ(ss2.str(), "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    std::stringstream ss3;
    ss3 << m_3;
    EXPECT_EQ(ss3.str(), "[[1, 2, 3]]");

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    std::stringstream ss4;
    ss4 << m_4;
    EXPECT_EQ(ss4.str(), "[[1], [2], [3]]");
}

/** Test op_sum method of cmatrix class */
TEST(MatrixTest, op_sum)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_3 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    cmatrix<int> m_3_bis = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    EXPECT_EQ(m_1 + m_2, m_3);
    EXPECT_EQ(m_1 + 1, m_3_bis);
    EXPECT_EQ(1 + m_1, m_3_bis);

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{1, 2, 3}};
    cmatrix<int> m_5 = {{4, 5, 6}};
    cmatrix<int> m_6 = {{5, 7, 9}};
    cmatrix<int> m_6_bis = {{11, 12, 13}};
    EXPECT_EQ(m_4 + m_5, m_6);
    EXPECT_EQ(m_4 + 10, m_6_bis);
    EXPECT_EQ(10 + m_4, m_6_bis);

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{1}, {2}, {3}};
    cmatrix<int> m_8 = {{4}, {5}, {6}};
    cmatrix<int> m_9 = {{5}, {7}, {9}};
    cmatrix<int> m_9_coeff = {{11}, {12}, {13}};
    EXPECT_EQ(m_7 + m_8, m_9);
    EXPECT_EQ(m_7 + 10, m_9_coeff);
    EXPECT_EQ(10 + m_7, m_9_coeff);

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    cmatrix<int> m_12;
    EXPECT_EQ(m_10 + m_11, m_12);
    EXPECT_EQ(m_10 + 10, m_12);
    EXPECT_EQ(10 + m_10, m_12);

    // NOT EQUAL DIMENSIONS
    cmatrix<int> m_13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m_13 + m_14, std::invalid_argument);
}

/** Test op_sub method of cmatrix class */
TEST(MatrixTest, op_sub)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_3_bis = {{1, 3, 5}, {7, 9, 11}, {13, 15, 17}};
    EXPECT_EQ(m_1 - m_2, m_3);
    EXPECT_EQ(m_1 - 1, m_3_bis);
    EXPECT_EQ(1 - m_1, -m_3_bis);
    EXPECT_EQ(-m_1, m_1 * (-1));

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{5, 7, 9}};
    cmatrix<int> m_5 = {{1, 2, 3}};
    cmatrix<int> m_6 = {{4, 5, 6}};
    cmatrix<int> m_6_bis = {{-5, -3, -1}};
    EXPECT_EQ(m_4 - m_5, m_6);
    EXPECT_EQ(10 - m_4, -m_6_bis);
    EXPECT_EQ(-m_4, m_4 * (-1));

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{5}, {7}, {9}};
    cmatrix<int> m_8 = {{1}, {2}, {3}};
    cmatrix<int> m_9 = {{4}, {5}, {6}};
    cmatrix<int> m_9_coeff = {{-5}, {-3}, {-1}};
    EXPECT_EQ(m_7 - m_8, m_9);
    EXPECT_EQ(10 - m_7, -m_9_coeff);
    EXPECT_EQ(-m_7, m_7 * (-1));

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    cmatrix<int> m_12;
    EXPECT_EQ(m_10 - m_11, m_12);
    EXPECT_EQ(m_10 - 10, m_12);
    EXPECT_EQ(10 - m_10, -m_12);
    EXPECT_EQ(-m_10, m_10 * (-1));

    // NOT EQUAL DIMENSIONS
    cmatrix<int> m_13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m_13 - m_14, std::invalid_argument);
}

/** Test op_mul method of cmatrix class */
TEST(MatrixTest, op_mul)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    cmatrix<int> m_3 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    cmatrix<int> m_3_bis = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    EXPECT_EQ(m_1 * m_2, m_3);
    EXPECT_EQ(m_1 * 2, m_3_bis);
    EXPECT_EQ(2 * m_1, m_3_bis);

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{5, 7, 9}};
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<int> m_6 = {{46}};
    cmatrix<int> m_6_bis = {{50, 70, 90}};
    EXPECT_EQ(m_4 * m_5, m_6);
    EXPECT_EQ(m_4 * 10, m_6_bis);
    EXPECT_EQ(10 * m_4, m_6_bis);

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{1}, {2}, {3}};
    cmatrix<int> m_8 = {{5, 7, 9}};
    cmatrix<int> m_9 = {{5, 7, 9}, {10, 14, 18}, {15, 21, 27}};
    cmatrix<int> m_9_coeff = {{2}, {4}, {6}};
    EXPECT_EQ(m_7 * m_8, m_9);
    EXPECT_EQ(m_7 * 2, m_9_coeff);
    EXPECT_EQ(2 * m_7, m_9_coeff);

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    cmatrix<int> m_12;
    EXPECT_EQ(m_10 * m_11, m_12);
    EXPECT_EQ(m_10 * 10, m_12);
    EXPECT_EQ(10 * m_10, m_12);

    // NOT EQUAL DIMENSIONS
    cmatrix<int> m_13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m_13 * m_14, std::invalid_argument);
}

/** Test op_div method of cmatrix class */
TEST(MatrixTest, op_div)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    cmatrix<int> m_2 = {{15, 12, 9}, {42, 34, 27}, {69, 57, 45}};
    EXPECT_EQ(m_1 / 2, m_2);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{10, 14, 18}};
    cmatrix<int> m_4 = {{1, 1, 1}};
    EXPECT_EQ(m_3 / 10, m_4);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{100}, {140}, {180}};
    cmatrix<int> m_6 = {{10}, {14}, {18}};
    EXPECT_EQ(m_5 / 10, m_6);

    // EMPTY MATRICES
    cmatrix<int> m_7;
    cmatrix<int> m_8;
    EXPECT_EQ(m_7 / 10, m_8);

    // DIVISION BY ZEROS
    cmatrix<int> m_9 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_THROW(m_9 / 0, std::invalid_argument);
}

/** Test op_power method of cmatrix class */
TEST(MatrixTest, op_power)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    EXPECT_EQ(m_1 ^ 2, m_2);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_THROW(m_3 ^ 2, std::invalid_argument);

    // 3x1 MATRIX
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    EXPECT_THROW(m_5 ^ 2, std::invalid_argument);

    // EMPTY MATRIX
    cmatrix<int> m_7;
    cmatrix<int> m_8;
    EXPECT_EQ(m_7 ^ 2, m_8);
}

/** Test op_assign_sum method of cmatrix class */
TEST(MatrixTest, op_assign_sum)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_3 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    m_1 += m_2;
    EXPECT_EQ(m_1, m_3);

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{1, 2, 3}};
    cmatrix<int> m_5 = {{4, 5, 6}};
    cmatrix<int> m_6 = {{5, 7, 9}};
    m_4 += m_5;
    EXPECT_EQ(m_4, m_6);

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{1}, {2}, {3}};
    cmatrix<int> m_8 = {{4}, {5}, {6}};
    cmatrix<int> m_9 = {{5}, {7}, {9}};
    m_7 += m_8;
    EXPECT_EQ(m_7, m_9);

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    m_10 += m_11;
    EXPECT_EQ(m_10, cmatrix<int>());

    // WITH COEFFICIENT
    cmatrix<int> m_12 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_13 = {{2, 3, 4}, {5, 6, 7}, {8, 9, 10}};
    m_12 += 1;
    EXPECT_EQ(m_12, m_13);
}

/** Test op_assign_sub method of cmatrix class */
TEST(MatrixTest, op_assign_sub)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    cmatrix<int> m_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m_1 -= m_2;
    EXPECT_EQ(m_1, m_3);

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{5, 7, 9}};
    cmatrix<int> m_5 = {{1, 2, 3}};
    cmatrix<int> m_6 = {{4, 5, 6}};
    m_4 -= m_5;
    EXPECT_EQ(m_4, m_6);

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{5}, {7}, {9}};
    cmatrix<int> m_8 = {{1}, {2}, {3}};
    cmatrix<int> m_9 = {{4}, {5}, {6}};
    m_7 -= m_8;
    EXPECT_EQ(m_7, m_9);

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    m_10 -= m_11;
    EXPECT_EQ(m_10, cmatrix<int>());

    // WITH COEFFICIENT
    cmatrix<int> m_12 = {{2, 4, 6}, {8, 10, 12}};
    cmatrix<int> m_13 = {{1, 3, 5}, {7, 9, 11}};
    m_12 -= 1;
    EXPECT_EQ(m_12, m_13);
}

/** Test op_assign_mul method of cmatrix class */
TEST(MatrixTest, op_assign_mul)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    cmatrix<int> m_3 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    m_1 *= m_2;
    EXPECT_EQ(m_1, m_3);

    // 1x3 MATRICES
    cmatrix<int> m_4 = {{5, 7, 9}};
    cmatrix<int> m_5 = {{1}, {2}, {3}};
    cmatrix<int> m_6 = {{46}};
    m_4 *= m_5;
    EXPECT_EQ(m_4, m_6);

    // 3x1 MATRICES
    cmatrix<int> m_7 = {{1}, {2}, {3}};
    cmatrix<int> m_8 = {{5, 7, 9}};
    cmatrix<int> m_9 = {{5, 7, 9}, {10, 14, 18}, {15, 21, 27}};
    m_7 *= m_8;
    EXPECT_EQ(m_7, m_9);

    // EMPTY MATRICES
    cmatrix<int> m_10;
    cmatrix<int> m_11;
    m_10 *= m_11;
    EXPECT_EQ(m_10, cmatrix<int>());

    // WITH COEFFICIENT
    cmatrix<int> m_12 = {{1, 2, 3}, {4, 5, 6}};
    cmatrix<int> m_13 = {{2, 4, 6}, {8, 10, 12}};
    m_12 *= 2;
    EXPECT_EQ(m_12, m_13);
}

/** Test op_assign_div method of cmatrix class */
TEST(MatrixTest, op_assign_div)
{
    // 3x3 MATRICES
    cmatrix<int> m_1 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    cmatrix<int> m_2 = {{15, 12, 9}, {42, 34, 27}, {69, 57, 45}};
    m_1 /= 2;
    EXPECT_EQ(m_1, m_2);

    // 1x3 MATRICES
    cmatrix<int> m_3 = {{10, 14, 18}};
    cmatrix<int> m_4 = {{1, 1, 1}};
    m_3 /= 10;
    EXPECT_EQ(m_3, m_4);

    // 3x1 MATRICES
    cmatrix<int> m_5 = {{100}, {140}, {180}};
    cmatrix<int> m_6 = {{10}, {14}, {18}};
    m_5 /= 10;
    EXPECT_EQ(m_5, m_6);

    // EMPTY MATRICES
    cmatrix<int> m_7;
    cmatrix<int> m_8;
    m_7 /= 10;
    EXPECT_EQ(m_7, m_8);

    // DIVISION BY ZEROS
    cmatrix<int> m_9 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_THROW(m_9 /= 0, std::invalid_argument);
}

/** Test op_assign_power method of cmatrix class */
TEST(MatrixTest, op_assign_power)
{
    // 3x3 MATRIX
    cmatrix<int> m_1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    cmatrix<int> m_2 = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    m_1 ^= 2;
    EXPECT_EQ(m_1, m_2);

    // 1x3 MATRIX
    cmatrix<int> m_3 = {{1, 2, 3}};
    EXPECT_THROW(m_3 ^= 2, std::invalid_argument);

    // 3x1 MATRIX
    cmatrix<int> m_4 = {{1}, {2}, {3}};
    EXPECT_THROW(m_4 ^= 2, std::invalid_argument);

    // EMPTY MATRIX
    cmatrix<int> m_5;
    m_5 ^= 2;
    EXPECT_EQ(m_5, cmatrix<int>());
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
