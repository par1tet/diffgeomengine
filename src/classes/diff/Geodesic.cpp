#include<core/classes/diff/Geodesic.hpp>
#include<core/classes/compute/rk4_realize.hpp>
#include<iostream>
#include<cmath>

Geodesic::Geodesic(ChristoffelSymbols* christo): christoffelSymbols(christo){};


Geodesic::~Geodesic(){
    delete this->christoffelSymbols;
}

State Geodesic::geodesicRhs(double time, State& initState,
        std::function<std::vector<double>(std::vector<double>)> force){
    State dInit(initState.dimension);

    for(int i = 0;i != initState.dimension;i++){
        dInit.x0[i] = initState.v0[i];
    }

    for(int k = 0;k != initState.dimension;k++){
        double acc = 0.f;

        for(int i = 0;i != initState.dimension;i++){
            for(int j = 0;j != initState.dimension; j++){
                acc += this->christoffelSymbols->computeChristoffelSybmbolsAtPoint(initState.x0, k, i, j) * initState.v0[i] * initState.v0[j];
            }
        }
        acc += force(initState.x0)[k];

        dInit.v0[k] = -acc;
    }

    return dInit;
}

State Geodesic::computeGeodesicNextState(double time, State& initState, double dx,
         std::function<std::vector<double>(std::vector<double>)> force){
    return computeRK4(time,
        [this, force](double t, State state) {
            return this->geodesicRhs(t, state, force);
        },initState, dx);
}

Curve Geodesic::computeGeodesic(double T, State& initState, double dx,
         std::function<std::vector<double>(std::vector<double>)> force){
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