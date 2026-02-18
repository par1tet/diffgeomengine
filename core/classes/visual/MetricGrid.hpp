#include<core/classes/diff/Manifold.hpp>

class MetricGrid{
public:
    MetricGrid(Manifold* manifold);

    std::vector<Curve> computePoints(const std::vector<int>& size,
        const std::vector<double>& gaps,
        std::function<std::vector<double>(const std::vector<double>&)> embedding,
        double T,
        double dt,
        int directionDensity);
private:
    Manifold* manifold;
};