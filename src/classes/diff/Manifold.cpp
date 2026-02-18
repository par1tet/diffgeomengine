#include<core/classes/diff/Manifold.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

Manifold::Manifold(Metric* metric){
    this->metric = metric;
    this->geodesic = new Geodesic(new ChristoffelSymbols(this->metric));
};

void Manifold::showmetric(){
    std::cout << "hii" << std::endl;
}

Metric* Manifold::getMetric(){
    return this->metric;
}

void Manifold::normalizeVelocity(
    const std::vector<double>& x,
    std::vector<double>& v)
{
    int N = this->metric->getSize();

    auto g = this->metric->getMatrixAtPoint(x);

    double length2 = 0.0;

    for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            length2 += g[i][j] * v[i] * v[j];

    if(std::abs(length2) < 1e-12)
        throw std::runtime_error("Zero velocity norm");

    double invLength = 1.0 / std::sqrt(length2);

    for(int i = 0; i < N; ++i)
        v[i] *= invLength;
}

Geodesic* Manifold::getGeodesic(){
    return this->geodesic;
}