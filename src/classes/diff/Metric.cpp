#include<core/classes/diff/Metric.hpp>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<core/classes/compute/invert_matrix.hpp>

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
                metricComponents[i][j] = nullptr;
            }
        }
    }
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
    return invertComponentMatrix((this->metricComponents), point).at(i).at(j);
}

int Metric::getSize(){
    return metricComponents[0].size();
}
