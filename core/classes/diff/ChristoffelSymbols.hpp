#include<core/classes/diff/Metric.hpp>
typedef std::vector<std::vector<std::vector<std::function<double(std::vector<double>)>>>> Components;

class ChristoffelSymbols{
public:
    ChristoffelSymbols(Metric* metric);

    void computeAllChristoffelSybmbols();
    std::function<double(const std::vector<double>&)> getComponents(int k, int i, int j);
private:
    Components symbolsComponents;
    Metric* currentMetric;
};