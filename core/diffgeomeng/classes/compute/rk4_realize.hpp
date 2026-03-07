#pragma once

#include<functional>
#include<vector>
#include<core/utility/types.hpp>

State computeRK4(double time, std::function<State(double, State)> func, const State& initState, double dx);