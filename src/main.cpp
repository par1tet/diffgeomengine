#include<iostream>
#include<core/classes/diff/Manifold.hpp>
#include<core/classes/compute/partical_differentiation.hpp>

double func1(std::vector<double> x){
    return 1;
}

double func2(std::vector<double> x){
    return x[1]*x[1];
}

int main(){
    std::vector<std::function<double(const std::vector<double>&)>> funcs = {func1, func2};
    Metric* metric = new Metric(funcs);

    Manifold* manifold = new Manifold(metric);

    delete metric;
    delete manifold;
    return 0;
}
