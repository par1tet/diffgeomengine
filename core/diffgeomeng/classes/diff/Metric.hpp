#pragma once

#include<vector>
#include<functional>
#include<string>
#include<core/diffgeomeng/utility/types.hpp>

std::vector<double> zero(std::vector<double> x);

class Metric{
public:
    Metric(const Components&);
    Metric(const std::vector<std::function<double(const std::vector<double>&)>>&);

    std::function<double(const std::vector<double>&)> getComponent(int i, int j);
    double getReverseInPoint(std::vector<double> point, int i, int j);
    int getSize();
    std::vector<std::vector<double>> getMatrixAtPoint(std::vector<double> point);
    bool getIsDiagonal();
    double getInvariant(State state);

private:
    Components metricComponents;
    bool isDiagonal = false;
};