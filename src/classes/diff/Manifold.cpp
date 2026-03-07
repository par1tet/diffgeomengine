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

Manifold::Manifold(Metric* metric, std::function<std::vector<double>(std::vector<double>)> embedding){
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

State Manifold::normalizeVelocity(State state){
    State newState(state);

    int N = this->getDimension();
    auto g = this->metric->getMatrixAtPoint(newState.x0);

    double length2 = 0.0;

    for(int i = 0; i < N; ++i){
        for(int j = 0; j < N; ++j)
            length2 += g[i][j] * newState.v0[i] * newState.v0[j];
    }

    if(std::abs(length2) < 1e-12)
        throw std::runtime_error("Zero velocity norm");

    double invLength = 1.0 / std::sqrt(length2);

    for(int i = 0; i < N; ++i){
        newState.v0[i] *= invLength;
    }

    return newState;
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