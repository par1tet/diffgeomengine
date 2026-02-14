#include<core/classes/compute/partical_differentiation.hpp>
#include <stdexcept>

double diffBy(std::function<double(const std::vector<double>&)> func, const std::vector<double>& point, int p_index, double dx){
    if(func == nullptr){
        return 0;
    }

    if (p_index < 0 || p_index >= point.size()) {
        throw std::out_of_range("Index out of bounds in diffBy");
    }
    
    std::vector<double> copyPoint(point);

    copyPoint[p_index] += dx;
    double dPlus = func(copyPoint);

    copyPoint[p_index] -= 2*dx;
    double dMinus = func(copyPoint);

    return (dPlus - dMinus)/(2*dx);
}
