#pragma once

#include<functional>
#include<vector>
#include<diffgeomeng/utility/types.hpp>
#include<exception>
#include<diffgeomeng/utility/functions.hpp>

/////////// IMPLEMENTATION /////////////

// in state need x and p |!| not u
template<size_t N>
inline State<N> computeEuler(Hamiltonian<N>* ham,const State<N>& initStateP, double dx){
    checkCorrectState<N>(initStateP);

    State<N> integrateState = initStateP;

    Vector<N> halfKick_first = ham->dHdx(integrateState.x0, integrateState.v0);

    for(size_t i = 0;i < N;i++){
        integrateState.v0[i] -= * dx * halfKick_first[i];
    }

    Vector<N> drift = ham->dHdp(integrateState.x0, integrateState.v0);

    for(size_t i = 0;i < N;i++){
        integrateState.x0[i] += dx * drift[i];
    }

    return integrateState;
}