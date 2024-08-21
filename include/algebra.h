#ifndef AUT_AP_2024_Spring_HW1
#define AUT_AP_2024_Spring_HW1

#include <vector>
#include <optional>
#include <string>

//命名空间algebra
class algebra {

    //矩阵类型定义
    template<typename T>
    using MATRIX = std::vector<std::vector<T>>;
    enum class MatrixType {Zeros, Ones, Identity, Random};

    //矩阵创建函数
    template<typename T>
    MATRIX<T> create_matrix(std::size_t row, std::size_t columns, std::optional<MatrixType> type = MatrixType::Zeros, std::
    optional<T> lowerBound = std::nullopt, std::optional<T> upperBound = std::nullopt);

    //矩阵显示函数
    template<typename T>
    void display(const MATRIX<T>& matrix);
    
    // 矩阵相加或相减函数
    template<typename T>
    MATRIX<T> sum_sub(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB, std::optional<std::string> operation = "sum");

    // 标量乘法函数
    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrix, const T scalar);

    // 矩阵乘法函数
    template<typename T>
    MATRIX<T> multiply(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB);

    // Hadamard 积函数
    template<typename T>
    MATRIX<T> hadamard_product(const MATRIX<T>& matrixA, const MATRIX<T>& matrixB);

}
#include "algebra.cpp"
#endif //AUT_AP_2024_Spring_HW1
