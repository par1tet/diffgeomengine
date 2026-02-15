#include<core/classes/compute/rk4_realize.hpp>
#include<iostream>

std::vector<double> computeRK4(double time, std::function<std::vector<double>(double, std::vector<double>)> func, const std::vector<double>& initCondition, double dx){
    std::vector<double> k1 = func(time, initCondition);

    std::vector<double> tempInitCondition(initCondition.size());
    for(int i = 0;i != initCondition.size();i++){
        tempInitCondition[i] = initCondition[i] + (dx*k1[i])/2;
    }

    std::vector<double> k2 = func(time + dx/2, tempInitCondition);

    for(int i = 0;i != initCondition.size();i++){
        tempInitCondition[i] = initCondition[i] + (dx*k2[i])/2;
    }

    std::vector<double> k3 = func(time + dx/2, tempInitCondition);

    for(int i = 0;i != initCondition.size();i++){
        tempInitCondition[i] = initCondition[i] + (dx*k3[i]);
    }

    std::vector<double> k4 = func(time + dx, tempInitCondition);

    std::vector<double> solutions(initCondition.size());

    for(int i = 0;i != initCondition.size();i++){
        solutions[i] = initCondition[i] + dx/6 * (k1[i] + 2*(k2[i] + k3[i]) + k4[i]);
    } 

    return solutions;
}