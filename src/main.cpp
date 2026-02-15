#include<iostream>
#include<core/classes/diff/Manifold.hpp>
#include<core/classes/compute/partical_differentiation.hpp>

double func1(std::vector<double> x){
    return 1;
}

double func2(std::vector<double> x){
    return x[0]*x[0];
}

double func3(std::vector<double> x){
    return 1;
}

double func4(std::vector<double> x){
    return 1;
}

int main(){
    std::vector<std::function<double(const std::vector<double>&)>> funcs = {func1, func2};
    Metric* metric = new Metric(funcs);

    Manifold* manifold = new Manifold(metric);
    std::vector<double> point = {1,0};
    std::cout << diffBy(metric->getComponent(1,0),point, 1) << std::endl;

    ChristoffelSymbols* christo = new ChristoffelSymbols(metric);
    int n = 2;
    for(int k = 0;k != n;k++){
        for(int i = 0;i != n;i++){
            for(int j = 0;j != n;j++){
                std::cout << christo->computeChristoffelSybmbolsAtPoint(point, k, i, j) << std::endl;
            }
        }
    }

    std::cout << "-----------------" << std::endl;

    Geodesic* geodesic = new Geodesic(christo);

    double time = 0.f;
    double dx = 0.002f;
    std::vector<double> state = {point[0], point[1], 0.f, 1.f};

    for(int i = 0;i != 1000;i++){
        std::vector<double> nextState = geodesic->getGeodesicNextState(time, state, dx);
        if(i % 100 == 0){
            std::cout << nextState[0] << std::endl;
            std::cout << nextState[1] << std::endl;
            std::cout << "----------------- | t = " << time << std::endl;
        }
        state = nextState;
        time += dx;
    }


    delete metric;
    delete manifold;
    return 0;
}
