#pragma once

#include<diffgeomeng/classes/compute/verlet_realize.hpp>

/////////// IMPLEMENTATION /////////////

// in state need x and p |!| not u
template<size_t N>
inline State<N> computeYoshida4(Hamiltonian<N>* ham,const State<N>& initStateP, double dx){
    checkCorrectState<N>(initStateP);

    State<N> integrateState = initStateP;

    const double w1 = 1.35120719195966;
    const double w2 = -1.70241438391932;

    integrateState = computeVerlet(ham, integrateState, w1 * dx);
    integrateState = computeVerlet(ham, integrateState, w2 * dx);
    integrateState = computeVerlet(ham, integrateState, w1 * dx); 

    return integrateState;
}