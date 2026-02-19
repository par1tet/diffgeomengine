#include<core/classes/visual/MetricGrid.hpp>
#include <random>
#include<iostream>

MetricGrid::MetricGrid(Manifold* manifold): manifold(manifold){
}

std::vector<Curve> 
MetricGrid::computePoints(
    const std::vector<int>& size,
    const std::vector<double>& gaps,
    std::function<std::vector<double>(const std::vector<double>&)> embedding,
    double T,
    double dt,
    int directionDensity,
    std::vector<double> origin,
    std::function<std::vector<double>(std::vector<double>)> force){
    int N = this->manifold->getMetric()->getSize();
    
    std::vector<Curve> allCurves;

    int totalPoints = 1;
    for(int i = 0; i < N; ++i){
        totalPoints *= size[i];
    }

    for(int i = 0; i < totalPoints; ++i)
    {
        std::vector<double> x0(N);
        int tmp = i;

        for(int i = N - 1; i >= 0; --i)
        {
            int idx = tmp % size[i];
            tmp /= size[i];

            double center = size[i]/2;
            x0[i] = (idx - center + 1e-4) * gaps[i];

            // const double EPS = 1e-4;
            // if (std::abs(x0[i]) < EPS)
            //     x0[i] = (x0[i] < 0 ? -EPS : EPS);

            // if(x0[i] > M_PI - EPS) x0[i] = M_PI - EPS;
        }

        for(int d = 0; d < directionDensity; ++d)
        {
            std::vector<double> v0(N, 0.0);

            if (N >= 2)
            {
                double angle = 2.0 * M_PI * d / directionDensity;

                v0[0] = std::cos(angle);
                v0[1] = std::sin(angle) / x0[0];
            }

            manifold->normalizeVelocity(x0, v0);

            std::vector<double> initConditions = x0;
            initConditions.insert(initConditions.end(), v0.begin(), v0.end());

            Curve geodesic = manifold->getGeodesic()->computeGeodesic(T, initConditions, dt, force);

            Curve embeddedCurve;
            embeddedCurve.points.reserve(geodesic.points.size());

            for(const auto& point : geodesic.points)
            {
                auto embedded = embedding(point);
                for(int i = 0;i != origin.size();i++){
                    embedded[i] += origin[i];
                }
                embeddedCurve.points.push_back(embedded);
            }

            allCurves.push_back(std::move(embeddedCurve));
        }

    }

    return allCurves;
}