#pragma once

#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include<diffgeomeng/utility/types.hpp>

template <size_t N>
std::array<std::array<double, N>, N> invertComponentMatrix(
    const std::array<std::array<std::function<double(const std::array<double, N>&)>, N>, N>& componentMatrix,
    const Point<N>& point);
 