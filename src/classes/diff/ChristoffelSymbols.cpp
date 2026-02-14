#include<core/classes/diff/ChristoffelSymbols.hpp>
#include <stdexcept>

ChristoffelSymbols::ChristoffelSymbols(Metric* metric): currentMetric(metric){};

ChristoffelSymbols::computeAllChristoffelSybmbols(){

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