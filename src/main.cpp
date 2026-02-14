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
    std::vector<double> point = {1,1};
    std::cout << diffBy(metric->getComponent(1,1),point, 1) << std::endl;

    ChristoffelSymbols* christo = new ChristoffelSymbols(metric);
    int n = 2;
    for(int k = 0;k != n;k++){
        for(int i = 0;i != n;i++){
            for(int j = 0;j != n;j++){
                std::cout << christo->computeChristoffelSybmbolsAtPoint(point, k, i, j) << std::endl;
            }
        }
    }

    delete metric;
    delete manifold;
    return 0;
}
