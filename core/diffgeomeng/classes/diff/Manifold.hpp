#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<core/classes/diff/Geodesic.hpp>

class Manifold {
public:
    Manifold(Metric* metric);
    ~Manifold();

    Metric* getMetric();
    State normalizeVelocity(State state);
    Geodesic* getGeodesic();
    int getDimension();
    
private:
    Metric* metric;
    Geodesic* geodesic;
};