#include<core/classes/diff/ChristoffelSymbols.hpp>
#include <stdexcept>
#include <core/classes/compute/partical_differentiation.hpp>

ChristoffelSymbols::ChristoffelSymbols(Metric* metric): currentMetric(metric){};

void ChristoffelSymbols::computeAllChristoffelSybmbols(){
    int n = this->currentMetric->getSize();
    auto& metric = *(this->currentMetric);

    for(int k = 0;k != n;k++){
        for(int i = 0;i != n;i++){
            for(int j = 0;j != n;j++){
                this->symbolsComponents[k][i].push_back([this, k, i, j, &metric](std::vector<double> point) {
                    // Γᵏᵢⱼ = ½ gᵏˡ (∂ᵢ gⱼₗ + ∂ⱼ gᵢₗ - ∂ₗ gᵢⱼ)

                    double result = 0;

                    for(int l = 0;l != metric.getSize();l++){
                        result += metric.getReverseInPoint(point, k, l) * (diffBy(metric.getComponent(j,l), point, i) + diffBy(metric.getComponent(i,l), point, j) - diffBy(metric.getComponent(i,j), point, l));
                    }

                    return result/2;
                });

            }
        }
    }
}

std::function<double(const std::vector<double>&)> ChristoffelSymbols::getComponents(int k, int i, int j){
    if (i < 0 || static_cast<size_t>(i) >= this->currentMetric->getSize()) {
        throw std::out_of_range("Row index out of range");
    }
    
    if (j < 0 || static_cast<size_t>(j) >= this->currentMetric->getSize()) {
        throw std::out_of_range("Column index out of range");
    }

    if (k < 0 || static_cast<size_t>(j) >= this->currentMetric->getSize()) {
        throw std::out_of_range("Column index out of range");
    }
   
    return this->symbolsComponents[k][i][j];
}