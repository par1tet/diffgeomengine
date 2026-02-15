#include<core/classes/diff/ChristoffelSymbols.hpp>

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);

    std::vector<double> getGeodesicNextState(double time, std::vector<double>& initConditions, double dx = 0.002f);

private:
    std::vector<double> geodesicRhs(double time, std::vector<double>& initConditions);

    ChristoffelSymbols* currentChristoffelSymbols;
};