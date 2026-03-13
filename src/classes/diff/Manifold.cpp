#include<diffgeomeng/classes/diff/Manifold.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

Manifold::Manifold(Metric* metric){
    this->metric = metric;
    this->geodesic = new Geodesic(new ChristoffelSymbols(this->metric));
    this->embedding = zero;
};

Manifold::Manifold(Metric* metric, Embedding embedding){
    this->metric = metric;
    this->geodesic = new Geodesic(new ChristoffelSymbols(this->metric));
    this->embedding = embedding;
};

Manifold::~Manifold(){
    delete this->metric;
    delete this->geodesic;
}

Metric* Manifold::getMetric(){
    return this->metric;
}

Geodesic* Manifold::getGeodesic(){
    return this->geodesic;
}

int Manifold::getDimension(){
    return this->metric->getSize();
}


std::vector<double> Manifold::doEmbedding(std::vector<double> x){
    return this->embedding(x);
}

State Manifold::normalizeVelocity(State state, double normal){
    State newState(state);

    int N = this->getDimension();
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
        throw std::runtime_error("Zero velocity norm");

    double scale = std::sqrt(std::abs(normal / length2));

    for(int i = 0; i < N; ++i){
        newState.v0[i] *= scale;
    }

    return newState;
}