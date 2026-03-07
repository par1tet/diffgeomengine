#pragma once

#include<vector>
#include<functional>

typedef std::vector<std::vector<std::function<double(const std::vector<double>&)>>> Components;

struct Curve {
    std::vector<std::vector<double>> points;
};

struct State {
    std::vector<double> x0;
    std::vector<double> v0;
    int dimension;

    State(int d) : 
        x0(std::vector<double>(d, 0.0)),
        v0(std::vector<double>(d, 0.0)),
        dimension(d) {}
};