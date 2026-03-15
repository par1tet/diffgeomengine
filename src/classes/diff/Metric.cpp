#include<diffgeomeng/classes/diff/Metric.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<diffgeomeng/classes/compute/invert_matrix.hpp>
#include <iostream>
#include <diffgeomeng/utility/types.hpp>

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

template<size_t N>
Point<N> zero(Point<N> x){
    return Point<N>();
}

Metric::Metric(const Components& components): metricComponents(components) {
    if(metricComponents.size() != metricComponents[0].size()){
        throw std::runtime_error("Matrix of components must be squared");
    }
};

template<size_t N>
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

template<size_t N>
std::function<double(const Point<N>&)> Metric::getComponent(int i, int j) {
    checkRightIndices(i, j, this->metricComponents);
  
    return metricComponents[i][j];
}

template<size_t N>
double Metric::getReverseInPoint(Point<N> point, int i, int j){
    checkRightIndices(i, j, this->metricComponents);

    return invertComponentMatrix((this->metricComponents), point)[i][j];
}

int Metric::getSize(){
    return metricComponents[0].size();
}

template<size_t N>
std::array<std::array<double, N>, N> Metric::getMatrixAtPoint(Point<N> point){
    int n = this->getSize();
    if(n != N){
        throw std::runtime_error("Dimension of point must equal dimension of manifold");
    }

    std::array<std::array<double, N>, N> matrix(std::array<double, N>());

    for(int i = 0;i != n;i++){
        for(int j = i;j != n;j++){
            matrix[i][j] = this->getComponent<N>(i, j)(point);
        }
    }

    return matrix;
}

bool Metric::getIsDiagonal(){
    return this->isDiagonal;
}

template<size_t N>
double Metric::getInvariant(State<N> state){
    double acc = 0;

    for(int i = 0;i != state.dimension;i++){
        for(int j = 0;j != state.dimension;j++){
            acc += this->getComponent<N>(i,j)(state.x0) * state.v0[i] * state.v0[j];
        }
    }

    return acc;
}