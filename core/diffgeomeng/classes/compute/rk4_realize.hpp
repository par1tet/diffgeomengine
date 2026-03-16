#pragma once

#include<functional>
#include<vector>
#include<diffgeomeng/utility/types.hpp>
#include<exception>
#include<diffgeomeng/utility/functions.hpp>

/////////// IMPLEMENTATION /////////////

template<size_t N, typename RHS>
inline State<N> computeRK4(double time, RHS&& rhs,const State<N>& initState, double dx){
    checkCorrectState<N>(initState);

    State<N> k1 = rhs(time, initState);

    State<N> tempinitState = State<N>();
    for(size_t i = 0;i < N;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k1.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k1.v0[i])/2;
    }

    State<N> k2 = rhs(time + dx/2, tempinitState);

    for(size_t i = 0;i < N;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k2.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k2.v0[i])/2;
    }

    State<N> k3 = rhs(time + dx/2, tempinitState);

    for(size_t i = 0;i != N;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k3.x0[i]);
        tempinitState.v0[i] = initState.v0[i] + (dx*k3.v0[i]);
    }

    State<N> k4 = rhs(time + dx, tempinitState);

    State<N> solutions = State<N>();

    for(size_t i = 0;i < N;i++){
        solutions.x0[i] = initState.x0[i] + dx/6 * (k1.x0[i] + 2*(k2.x0[i] + k3.x0[i]) + k4.x0[i]);
        solutions.v0[i] = initState.v0[i] + dx/6 * (k1.v0[i] + 2*(k2.v0[i] + k3.v0[i]) + k4.v0[i]);
    } 

    return solutions;
}