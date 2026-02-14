#include<iostream>
#include<core/classes/diff/Manifold.hpp>


int main(){
    Manifold* manifold = new Manifold(new Metric());
    manifold->showmetric();

    return 0;
}
