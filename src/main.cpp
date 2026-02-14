#include<iostream>
#include<core/classes/diff/Manifold.hpp>
#include<core/classes/compute/partical_differentiation.hpp>

double f(std::vector<double> x){
    return (x[0])*(x[0]);
}

int main(){
    Manifold* manifold = new Manifold(new Metric());
    //manifold->showmetric();
    std::vector<double> point{0};

    std::cout << diffBy(f, point, 0) << std::endl;

    return 0;
}
