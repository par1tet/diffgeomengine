#include<core/classes/diff/ChristoffelSymbols.hpp>
#include <stdexcept>
#include <core/classes/compute/partical_differentiation.hpp>
#include <iostream>

ChristoffelSymbols::ChristoffelSymbols(Metric* metric): currentMetric(metric){
};

double ChristoffelSymbols::computeChristoffelSybmbolsAtPoint(std::vector<double> point, int k, int i, int j){
    int n = this->currentMetric->getSize();


    auto& metric = *(this->currentMetric);

    // Γᵏᵢⱼ = ½ gᵏˡ (∂ᵢ gⱼₗ + ∂ⱼ gᵢₗ - ∂ₗ gᵢⱼ)

    double result = 0;

    for(int l = 0;l != metric.getSize();l++){
        result += metric.getReverseInPoint(point, k, l) * (diffBy(metric.getComponent(j,l), point, i) + diffBy(metric.getComponent(i,l), point, j) - diffBy(metric.getComponent(i,j), point, l));
    }

    return result/2;
}
