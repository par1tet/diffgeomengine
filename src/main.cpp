#include<iostream>
#include<core/classes/diff/Manifold.hpp>
#include<core/classes/compute/partical_differentiation.hpp>
#include<cmath>

double getInv(Metric* metric, std::vector<double> state){
    int n = metric->getSize();
    double acc = 0;
    std::vector<double> x(n);

    for(int k = 0;k != n;k++){
        x[k] = state[k];
    }


    for(int i = 0;i != n;i++){
        for(int j = 0;j != n;j++){
            acc += metric->getComponent(i,j)(x) * state[n + i] * state[n + j];
        }
    }

    return acc;
}

double func1(std::vector<double> x){
    return -(1 - (2/x[1]));
}

double func2(std::vector<double> x){
    return 1/(1-(2/x[1]));
}

double func3(std::vector<double> x){
    return x[1]*x[1];
}

double func4(std::vector<double> x){
    return 1;
}

int main(){
    std::vector<std::function<double(const std::vector<double>&)>> funcs = {func1, func2, func3};
    Metric* metric = new Metric(funcs);
    Manifold* manifold = new Manifold(metric);
    ChristoffelSymbols* christo = new ChristoffelSymbols(metric);

    // std::vector<double> point = {1,0};
    // int n = 2;
    // for(int k = 0;k != n;k++){
    //     for(int i = 0;i != n;i++){
    //         for(int j = 0;j != n;j++){
    //             std::cout << christo->computeChristoffelSybmbolsAtPoint(point, k, i, j) << std::endl;
    //         }
    //     }
    // }

    Geodesic* geodesic = new Geodesic(christo);

    double time = 0.f;
    double dx = 0.002f;
    std::vector<double> state = {0.f, 6.f, 0.f, 1.1726f, 0.f, 0.061622f};

    for(int i = 0;i != 10000;i++){
        std::vector<double> nextState = geodesic->getGeodesicNextState(time, state, dx);
        if(i % 500 == 0){
            std::cout << nextState[0] << std::endl;
            std::cout << nextState[1] << std::endl;
            std::cout << nextState[2] << std::endl;
            std::cout << "INV: " << getInv(metric, state);
            std::cout << "----------------- | t = " << time << std::endl;
        }
        state = nextState;
        time += dx;
    }


    delete metric;
    delete manifold;
    return 0;
}
