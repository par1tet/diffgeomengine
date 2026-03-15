#pragma once

#include<diffgeomeng/classes/diff/Metric.hpp>
#include<diffgeomeng/utility/types.hpp>

template <size_t N>
class ChristoffelSymbols{
public:
    ChristoffelSymbols(Metric<N>* metric);

    double computeChristoffelSybmbolsAtPoint(Point<N> point, int k, int i, int j);
    Metric<N>* getMetric();
private:
    Metric<N>* currentMetric;
};