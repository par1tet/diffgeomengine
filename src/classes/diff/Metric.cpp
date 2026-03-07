#include<diffgeomeng/classes/diff/Metric.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<diffgeomeng/classes/compute/invert_matrix.hpp>
#include <iostream>

double funcZero(std::vector<double> x){
    return 0;
}

void checkRightIndices(int i, int j, Components components){
    if (i < 0 || static_cast<size_t>(i) >= components.size()) {
        throw std::out_of_range("Row index out of range");
    }
    
    if (j < 0 || static_cast<size_t>(j) >= components[i].size()) {
        throw std::out_of_range("Column index out of range");
    }
    
    if (components[i][j] == nullptr) {
        throw std::runtime_error("Component at (" + std::to_string(i) + "," + 
                                 std::to_string(j) + ") is not initialized");
    }
}

std::vector<double> zero(std::vector<double> x){
    return std::vector<double>(x.size(),0);
}

Metric::Metric(const Components& components): metricComponents(components) {
    if(metricComponents.size() != metricComponents[0].size()){
        throw std::runtime_error("Matrix of components must be squared");
    }
};

Metric::Metric(const std::vector<std::function<double(const std::vector<double>&)>>& components) {
    size_t n = components.size();

    if(n < 1){
        throw std::runtime_error("Count of components less then one");
    }
    
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
    checkRightIndices(i, j, this->metricComponents);
  
    return metricComponents[i][j];
}

double Metric::getReverseInPoint(std::vector<double> point, int i, int j){
    checkRightIndices(i, j, this->metricComponents);

    return invertComponentMatrix((this->metricComponents), point)[i][j];
}

int Metric::getSize(){
    return metricComponents[0].size();
}


std::vector<std::vector<double>> Metric::getMatrixAtPoint(std::vector<double> point){
    int n = this->getSize();
    if(n != point.size()){
        throw std::runtime_error("Dimension of point must equal dimension of manifold");
    }

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

double Metric::getInvariant(State state){
    double acc = 0;

    for(int i = 0;i != state.dimension;i++){
        for(int j = 0;j != state.dimension;j++){
            acc += this->getComponent(i,j)(state.x0) * state.v0[i] * state.v0[j];
        }
    }

    return acc;
}