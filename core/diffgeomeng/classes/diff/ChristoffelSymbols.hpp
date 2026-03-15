#pragma once

#include<diffgeomeng/classes/diff/Metric.hpp>
#include<diffgeomeng/utility/types.hpp>

class ChristoffelSymbols{
public:
    ChristoffelSymbols(Metric* metric);

    template <size_t N>
    double computeChristoffelSybmbolsAtPoint(Point<N> point, int k, int i, int j);
    Metric* getMetric();
private:
    Metric* currentMetric;
};