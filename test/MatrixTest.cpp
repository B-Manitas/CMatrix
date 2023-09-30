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

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.getCol(3), std::out_of_range);
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
    EXPECT_THROW(m4.setRow(0, {"a", "b", "c"}), std::invalid_argument);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m1.setRow(3, {10, 11, 12}), std::invalid_argument);
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
    EXPECT_THROW(m4.setCol(0, {"a", "b", "c"}), std::invalid_argument);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.setCol(3, {10, 11, 12}), std::invalid_argument);
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
    EXPECT_THROW(m4.setCell(0, 0, "a"), std::invalid_argument);

    // OUT OF RANGE - ROW
    EXPECT_THROW(m.setCell(3, 0, 10), std::invalid_argument);

    // OUT OF RANGE - COLUMN
    EXPECT_THROW(m.setCell(0, 3, 10), std::invalid_argument);
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
    EXPECT_THROW(m3.insertRow(1, {10, 11, 12}), std::invalid_argument);

    // OUT OF RANGE - 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_THROW(m4.insertRow(2, {10, 11, 12}), std::invalid_argument);

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
    EXPECT_THROW(m3.insertCol(1, {10, 11, 12}), std::invalid_argument);

    // OUT OF RANGE - 1x3 MATRIX
    Matrix<int> m4 = {{1, 2, 3}};
    EXPECT_THROW(m4.insertCol(2, {10, 11, 12}), std::invalid_argument);
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
    // Test findRow with existing row
    // Expected returns the correct row index
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_EQ(m.findRow({4, 5, 6}), 1);

    // Test findRow with non-existing row
    // Expected returns -1
    EXPECT_EQ(m.findRow({10, 11, 12}), -1);
}

/** Test findCol method of Matrix class */
TEST(MatrixTest, findCol)
{
    Matrix<int> m = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    // 3x3 MATRIX - FIND
    EXPECT_EQ(m.findCol({2, 5, 8}), 1);

    // 3x3 MATRIX - NOT FIND
    EXPECT_EQ(m.findCol({10, 11, 12}), -1);
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

GTEST_API_ int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
