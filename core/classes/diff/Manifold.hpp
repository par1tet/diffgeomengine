#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<core/classes/diff/Geodesic.hpp>

class Manifold {
public:
    Manifold(Metric* metric);

    void showmetric();
    Metric* getMetric();
    
    void normalizeVelocity(
        const std::vector<double>& x,
        std::vector<double>& v);
        
    Geodesic* getGeodesic();
    
private:
    Metric* metric;
    Geodesic* geodesic;
};