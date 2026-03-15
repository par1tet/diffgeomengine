#pragma once

#include<vector>
#include <functional>
#include <diffgeomeng/utility/types.hpp>
#include <stdexcept>

template <size_t N>
double diffBy(std::function<double(const Point<N>&)> func, 
             const Point<N>& point,
                int p_index,
                double dx=1e-4);

/////////// IMPLEMENTATION /////////////

template <size_t N>
double diffBy(std::function<double(const std::vector<double>&)> func, const std::vector<double>& point, int p_index, double dx){
    if(func == nullptr){
        return 0;
    }

    if (p_index < 0 || p_index >= point.size()) {
        throw std::out_of_range("Index out of bounds in diffBy");
    }
    
    std::array<double, N> copyPoint(point);

    copyPoint[p_index] += dx;
    double dPlus = func(copyPoint);

    copyPoint[p_index] -= 2*dx;
    double dMinus = func(copyPoint);

    return (dPlus - dMinus)/(2*dx);
}
