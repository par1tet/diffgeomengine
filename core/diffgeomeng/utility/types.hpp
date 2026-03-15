#pragma once

#include<vector>
#include<functional>

typedef std::vector<std::vector<std::function<double(const std::vector<double>&)>>> Components;

template <size_t N>
struct Embedding {
    std::function<std::array<double, N>(std::array<double, N>)> embFunc;

    Embedding(std::function<std::array<double, N>(std::array<double, N>)> embFunc) : embFunc(embFunc){}
};

struct Curve {
    std::vector<std::vector<double>> points;
};

template <size_t N>
struct State {
    std::array<double, N> x0;
    std::array<double, N> v0;
    constexpr static size_t dimension = N;

    State() {
        x0.fill(0.0);
        v0.fill(0.0);
    }

    State(std::array<double,N> x0,
          std::array<double,N> v0)
        : x0(x0), v0(v0) {}
};

template <size_t N>
struct Point {
    std::array<double, N> x;

    Point() {
        x.fill(0.0);
    }

    Point(std::array<double,N> x0) : x(x0){}
};