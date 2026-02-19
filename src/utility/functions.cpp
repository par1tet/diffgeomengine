#include<core/utility/functions.hpp>

void checkCorrectState(State state){
    if((state.dimension != state.x0.size()) || (state.dimension != state.v0.size())){
        throw std::runtime_error("Size of x0 and v0 must equal dimension of the state");
    }

    if(state.dimension < 1){
        throw std::runtime_error("Dimension of state must be greater then one");
    }
}
