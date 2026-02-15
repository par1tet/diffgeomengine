#include<core/classes/diff/Geodesic.hpp>
#include<core/classes/compute/rk4_realize.hpp>

Geodesic::Geodesic(ChristoffelSymbols* christo): currentChristoffelSymbols(christo){};

std::vector<double> Geodesic::geodesicRhs(double time, std::vector<double>& initConditioins){
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

        dInit[k+n] = -acc;
    }

    return dInit;
}

std::vector<double> Geodesic::getGeodesicNextState(double time, std::vector<double>& initConditions, double dx){
    return computeRK4(time,
        [this](double t, std::vector<double> y) {
            return this->geodesicRhs(t, y);
        },initConditions, dx);
}