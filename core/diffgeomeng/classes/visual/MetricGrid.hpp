#pragma once

#include<diffgeomeng/classes/diff/Manifold.hpp>
#include<diffgeomeng/utility/types.hpp>

template<size_t N>
class MetricGrid{
public:
    MetricGrid(Manifold<N>* manifold);

    std::vector<Curve<N>> computePoints(const std::vector<int>& size,
        const std::vector<double>& gaps,
        Embedding<N> embedding,
        double T,
        double dt,
        int directionDensity,
        Point<N> origin = {},
        std::function<std::array<double, N>(std::array<double, N>)> force = zeroPoint
    );
private:
    Manifold<N>* manifold;
};