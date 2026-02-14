#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<core/classes/diff/Metric.hpp>

class Manifold {
public:
    Manifold(Metric* metric);

    void showmetric();
private:
    Metric* metric;
};