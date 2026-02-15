#include<core/classes/diff/Metric.hpp>

class ChristoffelSymbols{
public:
    ChristoffelSymbols(Metric* metric);

    double computeChristoffelSybmbolsAtPoint(std::vector<double> point, int k, int i, int j);
    Metric* getMetric();
private:
    Metric* currentMetric;
};