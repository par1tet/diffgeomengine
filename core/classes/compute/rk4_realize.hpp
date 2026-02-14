#include<functional>
#include<vector>

std::vector<double> computeRK4(double time, std::function<std::vector<double>(double, std::vector<double>)> func, const std::vector<double>& initCondition, double dx=0.02){