#pragma once

#include<diffgeomeng/classes/diff/Manifold.hpp>

class MetricGrid{
public:
    MetricGrid(Manifold* manifold);

    std::vector<Curve> computePoints(const std::vector<int>& size,
        const std::vector<double>& gaps,
        std::function<std::vector<double>(const std::vector<double>&)> embedding,
        double T,
        double dt,
        int directionDensity,
        std::vector<double> origin = {},
        std::function<std::vector<double>(std::vector<double>)> force = zero
    );
private:
    Manifold* manifold;
};