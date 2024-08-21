// algebra.cpp

#include "algebra.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include <format>

// 定义命名空间 algebra
namespace algebra {

// 矩阵创建函数实现
// 根据给定的行数、列数、矩阵类型和边界值创建不同类型的矩阵
template<typename T>
MATRIX<T> create_matrix(std::size_t rows, std::size_t columns, std::optional<MatrixType> type,
                        std::optional<T> lowerBound, std::optional<T> upperBound) {
    MATRIX<T> matrix(rows, std::vector<T>(columns));

    if (type == MatrixType::Identity) {
        if (rows != columns) {
            throw std::invalid_argument("Identity matrix must be square (rows == columns).");
        }
        for (std::size_t i = 0; i < rows; ++i) {
            matrix[i][i] = 1;
        }
    } else if (type == MatrixType::Ones) {
        for (auto& row : matrix) {
            std::fill(row.begin(), row.end(), 1);
        }
    } else if (type == MatrixType::Zeros) {
        // 默认是零矩阵，已初始化完成
    } else if (type == MatrixType::Random) {
        if (!lowerBound.has_value() || !upperBound.has_value() || lowerBound >= upperBound) {
            throw std::invalid_argument("For Random matrix, valid lowerBound and upperBound must be provided.");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dist(*lowerBound, *upperBound);
        for (auto& row : matrix) {
            for (auto& elem : row) {
                elem = dist(gen);
            }
        }
    }

    return matrix;
}

// 矩阵显示函数实现
// 打印矩阵内容到控制台
template<typename T>
void display(const MATRIX<T>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << std::format("{:^7}", elem) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// 矩阵相加或相减函数实现
// 根据给定的操作符（加或减）对两个矩阵进行相应操作
template<typename T>
MATRIX<T> sum_sub(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB, std::optional<std::string> operation) {
    std::size_t rows = matrixA.size();
    std::size_t columns = matrixA[0].size();

    if (matrixB.size() != rows || matrixB[0].size() != columns) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition or subtraction.");
    }

    MATRIX<T> result(rows, std::vector<T>(columns));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
            if (operation.value_or("sum") == "sub") {
                result[i][j] = matrixA[i][j] - matrixB[i][j];
            } else {
                result[i][j] = matrixA[i][j] + matrixB[i][j];
            }
        }
    }

    return result;
}

// 标量乘法函数实现
// 对矩阵进行标量乘法操作
template<typename T>
MATRIX<T> multiply(const MATRIX<T>& matrix, const T scalar) {
    MATRIX<T> result = matrix;
    for (auto& row : result) {
        for (auto& elem : row) {
            elem *= scalar;
        }
    }
    return result;
}

// 矩阵乘法函数实现
// 对两个矩阵进行矩阵乘法操作
template<typename T>
MATRIX<T> multiply(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB) {
    std::size_t rowsA = matrixA.size();
    std::size_t colsA = matrixA[0].size();
    std::size_t rowsB = matrixB.size();
    std::size_t colsB = matrixB[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Number of columns in matrixA must match number of rows in matrixB.");
    }

    MATRIX<T> result(rowsA, std::vector<T>(colsB, 0));
    for (std::size_t i = 0; i < rowsA; ++i) {
        for (std::size_t j = 0; j < colsB; ++j) {
            for (std::size_t k = 0; k < colsA; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return result;
}

// Hadamard 积函数实现
// 对两个矩阵进行Hadamard积（元素对应相乘）操作
template<typename T>
MATRIX<T> hadamard_product(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB) {
    std::size_t rows = matrixA.size();
    std::size_t columns = matrixA[0].size();

    if (matrixB.size() != rows || matrixB[0].size() != columns) {
        throw std::invalid_argument("Matrices must have the same dimensions for Hadamard product.");
    }

    MATRIX<T> result(rows, std::vector<T>(columns));
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
            result[i][j] = matrixA[i][j] * matrixB[i][j];
        }
    }

    return result;
}

} // namespace algebra