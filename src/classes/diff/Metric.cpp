#include<diffgeomeng/classes/diff/Metric.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<diffgeomeng/classes/compute/invert_matrix.hpp>
#include <iostream>
#include <diffgeomeng/utility/types.hpp>

template<size_t N>
double funczeroPoint(Point<N> x){
    return 0;
}


template<size_t N>
void checkRightIndices(int i, int j, Components<N> components){
    if (i < 0 || static_cast<size_t>(i) >= N) {
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
Point<N> zeroPoint(Point<N> x){
    return Point<N>();
}

template<size_t N>
Metric<N>::Metric(const Components<N>& components): metricComponents(components) {
    if(metricComponents.size() != metricComponents[0].size()){
        throw std::runtime_error("Matrix of components must be squared");
    }
};

template<size_t N>
Metric<N>::Metric(const std::array<std::function<double(const std::array<double, N>&)>, N>& components) {
    if(N < 1){
        throw std::runtime_error("Count of components less then one");
    }
    
    metricComponents = Components<N>();
    
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (i == j) {
                metricComponents[i][j] = components[i];
            }
        }
    }
    this->isDiagonal = true;
}

template<size_t N>
std::function<double(const Point<N>&)> Metric<N>::getComponent(int i, int j) {
    checkRightIndices(i, j, this->metricComponents);
  
    return metricComponents[i][j];
}

template<size_t N>
double Metric<N>::getReverseInPoint(Point<N> point, int i, int j){
    checkRightIndices(i, j, this->metricComponents);

    return invertComponentMatrix((this->metricComponents), point)[i][j];
}

template<size_t N>
int Metric<N>::getSize(){
    return N;
}

template<size_t N>
std::array<std::array<double, N>, N> Metric<N>::getMatrixAtPoint(Point<N> point){
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

template<size_t N>
bool Metric<N>::getIsDiagonal(){
    return this->isDiagonal;
}

template<size_t N>
double Metric<N>::getInvariant(State<N> state){
    double acc = 0;

    for(int i = 0;i != state.dimension;i++){
        for(int j = 0;j != state.dimension;j++){
            acc += this->getComponent<N>(i,j)(state.x0) * state.v0[i] * state.v0[j];
        }
    }

    return acc;
}