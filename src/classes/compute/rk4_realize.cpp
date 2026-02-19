#include<core/classes/compute/rk4_realize.hpp>
#include<exception>
#include<core/utility/functions.hpp>

State computeRK4(double time, std::function<State(double, State)> func,const State& initState, double dx){
    checkCorrectState(initState);

    State k1 = func(time, initState);

    State tempinitState(initState.dimension);
    for(int i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k1.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k1.v0[i])/2;
    }

    State k2 = func(time + dx/2, tempinitState);

    for(int i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k2.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k2.v0[i])/2;
    }

    State k3 = func(time + dx/2, tempinitState);

    for(int i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k3.x0[i]);
        tempinitState.v0[i] = initState.v0[i] + (dx*k3.v0[i]);
    }

    State k4 = func(time + dx, tempinitState);

    State solutions(initState.dimension);

    for(int i = 0;i != initState.dimension;i++){
        solutions.x0[i] = initState.x0[i] + dx/6 * (k1.x0[i] + 2*(k2.x0[i] + k3.x0[i]) + k4.x0[i]);
        solutions.v0[i] = initState.v0[i] + dx/6 * (k1.v0[i] + 2*(k2.v0[i] + k3.v0[i]) + k4.v0[i]);
    } 

    return solutions;
}