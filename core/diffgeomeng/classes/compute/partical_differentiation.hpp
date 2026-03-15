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
double diffBy(std::function<double(const Point<N>&)> func, const Point<N>& point, int p_index, double dx){
    if(func == nullptr){
        return 0;
    }

    if (p_index < 0 || p_index >= N) {
        throw std::out_of_range("Index out of bounds in diffBy");
    }
    
    Point<N> copyPoint = Point<N>(point);

    copyPoint.x[p_index] += dx;
    double dPlus = func(copyPoint);

    copyPoint.x[p_index] -= 2*dx;
    double dMinus = func(copyPoint);

    return (dPlus - dMinus)/(2*dx);
}
