#include <gtest/gtest.h>
#include "Matrix.hpp"

// ==================================================
// CONSTRUCTOR
/** Test Constuctor of Matrix class */
TEST(MatrixTest, Constructor)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_EQ(m1.dimH(), 0);
    EXPECT_EQ(m1.dimV(), 0);

    // 3X3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m2.dimH(), 3);
    EXPECT_EQ(m2.dimV(), 3);
    EXPECT_EQ(m2.getRow(0), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(m2.getCol(1).at(0), std::vector<int>({2}));
    EXPECT_EQ(m2.getCol(1).at(1), std::vector<int>({5}));
    EXPECT_EQ(m2.getCol(1).at(2), std::vector<int>({8}));
    EXPECT_EQ(m2.getCell(2, 2), 9);

    // 1X3 MATRIX
    Matrix<int> m3 = {{1}, {4}, {7}};
    EXPECT_EQ(m3.dimH(), 1);
    EXPECT_EQ(m3.dimV(), 3);
    EXPECT_EQ(m3.getCol(0).at(0), std::vector<int>({1}));
    EXPECT_EQ(m3.getCol(0).at(1), std::vector<int>({4}));
    EXPECT_EQ(m3.getCol(0).at(2), std::vector<int>({7}));

    // 3X1 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_EQ(m4.getRow(0), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(m4.dimH(), 3);
    EXPECT_EQ(m4.dimV(), 1);

    // CREATE MATRIX FROM DIMENSIONS
    Matrix<std::string> m5(2, 3);
    EXPECT_EQ(m5.dimH(), 2);
    EXPECT_EQ(m5.dimV(), 3);

    // CREATE MATRIX FROM DIMENSIONS AND VALUE
    Matrix<std::string> m6(2, 3, "a");
    EXPECT_EQ(m6.dimH(), 2);
    EXPECT_EQ(m6.dimV(), 3);
    for (size_t r = 0; r < m6.dimV(); r++)
        for (size_t c = 0; c < m6.dimH(); c++)
            EXPECT_EQ(m6.getCell(c, r), "a");

    // INVALID MATRIX - NOT RECTANGULAR
    EXPECT_THROW(Matrix<int> m6({{1, 2}, {3, 4, 5}}), std::invalid_argument);
}

// ==================================================
// GETTER METHODS
/** Test getRow method of Matrix class */
TEST(MatrixTest, getRow)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.getRow(0), std::vector<int>({1, 2, 3}));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.getRow(0), std::vector<int>({1, 2, 3}));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.getRow(0), std::vector<int>({1}));
    EXPECT_EQ(m3.getRow(1), std::vector<int>({2}));
    EXPECT_EQ(m3.getRow(2), std::vector<int>({3}));

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.getRow(3), std::out_of_range);
}

/** Test getCol method of Matrix class */
TEST(MatrixTest, getCol)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.getCol(0).at(0), std::vector<int>({1}));
    EXPECT_EQ(m.getCol(0).at(1), std::vector<int>({4}));
    EXPECT_EQ(m.getCol(0).at(2), std::vector<int>({7}));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.getCol(0).at(0), std::vector<int>({1}));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.getCol(0).at(0), std::vector<int>({1}));
    EXPECT_EQ(m3.getCol(0).at(1), std::vector<int>({2}));
    EXPECT_EQ(m3.getCol(0).at(2), std::vector<int>({3}));

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.getCol(3), std::out_of_range);
}

/** Test getFlatCol method of Matrix class */
TEST(MatrixTest, getFlatCol)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.getFlatCol(0), std::vector<int>({1, 4, 7}));
    EXPECT_EQ(m.getFlatCol(1), std::vector<int>({2, 5, 8}));
    EXPECT_EQ(m.getFlatCol(2), std::vector<int>({3, 6, 9}));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.getFlatCol(0), std::vector<int>({1}));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.getFlatCol(0), std::vector<int>({1, 2, 3}));

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.getFlatCol(3), std::out_of_range);
}

/** Test getCell method of Matrix class */
TEST(MatrixTest, getCell)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.getCell(0, 0), 1);
    EXPECT_EQ(m.getCell(1, 1), 5);
    EXPECT_EQ(m.getCell(2, 2), 9);
    EXPECT_EQ(m.getCell(0, 1), 4);
    EXPECT_EQ(m.getCell(1, 0), 2);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.getCell(3, 0), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.getCell(0, 3), std::out_of_range);
}

/** Test at method of Matrix class */
TEST(MatrixTest, at)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.at(0), Matrix<int>({{1, 2, 3}}));
    EXPECT_EQ(m.at(1), Matrix<int>({{4, 5, 6}}));
    EXPECT_EQ(m.at(2), Matrix<int>({{7, 8, 9}}));

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.at(3), std::out_of_range);
}

/** Test iloc method of Matrix class */
TEST(MatrixTest, iloc)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.iloc(0), Matrix<int>({{1}, {4}, {7}}));
    EXPECT_EQ(m.iloc(1), Matrix<int>({{2}, {5}, {8}}));
    EXPECT_EQ(m.iloc(2), Matrix<int>({{3}, {6}, {9}}));

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.iloc(3), std::out_of_range);
}

/** Test dimH method of Matrix class */
TEST(MatrixTest, dimH)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m1.dimH(), 3);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.dimH(), 3);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m1.dimH(), 3);

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_EQ(m4.dimH(), 0);
}

/** Test dimV method of Matrix class */
TEST(MatrixTest, dimV)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m1.dimV(), 3);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.dimV(), 1);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.dimV(), 3);

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_EQ(m4.dimV(), 0);
}

/** Test dim method of Matrix class */
TEST(MatrixTest, dim)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.dim(), std::make_tuple(3, 3));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.dim(), std::make_tuple(1, 3));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.dim(), std::make_tuple(3, 1));

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_EQ(m4.dim(), std::make_tuple(0, 0));
}

/** Test transpose method of Matrix class */
TEST(MatrixTest, transpose)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
    EXPECT_EQ(m1.transpose(), m2);

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.transpose(), m4);

    // 3x1 MATRIX
    Matrix<int> m5 = {{1}, {2}, {3}};
    Matrix<int> m6 = {{1, 2, 3}};
    EXPECT_EQ(m5.transpose(), m6);

    // EMPTY MATRIX
    Matrix<std::string> m7;
    EXPECT_EQ(m7.transpose(), Matrix<std::string>());
}

/** Test diag method of Matrix class */
TEST(MatrixTest, diag)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m1.diag(), std::vector<int>({1, 5, 9}));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    EXPECT_EQ(m2.diag(), std::vector<int>({1}));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_EQ(m3.diag(), std::vector<int>({1}));

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_EQ(m4.diag(), std::vector<std::string>());
}

// ==================================================
// SETTER METHODS
/** Test setRow method of Matrix class */
TEST(MatrixTest, setRow)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m1.setRow(0, {10, 11, 12});
    EXPECT_EQ(m1.getRow(0), std::vector<int>({10, 11, 12}));

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    m2.setRow(0, {10, 11, 12});
    EXPECT_EQ(m2.getRow(0), std::vector<int>({10, 11, 12}));

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    m3.setRow(0, {10});
    EXPECT_EQ(m3.getRow(0), std::vector<int>({10}));

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_THROW(m4.setRow(0, {"a", "b", "c"}), std::out_of_range);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m1.setRow(3, {10, 11, 12}), std::out_of_range);
}

/** Test setCol method of Matrix class */
TEST(MatrixTest, setCol)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m.setCol(0, {10, 11, 12});
    EXPECT_EQ(m.getCell(0, 0), 10);
    EXPECT_EQ(m.getCell(0, 1), 11);
    EXPECT_EQ(m.getCell(0, 2), 12);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    m2.setCol(0, {10});
    EXPECT_EQ(m2.getCell(0, 0), 10);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    m3.setCol(0, {10, 11, 12});
    EXPECT_EQ(m3.getCell(0, 0), 10);
    EXPECT_EQ(m3.getCell(0, 1), 11);
    EXPECT_EQ(m3.getCell(0, 2), 12);

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_THROW(m4.setCol(0, {"a", "b", "c"}), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.setCol(3, {10, 11, 12}), std::out_of_range);
}

/** Test setCell method of Matrix class */
TEST(MatrixTest, setCell)
{
    // 3x3 MATRIX
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m.setCell(0, 0, 10);
    EXPECT_EQ(m.getCell(0, 0), 10);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    m2.setCell(1, 0, 10);
    EXPECT_EQ(m2.getCell(1, 0), 10);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    m3.setCell(0, 1, 10);
    EXPECT_EQ(m3.getCell(0, 1), 10);

    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_THROW(m4.setCell(0, 0, "a"), std::out_of_range);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.setCell(3, 0, 10), std::out_of_range);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.setCell(0, 3, 10), std::out_of_range);
}

/** Test setDiag method of Matrix class */
TEST(MatrixTest, setDiag)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m1.setDiag({10, 11, 12});
    EXPECT_EQ(m1.getCell(0, 0), 10);
    EXPECT_EQ(m1.getCell(1, 1), 11);
    EXPECT_EQ(m1.getCell(2, 2), 12);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    m2.setDiag({10});
    EXPECT_EQ(m2.getCell(0, 0), 10);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    m3.setDiag({10});
    EXPECT_EQ(m3.getCell(0, 0), 10);
    // EMPTY MATRIX
    Matrix<std::string> m4;
    EXPECT_THROW(m4.setDiag({"a", "b", "c"}), std::invalid_argument);

    // INVALID SIZE
    EXPECT_THROW(m1.setDiag({10, 11, 12, 13}), std::invalid_argument);
}

// ==================================================
// MANIPULATION METHODS
/** Test insertRow method of Matrix class */
TEST(MatrixTest, insertRow)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m1.insertRow(1, {10, 11, 12});
    EXPECT_EQ(m1.getRow(1), std::vector<int>({10, 11, 12}));

    // EMPTY MATRIX
    Matrix<int> m2;
    m2.insertRow(0, {10, 11, 12});
    EXPECT_EQ(m2.getRow(0), std::vector<int>({10, 11, 12}));

    // OUT OF RANGE - EMPTY MATRIX
    Matrix<int> m3;
    EXPECT_THROW(m3.insertRow(1, {10, 11, 12}), std::out_of_range);

    // OUT OF RANGE - 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_THROW(m4.insertRow(2, {10, 11, 12}), std::out_of_range);

    // INVALID SIZE
    EXPECT_THROW(m4.insertRow(0, {10, 11, 12, 13}), std::invalid_argument);
}

/** Test insertCol method of Matrix class */
TEST(MatrixTest, insertCol)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m1.insertCol(1, {10, 11, 12});
    EXPECT_EQ(m1.dimH(), 4);
    EXPECT_EQ(m1.dimV(), 3);
    EXPECT_EQ(m1.getCell(1, 0), 10);
    EXPECT_EQ(m1.getCell(1, 1), 11);
    EXPECT_EQ(m1.getCell(1, 2), 12);

    // EMPTY MATRIX
    Matrix<int> m2;
    m2.insertCol(0, {10, 11, 12});
    EXPECT_EQ(m2.dimH(), 1);
    EXPECT_EQ(m2.dimV(), 3);
    EXPECT_EQ(m2.getCell(0, 0), 10);
    EXPECT_EQ(m2.getCell(0, 1), 11);
    EXPECT_EQ(m2.getCell(0, 2), 12);

    // OUT OF RANGE - EMPTY MATRIX
    Matrix<int> m3;
    EXPECT_THROW(m3.insertCol(1, {10, 11, 12}), std::out_of_range);

    // OUT OF RANGE - 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_THROW(m4.insertCol(4, {10}), std::out_of_range);

    // INVALID SIZE
    EXPECT_THROW(m4.insertCol(0, {10, 11, 12, 13}), std::invalid_argument);
}

/** Test pushRowFront method of Matrix class */
TEST(MatrixTest, pushRowFront)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    m1.pushRowFront({1, 2, 3});
    EXPECT_EQ(m1.getRow(0), std::vector<int>({1, 2, 3}));

    // 2x3 MATRIX
    Matrix<int> m2 = {{4, 5, 6}, {7, 8, 9}};
    m2.pushRowFront({1, 2, 3});
    EXPECT_EQ(m2.getRow(0), std::vector<int>({1, 2, 3}));
}

/** Test pushRowBack method of Matrix class */
TEST(MatrixTest, pushRowBack)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    m1.pushRowBack({1, 2, 3});
    EXPECT_EQ(m1.getRow(0), std::vector<int>({1, 2, 3}));

    // 2x3 MATRIX
    Matrix<int> m2 = {{4, 5, 6}, {7, 8, 9}};
    m2.pushRowBack({1, 2, 3});
    EXPECT_EQ(m2.getRow(2), std::vector<int>({1, 2, 3}));
}

/** Test pushColFront method of Matrix class */
TEST(MatrixTest, pushColFront)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    m1.pushColFront({1, 2, 3});
    EXPECT_EQ(m1.getCell(0, 0), 1);
    EXPECT_EQ(m1.getCell(0, 1), 2);
    EXPECT_EQ(m1.getCell(0, 2), 3);

    // 2x3 MATRIX
    Matrix<int> m2 = {{4, 5, 6}, {7, 8, 9}};
    m2.pushColFront({1, 2});
    EXPECT_EQ(m2.getCell(0, 0), 1);
    EXPECT_EQ(m2.getCell(0, 1), 2);
}

/** Test pushColBack method of Matrix class */
TEST(MatrixTest, pushColBack)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    m1.pushColBack({1, 2, 3});
    EXPECT_EQ(m1.getCell(0, 0), 1);
    EXPECT_EQ(m1.getCell(0, 1), 2);
    EXPECT_EQ(m1.getCell(0, 2), 3);

    // 2x3 MATRIX
    Matrix<int> m2 = {{4, 5, 6}, {7, 8, 9}};
    m2.pushColBack({1, 2});
    EXPECT_EQ(m2.getCell(3, 0), 1);
    EXPECT_EQ(m2.getCell(3, 1), 2);
}

TEST(MatrixTest, findRow)
{
    // 3x3 MATRIX - FIND
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.findRow({4, 5, 6}), 1);
    EXPECT_EQ(m.findRow([](std::vector<int> row)
                        { return row.at(0) == row.at(1) - 1 && row.at(1) == row.at(2) - 1; }),
              0);

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.findRow({10, 11, 12}), -1);
    EXPECT_EQ(m.findRow({10, 11, 12, 13}), -1);

    // 3x1 MATRIX - FIND
    Matrix<int> m2 = {{1}, {2}, {3}};
    EXPECT_EQ(m2.findRow({2}), 1);
    EXPECT_EQ(m2.findRow([](std::vector<int> row)
                         { return row.at(0) == 2; }),
              1);

    // 3x1 MATRIX - NOT FIND
    EXPECT_EQ(m2.findRow({10}), -1);

    // 1x3 MATRIX - FIND
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_EQ(m3.findRow({1, 2, 3}), 0);
    EXPECT_EQ(m3.findRow([](std::vector<int> row)
                         { return row.at(2) == 3; }),
              0);

    // 1x3 MATRIX - NOT FIND
    EXPECT_EQ(m3.findRow({10, 11, 12}), -1);

    // EMPTY MATRIX
    Matrix<int> m4;
    EXPECT_EQ(m4.findRow({1, 2, 3}), -1);
}

/** Test findCol method of Matrix class */
TEST(MatrixTest, findCol)
{
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 3x3 MATRIX - FIND
    EXPECT_EQ(m.findCol({2, 5, 8}), 1);

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.findCol({10, 11, 12}), -1);
    EXPECT_EQ(m.findCol({10, 11, 12, 13}), -1);

    // 3x1 MATRIX - FIND
    Matrix<int> m2 = {{1}, {2}, {3}};
    EXPECT_EQ(m2.findCol({1, 2, 3}), 0);

    // 3x1 MATRIX - NOT FIND
    EXPECT_EQ(m2.findCol({10}), -1);

    // 1x3 MATRIX - FIND
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_EQ(m3.findCol({2}), 1);

    // 1x3 MATRIX - NOT FIND
    EXPECT_EQ(m3.findCol({10, 11, 12}), -1);

    // EMPTY MATRIX
    Matrix<int> m4;
    EXPECT_EQ(m4.findCol({1, 2, 3}), -1);
}

/** Test find method of Matrix class */
TEST(MatrixTest, find)
{
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 3x3 MATRIX - FIND
    EXPECT_EQ(m.find(5), std::make_tuple(1, 1));

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.find(10), std::make_tuple(-1, -1));
}

/** Test removeRow method of Matrix class */
TEST(MatrixTest, removeRow)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // REMOVE FIRST ROW
    m1.removeRow(0);
    EXPECT_EQ(m1.getRow(0), std::vector<int>({4, 5, 6}));
    EXPECT_EQ(m1.getRow(1), std::vector<int>({7, 8, 9}));

    // REMOVE LAST ROW
    m1.removeRow(1);
    EXPECT_EQ(m1.getRow(0), std::vector<int>({4, 5, 6}));

    // REMOVE ONLY ROW
    m1.removeRow(0);
    EXPECT_TRUE(m1.isEmpty());

    // EMPTY MATRIX
    Matrix<int> m2;
    EXPECT_THROW(m2.removeRow(0), std::out_of_range);

    // OUT OF RANGE
    EXPECT_THROW(m1.removeRow(0), std::out_of_range);
}

/** Test removeCol method of Matrix class */
TEST(MatrixTest, removeCol)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // REMOVE FIRST COLUMN
    m1.removeCol(0);
    EXPECT_EQ(m1.dimH(), 2);
    EXPECT_EQ(m1.dimV(), 3);
    EXPECT_EQ(m1.getFlatCol(0), std::vector<int>({2, 5, 8}));
    EXPECT_EQ(m1.getFlatCol(1), std::vector<int>({3, 6, 9}));

    // REMOVE LAST COLUMN
    m1.removeCol(1);
    EXPECT_EQ(m1.dimH(), 1);
    EXPECT_EQ(m1.dimV(), 3);
    EXPECT_EQ(m1.getFlatCol(0), std::vector<int>({2, 5, 8}));

    // REMOVE ONLY COLUMN
    m1.removeCol(0);
    EXPECT_TRUE(m1.isEmpty());

    // EMPTY MATRIX
    Matrix<int> m2;
    EXPECT_THROW(m2.removeCol(0), std::out_of_range);

    // OUT OF RANGE
    EXPECT_THROW(m1.removeCol(0), std::out_of_range);
}

// ==================================================
// CHECK METHODS
/** Test isEmpty method of Matrix class */
TEST(MatrixTest, isEmpty)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isEmpty());

    // NON-EMPTY 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_FALSE(m2.isEmpty());

    // NON-EMPTY 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    EXPECT_FALSE(m3.isEmpty());

    // NON-EMPTY 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_FALSE(m4.isEmpty());
}

/** Test isSquare method of Matrix class */
TEST(MatrixTest, isSquare)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isSquare());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(m2.isSquare());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isSquare());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isSquare());
}

/** Test isDiagonal method of Matrix class */
TEST(MatrixTest, isDiagonal)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isDiagonal());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};
    EXPECT_TRUE(m2.isDiagonal());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isDiagonal());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isDiagonal());
}

/** Test isIdentity method of Matrix class */
TEST(MatrixTest, isIdentity)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isIdentity());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    EXPECT_TRUE(m2.isIdentity());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isIdentity());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isIdentity());
}

TEST(MatrixTest, isSymmetric)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isSymmetric());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_TRUE(m2.isSymmetric());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isSymmetric());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isSymmetric());
}

/** Test isUpperTriangular method of Matrix class */
TEST(MatrixTest, isUpperTriangular)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isUpperTriangular());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {0, 5, 6}, {0, 0, 9}};
    EXPECT_TRUE(m2.isUpperTriangular());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isUpperTriangular());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isUpperTriangular());
}

/** Test isLowerTriangular method of Matrix class */
TEST(MatrixTest, isLowerTriangular)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isLowerTriangular());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 0, 0}, {4, 5, 0}, {7, 8, 9}};
    EXPECT_TRUE(m2.isLowerTriangular());

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isLowerTriangular());

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isLowerTriangular());
}

/** Test isAll method of Matrix class */
TEST(MatrixTest, isAll)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_TRUE(m1.isAll([](int x)
                         { return x == 0; }));

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_FALSE(m2.isAll(0));
    EXPECT_FALSE(m2.isAll([](int x)
                          { return x == 0; }));
    EXPECT_TRUE(m2.isAll([](int x)
                         { return x > 0; }));

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isAll([](int x)
                          { return x == 0; }));

    EXPECT_TRUE(m3.isAll([](int x)
                         { return x > 0; }));

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m4.isAll([](int x)
                          { return x == 0; }));

    EXPECT_TRUE(m4.isAll([](int x)
                         { return x > 0; }));

    // FILL MATRIX WITH 4
    Matrix<int> m5(3, 3, 4);
    EXPECT_TRUE(m5.isAll(4));
    EXPECT_FALSE(m5.isAll(2));
}

/** Test isAny method of Matrix class */
TEST(MatrixTest, isAny)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_FALSE(m1.isAny([](int x)
                          { return x == 0; }));

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {2, 5, 6}, {3, 6, 9}};
    EXPECT_FALSE(m2.isAny([](int x)
                          { return x == 0; }));

    EXPECT_TRUE(m2.isAny(1));
    EXPECT_TRUE(m2.isAny([](int x)
                         { return x == 5; }));

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_FALSE(m3.isAny(5));
    EXPECT_FALSE(m3.isAny([](int x)
                          { return x == 0; }));

    EXPECT_TRUE(m3.isAny(3));
    EXPECT_TRUE(m3.isAny([](int x)
                         { return x == 2; }));

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_FALSE(m3.isAny(5));
    EXPECT_FALSE(m4.isAny([](int x)
                          { return x == 0; }));

    EXPECT_TRUE(m3.isAny(2));
    EXPECT_TRUE(m4.isAny([](int x)
                         { return x == 2; }));
}

/** Test checkDim method of Matrix class */
TEST(MatrixTest, checkDim)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_NO_THROW(m1.checkDim(std::tuple<size_t, size_t>(0, 0)));
    EXPECT_THROW(m1.checkDim(std::tuple<size_t, size_t>(1, 1)), std::invalid_argument);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    Matrix<int> m3 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkDim(std::tuple<size_t, size_t>(2, 3)));
    EXPECT_NO_THROW(m2.checkDim(m3));
    EXPECT_THROW(m2.checkDim(std::tuple<size_t, size_t>(3, 1)), std::invalid_argument);
    EXPECT_THROW(m2.checkDim(m1), std::invalid_argument);
}

/** Test checkValidRow method of Matrix class */
TEST(MatrixTest, checkValidRow)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_THROW(m1.checkValidRow({0}), std::invalid_argument);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkValidRow({0, 1, 2}));
    EXPECT_THROW(m2.checkValidRow({1}), std::invalid_argument);
}

/** Test checkValidCol method of Matrix class */
TEST(MatrixTest, checkValidCol)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_THROW(m1.checkValidCol({0}), std::invalid_argument);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkValidCol({0, 1}));
    EXPECT_THROW(m2.checkValidCol({3, 3, 4}), std::invalid_argument);
}

/** Test checkIdRow method of Matrix class */
TEST(MatrixTest, checkIdRow)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_THROW(m1.checkIdRow(0), std::out_of_range);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkIdRow(0));
    EXPECT_THROW(m2.checkIdRow(3), std::out_of_range);
}

/** Test checkIdCol method of Matrix class */
TEST(MatrixTest, checkIdCol)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_THROW(m1.checkIdCol(0), std::out_of_range);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkIdCol(0));
    EXPECT_THROW(m2.checkIdCol(3), std::out_of_range);
}

/** Test checkIdExpected method of Matrix class */
TEST(MatrixTest, checkIdExpected)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_NO_THROW(m1.checkIdExpected(0, 0));
    EXPECT_THROW(m1.checkIdExpected(1, 0), std::out_of_range);

    // 2x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {3, 6, 9}};
    EXPECT_NO_THROW(m2.checkIdExpected(2, 0, 3));
    EXPECT_NO_THROW(m2.checkIdExpected(2, 0, 2));
    EXPECT_NO_THROW(m2.checkIdExpected(3, 3));
}

// ==================================================
// STATISTICS METHODS
/** Test min method of Matrix class */
TEST(MatrixTest, min)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_EQ(m1.min(), std::vector<int>());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, -2, 3}, {3, 6, 9}, {-2, 4, 6}};
    EXPECT_EQ(m2.min(0), std::vector<int>({-2, 3, -2}));
    EXPECT_EQ(m2.min(1), std::vector<int>({-2, -2, 3}));

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_EQ(m3.min(0), std::vector<int>({1}));
    EXPECT_EQ(m3.min(1), std::vector<int>({1, 2, 3}));

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_EQ(m4.min(0), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(m4.min(1), std::vector<int>({1}));

    // 1x3 STRING MATRIX
    Matrix<std::string> m5 = {{"a", "b", "c"}};
    EXPECT_EQ(m5.min(0), std::vector<std::string>({"a"}));
    EXPECT_EQ(m5.min(1), std::vector<std::string>({"a", "b", "c"}));

    // INVALID AXIS
    EXPECT_THROW(m5.min(2), std::invalid_argument);
}

/** Test max method of Matrix class */
TEST(MatrixTest, max)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    EXPECT_EQ(m1.max(), std::vector<int>());

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, -2, 3}, {3, 6, 9}, {-2, 4, 6}};
    EXPECT_EQ(m2.max(0), std::vector<int>({3, 9, 6}));
    EXPECT_EQ(m2.max(1), std::vector<int>({3, 6, 9}));

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_EQ(m3.max(0), std::vector<int>({3}));
    EXPECT_EQ(m3.max(1), std::vector<int>({1, 2, 3}));

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_EQ(m4.max(0), std::vector<int>({1, 2, 3}));
    EXPECT_EQ(m4.max(1), std::vector<int>({3}));

    // 1x3 STRING MATRIX
    Matrix<std::string> m5 = {{"a", "b", "c"}};
    EXPECT_EQ(m5.max(0), std::vector<std::string>({"c"}));
    EXPECT_EQ(m5.max(1), std::vector<std::string>({"a", "b", "c"}));

    // INVALID AXIS
    EXPECT_THROW(m5.max(2), std::invalid_argument);
}

// ==================================================
// OTHER METHODS
/** Test clear method of Matrix class */
TEST(MatrixTest, clear)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    m1.clear();
    EXPECT_TRUE(m1.isEmpty());

    // NON-EMPTY 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m2.clear();
    EXPECT_TRUE(m2.isEmpty());

    // NON-EMPTY 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    m3.clear();
    EXPECT_TRUE(m3.isEmpty());

    // NON-EMPTY 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    m4.clear();
    EXPECT_TRUE(m4.isEmpty());
}

/** Test copy method of Matrix class */
TEST(MatrixTest, copy)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    Matrix<int> m1Copy = m1.copy();
    EXPECT_EQ(m1, m1Copy);

    // NON-EMPTY 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2Copy = m2.copy();
    EXPECT_EQ(m2, m2Copy);

    // NON-EMPTY 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    Matrix<int> m3Copy = m3.copy();
    EXPECT_EQ(m3, m3Copy);

    // AFTER COPY, CHANGE ORIGINAL MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    Matrix<int> m4Copy = m4.copy();
    m4.setCell(0, 0, 10);
    EXPECT_NE(m4, m4Copy);
}

/** Test apply method of Matrix class */
TEST(MatrixTest, apply)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> expected = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    m1.apply([](int x, size_t *i, size_t *j)
             { return x * 2; });
    EXPECT_EQ(m1, expected);

    // 1x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}};
    Matrix<int> expected2 = {{2, 3, 4}};
    m2.apply([](int x, size_t *i, size_t *j)
             { return x + 1; });
    EXPECT_EQ(m2, expected2);

    // 3x1 MATRIX
    Matrix<int> m3 = {{1}, {2}, {3}};
    Matrix<int> expected3 = {{2}, {3}, {4}};
    m3.apply([](int x, size_t *i, size_t *j)
             { return x + 1; });
    EXPECT_EQ(m3, expected3);
}

/** Test map method of Matrix class */
TEST(MatrixTest, map)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> expected = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix<int> m2 = m1.map([](int x, size_t *i, size_t *j)
                            { return x * 2; });

    EXPECT_EQ(m2, expected);

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    Matrix<int> expected2 = {{2, 3, 4}};
    Matrix<int> m4 = m3.map([](int x, size_t *i, size_t *j)
                            { return x + 1; });
    EXPECT_EQ(m4, expected2);
}

/** Test fill method of Matrix class */
TEST(MatrixTest, fill)
{
    // 3x3 MATRIX
    Matrix<int> m1 = Matrix<int>::zeros(3, 3);
    Matrix<int> expected = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    m1.fill(1);
    EXPECT_EQ(m1, expected);

    // 1x3 MATRIX
    Matrix<int> m2 = Matrix<int>::zeros(3, 1);
    Matrix<int> expected2 = {{1, 1, 1}};
    m2.fill(1);
    EXPECT_EQ(m2, expected2);

    // 3x1 MATRIX
    Matrix<int> m3 = Matrix<int>::zeros(1, 3);
    Matrix<int> expected3 = {{1}, {1}, {1}};
    m3.fill(1);
    EXPECT_EQ(m3, expected3);
}

// ==================================================
// STATIC METHODS
/** Test isMatrix method of Matrix class */
TEST(MatrixTest, isMatrix)
{
    // EMPTY MATRIX
    EXPECT_TRUE(Matrix<int>::isMatrix({}));

    // 3x3 MATRIX
    EXPECT_TRUE(Matrix<int>::isMatrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));

    // 1x3 MATRIX
    EXPECT_TRUE(Matrix<int>::isMatrix({{1, 2, 3}}));

    // 3x1 MATRIX
    EXPECT_TRUE(Matrix<int>::isMatrix({{1}, {2}, {3}}));

    // INVALID MATRIX - NOT RECTANGULAR
    EXPECT_FALSE(Matrix<int>::isMatrix({{1, 2}, {3, 4, 5}}));
}

/** Test flattenVector method of Matrix class */
TEST(MatrixTest, flattenVector)
{
    // EMPTY VECTOR
    EXPECT_EQ(Matrix<int>::flattenVector({}), std::vector<int>());

    // 2D VECTOR
    EXPECT_EQ(Matrix<int>::flattenVector({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

/** Test randint method of Matrix class */
TEST(MatrixTest, randint)
{
    // 1x3 MATRIX
    Matrix<int> m1 = Matrix<int>::randint(1, 3, 0, 10);
    EXPECT_EQ(m1.dimH(), 1);
    EXPECT_EQ(m1.dimV(), 3);

    for (size_t i = 0; i < m1.dimH(); i++)
        for (size_t j = 0; j < m1.dimV(); j++)
        {
            EXPECT_GE(m1.getCell(i, j), 0);
            EXPECT_LE(m1.getCell(i, j), 10);
        }

    // 3x1 MATRIX
    Matrix<int> m2 = Matrix<int>::randint(3, 1, 0, 10);
    EXPECT_EQ(m2.dimH(), 3);
    EXPECT_EQ(m2.dimV(), 1);

    for (size_t i = 0; i < m2.dimH(); i++)
        for (size_t j = 0; j < m2.dimV(); j++)
        {
            EXPECT_GE(m2.getCell(i, j), 0);
            EXPECT_LE(m2.getCell(i, j), 10);
        }

    // 3x3 MATRIX
    Matrix<int> m3 = Matrix<int>::randint(3, 3, 0, 10);
    EXPECT_EQ(m3.dimH(), 3);
    EXPECT_EQ(m3.dimV(), 3);

    for (size_t i = 0; i < m3.dimH(); i++)
        for (size_t j = 0; j < m3.dimV(); j++)
        {
            EXPECT_GE(m3.getCell(i, j), 0);
            EXPECT_LE(m3.getCell(i, j), 10);
        }
}

/** Test zeros method of Matrix class */
TEST(MatrixTest, zeros)
{
    // 1x3 MATRIX
    Matrix<int> m1 = Matrix<int>::zeros(1, 3);
    EXPECT_EQ(m1.dimH(), 1);
    EXPECT_EQ(m1.dimV(), 3);
    for (size_t i = 0; i < m1.dimH(); i++)
        for (size_t j = 0; j < m1.dimV(); j++)
            EXPECT_EQ(m1.getCell(i, j), 0);

    // 3x1 MATRIX
    Matrix<int> m2 = Matrix<int>::zeros(3, 1);
    EXPECT_EQ(m2.dimH(), 3);
    EXPECT_EQ(m2.dimV(), 1);
    for (size_t i = 0; i < m2.dimH(); i++)
        for (size_t j = 0; j < m2.dimV(); j++)
            EXPECT_EQ(m2.getCell(i, j), 0);

    // 3x3 MATRIX
    Matrix<int> m3 = Matrix<int>::zeros(3, 3);
    EXPECT_EQ(m3.dimH(), 3);
    EXPECT_EQ(m3.dimV(), 3);
    for (size_t i = 0; i < m3.dimH(); i++)
        for (size_t j = 0; j < m3.dimV(); j++)
            EXPECT_EQ(m3.getCell(i, j), 0);
}

/** Test identity method of Matrix class */
TEST(MatrixTest, identity)
{
    // EMPTY MATRIX
    Matrix<int> m = Matrix<int>::identity(0);
    EXPECT_TRUE(m.isEmpty());

    // 1x3 MATRIX
    Matrix<int> m1 = Matrix<int>::identity(1);
    EXPECT_EQ(m1.dimH(), 1);
    EXPECT_EQ(m1.dimV(), 1);
    EXPECT_EQ(m1.getCell(0, 0), 1);

    // 2x2 MATRIX
    Matrix<int> m2 = Matrix<int>::identity(2);
    EXPECT_EQ(m2.dimH(), 2);
    EXPECT_EQ(m2.dimV(), 2);
    EXPECT_EQ(m2.getCell(0, 0), 1);
    EXPECT_EQ(m2.getCell(0, 1), 0);
    EXPECT_EQ(m2.getCell(1, 0), 0);
    EXPECT_EQ(m2.getCell(1, 1), 1);
}

// ==================================================
// OPERATOR METHODS
/** Test operatorEquals method of Matrix class */
TEST(MatrixTest, operatorEquals)
{
    // EQUAL 3x3 MATRICES
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(m1 == m2);

    // EQUAL 1x3 MATRICES
    Matrix<int> m3 = {{1, 2, 3}};
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_TRUE(m3 == m4);

    // EQUAL 3x1 MATRICES
    Matrix<int> m5 = {{1}, {2}, {3}};
    Matrix<int> m6 = {{1}, {2}, {3}};
    EXPECT_TRUE(m5 == m6);

    // EQUAL EMPTY MATRICES
    EXPECT_TRUE(Matrix<int>() == Matrix<int>());

    // NOT EQUAL 3x3 MATRICES
    Matrix<int> m7 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m8 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    EXPECT_TRUE(m7 != m8);
}

/** Test operatorStream method of Matrix class */
TEST(MatrixTest, operatorStream)
{
    // EMPTY MATRIX
    Matrix<int> m1;
    std::stringstream ss1;
    ss1 << m1;
    EXPECT_EQ(ss1.str(), "[]");

    // 3x3 MATRIX
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::stringstream ss2;
    ss2 << m2;
    EXPECT_EQ(ss2.str(), "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    std::stringstream ss3;
    ss3 << m3;
    EXPECT_EQ(ss3.str(), "[[1, 2, 3]]");

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    std::stringstream ss4;
    ss4 << m4;
    EXPECT_EQ(ss4.str(), "[[1], [2], [3]]");
}

/** Test operatorMap method of Matrix class */
TEST(MatrixTest, operatorMap)
{
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{6, 5, 4}, {3, 2, 1}};

    // EQUAL DIMENSIONS
    EXPECT_NO_THROW(m1.operatorMap(std::plus<int>(), m1));

    // NOT EQUAL DIMENSIONS
    EXPECT_THROW(m1.operatorMap(std::plus<int>(), m2), std::invalid_argument);
}

/** Test operatorSum method of Matrix class */
TEST(MatrixTest, operatorSum)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m3 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    EXPECT_EQ(m1 + m2, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{1, 2, 3}};
    Matrix<int> m5 = {{4, 5, 6}};
    Matrix<int> m6 = {{5, 7, 9}};
    EXPECT_EQ(m4 + m5, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{1}, {2}, {3}};
    Matrix<int> m8 = {{4}, {5}, {6}};
    Matrix<int> m9 = {{5}, {7}, {9}};
    EXPECT_EQ(m7 + m8, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    Matrix<int> m12;
    EXPECT_EQ(m10 + m11, m12);

    // NOT EQUAL DIMENSIONS
    Matrix<int> m13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m13 + m14, std::invalid_argument);
}

/** Test operatorSub method of Matrix class */
TEST(MatrixTest, operatorSub)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m1 - m2, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{5, 7, 9}};
    Matrix<int> m5 = {{1, 2, 3}};
    Matrix<int> m6 = {{4, 5, 6}};
    EXPECT_EQ(m4 - m5, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{5}, {7}, {9}};
    Matrix<int> m8 = {{1}, {2}, {3}};
    Matrix<int> m9 = {{4}, {5}, {6}};
    EXPECT_EQ(m7 - m8, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    Matrix<int> m12;
    EXPECT_EQ(m10 - m11, m12);

    // NOT EQUAL DIMENSIONS
    Matrix<int> m13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m13 - m14, std::invalid_argument);
}

/** Test operatorMul method of Matrix class */
TEST(MatrixTest, operatorMul)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix<int> m3 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    EXPECT_EQ(m1 * m2, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{5, 7, 9}};
    Matrix<int> m5 = {{1}, {2}, {3}};
    Matrix<int> m6 = {{46}};
    EXPECT_EQ(m4 * m5, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{1}, {2}, {3}};
    Matrix<int> m8 = {{5, 7, 9}};
    Matrix<int> m9 = {{5, 7, 9}, {10, 14, 18}, {15, 21, 27}};
    EXPECT_EQ(m7 * m8, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    Matrix<int> m12;
    EXPECT_EQ(m10 * m11, m12);

    // NOT EQUAL DIMENSIONS
    Matrix<int> m13 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m14 = {{6, 5, 4}, {3, 2, 1}};
    EXPECT_THROW(m13 * m14, std::invalid_argument);
}

/** Test operatorPower method of Matrix class */
TEST(MatrixTest, operatorPower)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    EXPECT_EQ(m1 ^ 2, m2);

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_THROW(m3 ^ 2, std::invalid_argument);

    // 3x1 MATRIX
    Matrix<int> m5 = {{1}, {2}, {3}};
    EXPECT_THROW(m5 ^ 2, std::invalid_argument);

    // EMPTY MATRIX
    Matrix<int> m7;
    Matrix<int> m8;
    EXPECT_EQ(m7 ^ 2, m8);
}

/** Test operatorSumAssign method of Matrix class */
TEST(MatrixTest, operatorSumAssign)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m3 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    m1 += m2;
    EXPECT_EQ(m1, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{1, 2, 3}};
    Matrix<int> m5 = {{4, 5, 6}};
    Matrix<int> m6 = {{5, 7, 9}};
    m4 += m5;
    EXPECT_EQ(m4, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{1}, {2}, {3}};
    Matrix<int> m8 = {{4}, {5}, {6}};
    Matrix<int> m9 = {{5}, {7}, {9}};
    m7 += m8;
    EXPECT_EQ(m7, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    m10 += m11;
    EXPECT_EQ(m10, Matrix<int>());
}

/** Test operatorSubAssign method of Matrix class */
TEST(MatrixTest, operatorSubAssign)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};
    Matrix<int> m2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    m1 -= m2;
    EXPECT_EQ(m1, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{5, 7, 9}};
    Matrix<int> m5 = {{1, 2, 3}};
    Matrix<int> m6 = {{4, 5, 6}};
    m4 -= m5;
    EXPECT_EQ(m4, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{5}, {7}, {9}};
    Matrix<int> m8 = {{1}, {2}, {3}};
    Matrix<int> m9 = {{4}, {5}, {6}};
    m7 -= m8;
    EXPECT_EQ(m7, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    m10 -= m11;
    EXPECT_EQ(m10, Matrix<int>());
}

/** Test operatorMulAssign method of Matrix class */
TEST(MatrixTest, operatorMulAssign)
{
    // 3x3 MATRICES
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    Matrix<int> m3 = {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}};
    m1 *= m2;
    EXPECT_EQ(m1, m3);

    // 1x3 MATRICES
    Matrix<int> m4 = {{5, 7, 9}};
    Matrix<int> m5 = {{1}, {2}, {3}};
    Matrix<int> m6 = {{46}};
    m4 *= m5;
    EXPECT_EQ(m4, m6);

    // 3x1 MATRICES
    Matrix<int> m7 = {{1}, {2}, {3}};
    Matrix<int> m8 = {{5, 7, 9}};
    Matrix<int> m9 = {{5, 7, 9}, {10, 14, 18}, {15, 21, 27}};
    m7 *= m8;
    EXPECT_EQ(m7, m9);

    // EMPTY MATRICES
    Matrix<int> m10;
    Matrix<int> m11;
    m10 *= m11;
    EXPECT_EQ(m10, Matrix<int>());
}

/** Test operatorPowerAssign method of Matrix class */
TEST(MatrixTest, operatorPowerAssign)
{
    // 3x3 MATRIX
    Matrix<int> m1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int> m2 = {{30, 36, 42}, {66, 81, 96}, {102, 126, 150}};
    m1 ^= 2;
    EXPECT_EQ(m1, m2);

    // 1x3 MATRIX
    Matrix<int> m3 = {{1, 2, 3}};
    EXPECT_THROW(m3 ^= 2, std::invalid_argument);

    // 3x1 MATRIX
    Matrix<int> m4 = {{1}, {2}, {3}};
    EXPECT_THROW(m4 ^= 2, std::invalid_argument);

    // EMPTY MATRIX
    Matrix<int> m5;
    m5 ^= 2;
    EXPECT_EQ(m5, Matrix<int>());
}

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
