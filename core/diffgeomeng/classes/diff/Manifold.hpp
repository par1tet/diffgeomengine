#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<diffgeomeng/classes/diff/Geodesic.hpp>
#include<vector>

template <size_t N>
class Manifold {
public:
    Manifold(Metric*);
    Manifold(Metric*, Embedding<N>);
    ~Manifold();

    Metric* getMetric();
    State<N> normalizeVelocity(State<N> state, double normal = 1.0);
    Geodesic* getGeodesic();
    int getDimension();
    Point<N> doEmbedding(Point<N> x);
    
private:
    Metric* metric;
    Geodesic* geodesic;
    Embedding<N> embedding;
};