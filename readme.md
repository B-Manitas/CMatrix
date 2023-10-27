# CMatrix: A Powerful C++ Matrix Library

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Status](https://img.shields.io/badge/Status-Active-green.svg)](https://github.com/B-Manitas/CMatrix)

CMatrix is a robust C++ matrix library designed to simplify matrix operations and provide extensive functionalities. This library is tailored for Data Science and Machine Learning projects, offering a versatile toolset for working with matrices.

## Table of Contents

1. [Installation](#installation)
2. [Example of Usage](#exemple-of-usage)
3. [Hierarchical Structure](#hierarchical-structure)
4. [Documentation](#documentation)
5. [See Also](#see-also)
6. [License](#license)

## Installation

To install the library, follow these steps:

1. Clone the repository using the following command:

```bash
git clone https://github.com/B-Manitas/CMatrix.git
```

2. Include the [`CMatrix.hpp`](include/CMatrix.hpp) file in your project.

## Exemple of Usage

Here's an example of how to use CMatrix:

```cpp
#include "CMatrix.hpp"

int main()
{
    // Create a 2x3 matrix
    cmatrix<int> mat = {{1, 2, 3}, {4, 5, 6}};

    // Create a random 3x2 matrix
    cmatrix<int> rand = cmatrix<int>::randint(3, 2, 0, 10);
    rand.print();

    // Performs a calculation on the matrix
    mat += ((rand * 2) - 1);

    // Print the transpose of the result
    mat.transpose().print();

    return 0;
}

>>> "[[18, 9], [5, 22], [20, 13]]"
```

## Hierarchical Structure

CMatrix is structured as follows:

| Class                                                        | Description                                                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------------------------------------------- |
| include                                                      |                                                                                             |
| [`CMatrix.hpp`](include/CMatrix.hpp)                         | The main template class that can work with any data type except bool.                       |
| src                                                          |                                                                                             |
| [`CMatrix.tpp`](include/CMatrix.tpp)                         | General methods of the class.                                                               |
| [`CMatrixConstructors.hpp`](include/CMatrixConstructors.tpp) | Implementation of class constructors.                                                       |
| [`CMatrixGetter.hpp`](include/CMatrixGetter.tpp)             | Methods to retrieve information about the matrix and access its elements.                   |
| [`CMatrixSetter.hpp`](include/CMatrixSetter.tpp)             | Methods to set data in the matrix.                                                          |
| [`CMatrixCheck.tpp`](include/CMatrixCheck.tpp)               | Methods to verify matrix conditions and perform checks before operations to prevent errors. |
| [`CMatrixManipulation.hpp`](include/CMatrixManipulation.tpp) | Methods to find elements in the matrix and transform it.                                    |
| [`CMatrixOperator.hpp`](include/CMatrixOperator.tpp)         | Implementation of various operators.                                                        |
| [`CMatrixStatic.hpp`](include/CMatrixStatic.tpp)             | Implementation of static methods of the class.                                              |
| [`CMatrixStatistics.hpp`](include/CMatrixStatistics.tpp)     | Methods to perform statistical operations on the matrix.                                    |
| test                                                         |                                                                                             |
| [`CMatrixTest.hpp`](test/CMatrixTest.tpp)                    | Contains the tests for the class.                                                           |

## Documentation

For detailed information on how to use CMatrix, consult the [documentation](docs/cmatrix.pdf).

## See Also

- [CDataFrame](https://github.com/B-Manitas/CDataFrame): A C++ DataFrame library for Data Science and Machine Learning projects.

## License

This project is licensed under the MIT License, ensuring its free and open availability to the community.
