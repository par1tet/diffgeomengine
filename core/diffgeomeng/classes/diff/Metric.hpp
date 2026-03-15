#pragma once

#include<vector>
#include<functional>
#include<string>
#include<diffgeomeng/utility/types.hpp>

template <size_t N>
std::array<double, N> zero(std::array<double, N> x);

class Metric{
public:
    Metric(const Components&);

    template <size_t N>
    Metric(const std::vector<std::function<double(const std::vector<double>&)>>&);
    virtual ~Metric() = default;

    template <size_t N>
    std::function<double(const Point<N>&)> getComponent(int i, int j);
    template <size_t N>
    double getReverseInPoint(Point<N> point, int i, int j);
    int getSize();

    template <size_t N>
    std::array<std::array<double, N>, N> getMatrixAtPoint(Point<N> point);
    bool getIsDiagonal();

    template <size_t N>
    double getInvariant(State<N> state);

private:
    Components metricComponents;
    bool isDiagonal = false;
};