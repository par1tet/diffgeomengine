#pragma once

#include<functional>
#include<vector>
#include<diffgeomeng/utility/types.hpp>

State computeRK4(double time, std::function<State(double, State)> func, const State& initState, double dx);