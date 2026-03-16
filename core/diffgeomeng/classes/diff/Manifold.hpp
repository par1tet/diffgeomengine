#pragma once

#include<diffgeomeng/classes/diff/Geodesic.hpp>
#include<iostream>
#include<vector>

template <size_t N>
class Manifold {
public:
    Manifold(Metric<N>*);
    Manifold(Metric<N>*, Embedding<N>);
    ~Manifold();

    Metric<N>* getMetric();
    State<N> normalizeVelocity(State<N> state, double normal = 1.0);
    Geodesic<N>* getGeodesic();
    int getDimension();
    Point<N> doEmbedding(Point<N> x);
    
private:
    Metric<N>* metric;
    Geodesic<N>* geodesic;
    Embedding<N> embedding;
};

/////////// IMPLEMENTATION /////////////

template <size_t N>
Manifold<N>::Manifold(Metric<N>* metric){
    this->metric = metric;
    this->geodesic = new Geodesic<N>(new ChristoffelSymbols<N>(this->metric));
    this->embedding = Embedding<N>();
};

template <size_t N>
Manifold<N>::Manifold(Metric<N>* metric, Embedding<N> embedding){
    this->metric = metric;
    this->geodesic = new Geodesic<N>(new ChristoffelSymbols<N>(this->metric));
    this->embedding = embedding;
};

template <size_t N>
Manifold<N>::~Manifold(){
    delete this->metric;
    delete this->geodesic;
}

template <size_t N>
Metric<N>* Manifold<N>::getMetric(){
    return this->metric;
}

template <size_t N>
Geodesic<N>* Manifold<N>::getGeodesic(){
    return this->geodesic;
}

template <size_t N>
int Manifold<N>::getDimension(){
    return this->metric->getSize();
}

template <size_t N>
Point<N> Manifold<N>::doEmbedding(Point<N> x){
    return this->embedding.embFunc(x);
}

template <size_t N>
State<N> Manifold<N>::normalizeVelocity(State<N> state, double normal){
    State<N> newState = State<N>(state);

    auto g = this->metric->getMatrixAtPoint(newState.x0);

    double length2 = 0.0;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j)
            length2 += g[i][j] * newState.v0[i] * newState.v0[j];
    }

    // if null-geodesic
    if(std::abs(normal) < 1e-14)
    {
        double spatial = 0.0;

        for(int i = 1; i < N; ++i){
            for(int j = 1; j < N; ++j){
                spatial += g[i][j] * newState.v0[i] * newState.v0[j];
            }
        }

        double gtt = g[0][0];

        if(std::abs(gtt) < 1e-14)
            throw std::runtime_error("Metric g_tt ~ 0");

        newState.v0[0] = std::sqrt(-spatial / gtt);

        return newState;
    }

    if(std::abs(length2) < 1e-12)
        throw std::runtime_error("zeroPoint velocity norm");

    double scale = std::sqrt(std::abs(normal / length2));

    for(int i = 0; i < N; ++i){
        newState.v0[i] *= scale;
    }

    return newState;
}