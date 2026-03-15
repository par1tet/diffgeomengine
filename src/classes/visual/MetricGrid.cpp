#include<diffgeomeng/classes/visual/MetricGrid.hpp>
#include <random>
#include<iostream>
#include<exception>


template<size_t N>
MetricGrid<N>::MetricGrid(Manifold<N>* manifold): manifold(manifold){
}

template<size_t N>
std::vector<Curve<N>> MetricGrid<N>::computePoints(
    const std::vector<int>& size,
    const std::vector<double>& gaps,
    Embedding<N> embedding,
    double T,
    double dt,
    int directionDensity,
    Point<N> origin,
    std::function<std::array<double, N>(std::array<double, N>)> force){
    // -------

    if(gaps.size() != N){
        std::runtime_error("Size of gaps vector must equals dimension of manifold");
    }
    int originSize = origin.size();
    if(originSize != 0){
        if(originSize != N){
            std::runtime_error("Size of origin vector must equals dimension of manifold");
        }
    }

    // -------
    
    std::vector<Curve<N>> allCurves;

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
            State initState(N);
            for(int i = 0;i != N;i++){
                initState.x0[i] = x0[i];
            }

            if (N >= 2){
                double angle = 2.0 * M_PI * d / directionDensity;

                initState.v0[0] = std::cos(angle);
                initState.v0[1] = std::sin(angle) / x0[0];
            }

            initState = manifold->normalizeVelocity(initState);

            Curve<N> geodesic = manifold->getGeodesic()->computeGeodesic(T, initState, dt, force);

            Curve<N> embeddedCurve;
            embeddedCurve.points.reserve(geodesic.points.size());

            for(const auto& point : geodesic.points)
            {
                auto embedded = this->manifold->doEmbedding(embedding(point));
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