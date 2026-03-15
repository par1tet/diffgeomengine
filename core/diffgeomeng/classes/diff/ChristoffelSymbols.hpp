#pragma once

#include<diffgeomeng/classes/diff/Metric.hpp>
#include<diffgeomeng/utility/types.hpp>
#include <stdexcept>
#include <diffgeomeng/classes/compute/partical_differentiation.hpp>

template <size_t N>
class ChristoffelSymbols{
public:
    ChristoffelSymbols(Metric<N>* metric);

    double computeChristoffelSybmbolsAtPoint(Point<N> point, int k, int i, int j);
    Metric<N>* getMetric();
private:
    Metric<N>* currentMetric;
};

/////////// IMPLEMENTATION /////////////

template <size_t N>
ChristoffelSymbols<N>::ChristoffelSymbols(Metric<N>* metric): currentMetric(metric){
};

template <size_t N>
double ChristoffelSymbols<N>::computeChristoffelSybmbolsAtPoint(Point<N> point, int k, int i, int j){
    int n = this->currentMetric->getSize();
    if(n != N){
        throw std::invalid_argument("Matrix must have NxN size as in the template");
    }
    auto& metric = *(this->currentMetric);

    // Γᵏᵢⱼ = ½ gᵏˡ (∂ᵢ gⱼₗ + ∂ⱼ gᵢₗ - ∂ₗ gᵢⱼ)

    double result = 0;
    
    if(metric.getIsDiagonal()){
        if((k == i) && (i == j)){
            result = diffBy(metric.getComponent<N>(i, k), point, k) / metric.getComponent<N>(i, k)(point);
        }else if(((k == i) && (i != j))){
            result = diffBy(metric.getComponent<N>(i, k), point, j) / metric.getComponent<N>(i, k)(point);
        }else if(((k == j) && (i != j))){
            result = diffBy(metric.getComponent<N>(j, k), point, i) / metric.getComponent<N>(j, k)(point);
        }else if(((k != i) && (i == j))){
            result = -diffBy(metric.getComponent<N>(j, i), point, k) / metric.getComponent<N>(k, k)(point);
        }else{
            result = 0;
        }
    }else{
        for(int l = 0;l != metric.getSize();l++){
            result += metric.getReverseInPoint<N>(point, k, l) * (diffBy<N>(metric.getComponent<N>(j,l), point, i) + diffBy<N>(metric.getComponent<N>(i,l), point, j) - diffBy<N>(metric.getComponent<N>(i,j), point, l));
        }
    }
    

    return result/2;
}

template <size_t N>
Metric<N>* ChristoffelSymbols<N>::getMetric(){
    return this->currentMetric;
}