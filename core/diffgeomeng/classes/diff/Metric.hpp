#pragma once

#include<vector>
#include<functional>
#include<string>
#include<diffgeomeng/utility/types.hpp>

template <size_t N>
class Metric{
public:
    Metric<N>(const Components<N>&);

    Metric<N>(const std::array<std::function<double(const std::array<double, N>&)>, N>&);
    virtual ~Metric() = default;

    std::function<double(const Point<N>&)> getComponent(int i, int j);
    double getReverseInPoint(Point<N> point, int i, int j);
    int getSize();

    std::array<std::array<double, N>, N> getMatrixAtPoint(Point<N> point);
    bool getIsDiagonal();

    double getInvariant(State<N> state);

private:
    Components<N> metricComponents;
    bool isDiagonal = false;
};