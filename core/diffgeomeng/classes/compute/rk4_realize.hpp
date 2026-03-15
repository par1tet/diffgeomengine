#pragma once

#include<functional>
#include<vector>
#include<diffgeomeng/utility/types.hpp>

template <size_t N>
State<N> computeRK4(double time, std::function<State<N>(double, State<N>)> func, const State<N>& initState, double dx);