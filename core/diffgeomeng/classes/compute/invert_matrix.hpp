#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<diffgeomeng/utility/types.hpp>
#include<iostream>

template <size_t N>
std::array<std::array<double, N>, N> invertComponentMatrix(
    const std::array<std::array<std::function<double(const std::array<double, N>&)>, N>, N>& componentMatrix,
    const Point<N>& point);
 
/////////// IMPLEMENTATION ////////////

template <size_t N>
std::array<std::array<double, N>, N> invertComponentMatrix(
    const std::array<std::array<std::function<double(const std::array<double, N>&)>, N>, N>& componentMatrix,
    const Point<N>& point) {
    
    size_t n = componentMatrix.size();
    if (n == 0) {
        throw std::invalid_argument("Matrix is empty");
    }

    if(n != N){
        throw std::invalid_argument("Matrix must have NxN size as in the template");
    }

    for (const auto& row : componentMatrix) {
        if (row.size() != n) {
            throw std::invalid_argument("Component matrix must be square");
        }
    }

    std::array<std::array<double, N>, N> A(n, std::array<double, N>(n));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if(componentMatrix[i][j] == nullptr){
                continue;
            }
            A[i][j] = componentMatrix[i][j](point);
        }
    }
    
    std::array<std::array<double, N>, N> LU = A;
    std::array<int, N> permutations;
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
    
    std::array<std::array<double, N>, N> inverse(n, std::array<double, N>(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        inverse[i][i] = 1.0;
    }
    
    std::array<std::array<double, N>, N> permutedIdentity(n, std::array<double, N>(n));
    for (size_t i = 0; i < n; ++i) {
        permutedIdentity[i] = inverse[permutations[i]];
    }
    
    for (size_t col = 0; col < n; ++col) {
        std::array<double, N> y(n);
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