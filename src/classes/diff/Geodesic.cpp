#include<core/classes/diff/Geodesic.hpp>
#include<core/classes/compute/rk4_realize.hpp>
#include<iostream>
#include<cmath>

Geodesic::Geodesic(ChristoffelSymbols* christo): currentChristoffelSymbols(christo){};

std::vector<double> Geodesic::geodesicRhs(double time, std::vector<double>& initConditioins,
        std::function<std::vector<double>(std::vector<double>)> force){
    std::vector<double> dInit(initConditioins.size());
    int n = (int)(initConditioins.size()/2);

    std::vector<double> x(n), v(n);

    for(int i = 0;i != n;i++){
        x[i] = initConditioins[i];
        v[i] = initConditioins[i+n];
    }

    for(int i = 0;i != n;i++){
        dInit[i] = v[i];
    }

    for(int k = 0;k != n;k++){
        double acc = 0.f;

        for(int i = 0;i != n;i++){
            for(int j = 0;j != n; j++){
                acc += this->currentChristoffelSymbols->computeChristoffelSybmbolsAtPoint(x, k, i, j)* v[i] * v[j];
            }
        }
        acc += force(x)[k];

        dInit[k+n] = -acc;
    }

    return dInit;
}

std::vector<double> Geodesic::computeGeodesicNextState(double time, std::vector<double>& initConditions, double dx,
         std::function<std::vector<double>(std::vector<double>)> force){
    return computeRK4(time,
        [this, force](double t, std::vector<double> y) {
            return this->geodesicRhs(t, y, force);
        },initConditions, dx);
}

Curve Geodesic::computeGeodesic(double T, std::vector<double>& initConditions, double dx,
         std::function<std::vector<double>(std::vector<double>)> force){
    Curve geodesic;
    std::vector<double> newInitConditions = initConditions;
    int n = initConditions.size()/2;

    for(double time;time <= T;time+=dx){
        //if(newInitConditions[0] > M_PI - 0.1)
        //    break;
        newInitConditions = this->computeGeodesicNextState(time, newInitConditions, dx, force);
        geodesic.points.push_back(newInitConditions);
    }


    for(int i = 0;i != geodesic.points.size();i++){
        geodesic.points[i].resize(n);
    }

    return geodesic;
}