#include<core/classes/diff/ChristoffelSymbols.hpp>

struct Curve {
    std::vector<std::vector<double>> points;
};

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);

    std::vector<double> computeGeodesicNextState(double time, std::vector<double>& initConditions, double dx);
    Curve computeGeodesic(double T, std::vector<double>& initConditions, double dx);

private:
    std::vector<double> geodesicRhs(double time, std::vector<double>& initConditions);

    ChristoffelSymbols* currentChristoffelSymbols;
};