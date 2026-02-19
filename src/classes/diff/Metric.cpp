#include<core/classes/diff/Metric.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<core/classes/compute/invert_matrix.hpp>
#include <iostream>

double funcZero(std::vector<double> x){
    return 0;
}

std::vector<double> zero(std::vector<double> x){
    return std::vector<double>(x.size(),0);
}

Metric::Metric(const Components& components): metricComponents(components) {};

Metric::Metric(const std::vector<std::function<double(const std::vector<double>&)>>& components) {
    size_t n = components.size();
    
    metricComponents.resize(n);
    
    for (size_t i = 0; i < n; ++i) {
        metricComponents[i].resize(n);
        
        for (size_t j = 0; j < n; ++j) {
            if (i == j) {
                metricComponents[i][j] = components[i];
            } else {
                metricComponents[i][j] = funcZero;
            }
        }
    }
    this->isDiagonal = true;
}

std::function<double(const std::vector<double>&)> Metric::getComponent(int i, int j) {
    if (i < 0 || static_cast<size_t>(i) >= metricComponents.size()) {
        throw std::out_of_range("Row index out of range");
    }
    
    if (j < 0 || static_cast<size_t>(j) >= metricComponents[i].size()) {
        throw std::out_of_range("Column index out of range");
    }
    
    if (metricComponents[i][j] == nullptr) {
        throw std::runtime_error("Component at (" + std::to_string(i) + "," + 
                                 std::to_string(j) + ") is not initialized");
    }
   
    return metricComponents[i][j];
}

double Metric::getReverseInPoint(std::vector<double> point, int i, int j){
    return invertComponentMatrix((this->metricComponents), point)[i][j];
}

int Metric::getSize(){
    return metricComponents[0].size();
}


std::vector<std::vector<double>> Metric::getMatrixAtPoint(std::vector<double> point){
    int n = this->getSize();
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0));

    for(int i = 0;i != n;i++){
        for(int j = i;j != n;j++){
            matrix[i][j] = this->getComponent(i, j)(point);
        }
    }

    return matrix;
}

bool Metric::getIsDiagonal(){
    return this->isDiagonal;
}

double Metric::getInvariant(std::vector<double> state){
    int n = this->getSize();
    double acc = 0;
    std::vector<double> x(n);

    for(int k = 0;k != n;k++){
        x[k] = state[k];
    }


    for(int i = 0;i != n;i++){
        for(int j = 0;j != n;j++){
            acc += this->getComponent(i,j)(x) * state[n + i] * state[n + j];
        }
    }

    return acc;
}