#include<diffgeomeng/classes/diff/Geodesic.hpp>
#include<diffgeomeng/classes/compute/rk4_realize.hpp>
#include<iostream>
#include<cmath>
#include<diffgeomeng/utility/functions.hpp>

Geodesic::Geodesic(ChristoffelSymbols* christo): christoffelSymbols(christo){};


Geodesic::~Geodesic(){
    delete this->christoffelSymbols;
}


template<size_t N>
State<N> Geodesic::geodesicRhs(double time, State<N>& initState,
        std::function<std::array<double, N>(std::array<double, N>)> force, bool isLogging){
    State dInit(initState.dimension);
    
    dInit.x0 = initState.v0;

    for(int k = 0;k != initState.dimension;k++){
        double acc = 0.f;

        for(int i = 0;i != initState.dimension;i++){
            for(int j = 0;j != initState.dimension; j++){
                acc -= this->christoffelSymbols->computeChristoffelSybmbolsAtPoint(initState.x0, k, i, j) * initState.v0[i] * initState.v0[j];
            }
        }
        std::vector<double> forceVector = force(initState.x0);
        if(forceVector.size() != initState.dimension){
            throw std::runtime_error("Force vector dimension is not equal initState dimension");
        }
        acc += forceVector[k];

        dInit.v0[k] = acc;
    }

    for (int i = 0; i < initState.dimension; i++) {
        if (std::isnan(dInit.v0[i]) || std::isinf(dInit.v0[i])) {
            throw std::runtime_error("NaN in geodesic RHS");
        }
    }

    std::cout << "<|--AFTER COMPUTION RHS--|>" << std::endl;
    if(isLogging){
        std::cout << "<-----Positioin----->" << std::endl;

        for(int i = 0;i != initState.dimension;i++){
            std::cout << "coordinate " << i << " :" << initState.x0[i] << std::endl;
        }

        std::cout << "<-----Velocity----->" << std::endl;

        for(int i = 0;i != initState.dimension;i++){
            std::cout << "coordinate " << i << " :" << initState.v0[i] << std::endl;
        }
    }

    return dInit;
}

template<size_t N>
State<N> Geodesic::computeGeodesicNextState(double time, State<N>& initState, double dx,
         std::function<std::array<double, N>(std::array<double, N>)> force, bool isLogging){
    checkCorrectState<N>(initState);
    
    if(isLogging){
        std::cout << "<-----Positioin----->" << std::endl;

        for(int i = 0;i != initState.dimension;i++){
            std::cout << "coordinate " << i << " :" << initState.x0[i] << std::endl;
        }

        std::cout << "<-----Velocity----->" << std::endl;

        for(int i = 0;i != initState.dimension;i++){
            std::cout << "coordinate " << i << " :" << initState.v0[i] << std::endl;
        }
    }

    return computeRK4<N>(time,
        [this, force, isLogging](double t, State<N> state) {
            return this->geodesicRhs(t, state, force, isLogging);
        },initState, dx);
}

template<size_t N>
Curve Geodesic::computeGeodesic(double T, State<N>& initState, double dx,
         std::function<std::array<double, N>(std::array<double, N>)> force){
    checkCorrectState(initState);
    Curve geodesic;
    State newInitState = initState;

    for(double time;time <= T;time+=dx){
        //if(newInitState[0] > M_PI - 0.1)
        //    break;
        newInitState = this->computeGeodesicNextState(time, newInitState, dx, force);
        geodesic.points.push_back(newInitState.x0);
    }


    for(int i = 0;i != geodesic.points.size();i++){
        geodesic.points[i].resize(initState.dimension);
    }

    return geodesic;
}

ChristoffelSymbols* Geodesic::getChristoffelSymbols(){
    return this->christoffelSymbols;
}