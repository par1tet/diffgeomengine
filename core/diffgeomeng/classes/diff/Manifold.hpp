#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<diffgeomeng/classes/diff/Geodesic.hpp>
#include<vector>

class Manifold {
public:
    Manifold(Metric* metric);
    Manifold(Metric* metric, std::function<std::vector<double>(std::vector<double>)>);
    ~Manifold();

    Metric* getMetric();
    State normalizeVelocity(State state, double normal = 1.0);
    Geodesic* getGeodesic();
    int getDimension();
    std::vector<double> doEmbedding(std::vector<double> x);
    
private:
    Metric* metric;
    Geodesic* geodesic;
    std::function<std::vector<double>(std::vector<double>)> embedding;
};