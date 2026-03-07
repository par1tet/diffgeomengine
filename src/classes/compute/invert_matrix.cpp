#include<diffgeomeng/classes/compute/invert_matrix.hpp>
#include<iostream>

std::vector<std::vector<double>> invertComponentMatrix(
    const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>& componentMatrix,
    const std::vector<double>& point) {
    
    size_t n = componentMatrix.size();
    if (n == 0) {
        throw std::invalid_argument("Matrix is empty");
    }

    for (const auto& row : componentMatrix) {
        if (row.size() != n) {
            throw std::invalid_argument("Component matrix must be square");
        }
    }

    std::vector<std::vector<double>> A(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if(componentMatrix[i][j] == nullptr){
                continue;
            }
            A[i][j] = componentMatrix[i][j](point);
        }
    }
    
    std::vector<std::vector<double>> LU = A;
    std::vector<int> permutations(n);
    for (size_t i = 0; i < n; ++i) {
        permutations[i] = i;
    }

    for (size_t k = 0; k < n; ++k) {
        double maxElement = std::abs(LU[k][k]);
        size_t maxRow = k;
        for (size_t i = k + 1; i < n; ++i) {
            if (std::abs(LU[i][k]) > maxElement) {
                maxElement = std::abs(LU[i][k]);
                maxRow = i;
            }
        }
        
        // if (maxElement < 1e-12) {
        //     throw std::runtime_error("Matrix is singular or nearly singular at given point");
        // }
        
        if (maxRow != k) {
            std::swap(LU[k], LU[maxRow]);
            std::swap(permutations[k], permutations[maxRow]);
        }
        
        for (size_t i = k + 1; i < n; ++i) {
            LU[i][k] /= LU[k][k];
            for (size_t j = k + 1; j < n; ++j) {
                LU[i][j] -= LU[i][k] * LU[k][j];
            }
        }
    }
    
    std::vector<std::vector<double>> inverse(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }
    
    std::vector<std::vector<double>> permutedIdentity(n, std::vector<double>(n));
    for (size_t i = 0; i < n; ++i) {
        permutedIdentity[i] = inverse[permutations[i]];
    }
    
    for (size_t col = 0; col < n; ++col) {
        std::vector<double> y(n);
        for (size_t i = 0; i < n; ++i) {
            double sum = 0.0;
            for (size_t j = 0; j < i; ++j) {
                sum += LU[i][j] * y[j];
            }
            y[i] = permutedIdentity[i][col] - sum;
        }
        
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0.0;
            for (size_t j = i + 1; j < n; ++j) {
                sum += LU[i][j] * inverse[j][col];
            }
            inverse[i][col] = (y[i] - sum) / LU[i][i];
        }
    }
    
    return inverse;
}