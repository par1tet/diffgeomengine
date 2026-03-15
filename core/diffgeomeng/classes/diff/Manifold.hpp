#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<diffgeomeng/classes/diff/Geodesic.hpp>
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