#pragma once

#include<vector>
#include<functional>

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

template <size_t N>
Point<N> zeroPoint(Point<N> x);

template <size_t N>
struct Embedding {
    std::function<Point<N>(Point<N>)> embFunc;

    Embedding(std::function<Point<N>(Point<N>)> embFunc) : embFunc(embFunc){}
    Embedding() : embFunc([](Point<N> point){return point;}){}
};

template <size_t N>
struct Curve {
    std::vector<Point<N>> points;
};

template <size_t N>
using ComponentsRowType = std::array<std::function<double(const std::array<double, N>&)>,N>;

template <size_t N>
using ComponentsType = std::array<std::array<std::function<double(const std::array<double, N>&)>,N>, N>;

template <size_t N>
ComponentsType<N> zeroPointComponents();

template <size_t N>
struct Components {
    ComponentsType<N> components;

    Components<N>(ComponentsType<N> components): components(components){}
    Components<N>(): components(zeroPointComponents<N>()){}
};

template <size_t N>
using VectorField = std::function<Point<N>(Point<N>)>;

template <size_t N>
VectorField<N> zeroVectorField(){return [](Point<N> x){return Point<N>();};}

/////////// IMPLEMENTATION /////////////

template <size_t N>
Point<N> zeroPoint(Point<N> x){
    return Point<N>();
}

template <size_t N>
ComponentsType<N> zeroPointComponents(){
    ComponentsType<N> comps;
    
    for(int i = 0;i != N;i++){
        comps[i].fill(zeroPoint);
    }

    return comps;
}