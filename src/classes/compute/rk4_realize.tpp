template<size_t N>
State<N> computeRK4(double time, std::function<State<N>(double, State<N>)> func,const State<N>& initState, double dx){
    checkCorrectState<N>(initState);

    State<N> k1 = func(time, initState);

    State<N> tempinitState(initState.dimension);
    for(size_t i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k1.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k1.v0[i])/2;
    }

    State<N> k2 = func(time + dx/2, tempinitState);

    for(size_t i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k2.x0[i])/2;
        tempinitState.v0[i] = initState.v0[i] + (dx*k2.v0[i])/2;
    }

    State<N> k3 = func(time + dx/2, tempinitState);

    for(size_t i = 0;i != initState.dimension;i++){
        tempinitState.x0[i] = initState.x0[i] + (dx*k3.x0[i]);
        tempinitState.v0[i] = initState.v0[i] + (dx*k3.v0[i]);
    }

    State<N> k4 = func(time + dx, tempinitState);

    State<N> solutions(initState.dimension);

    for(size_t i = 0;i != initState.dimension;i++){
        solutions.x0[i] = initState.x0[i] + dx/6 * (k1.x0[i] + 2*(k2.x0[i] + k3.x0[i]) + k4.x0[i]);
        solutions.v0[i] = initState.v0[i] + dx/6 * (k1.v0[i] + 2*(k2.v0[i] + k3.v0[i]) + k4.v0[i]);
    } 

    return solutions;
}