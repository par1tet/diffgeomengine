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

#include<src/classes/compute/partical_differentiation.tpp>