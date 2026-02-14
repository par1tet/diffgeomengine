#include<core/classes/diff/Manifold.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

Manifold::Manifold(Metric* metric){
    this->metric = metric;
};

void Manifold::showmetric(){
    std::cout << "hii" << std::endl;
}