#include<core/classes/diff/ChristoffelSymbols.hpp>

struct Curve {
    std::vector<std::vector<double>> points;
};

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);

    std::vector<double> computeGeodesicNextState(double time, std::vector<double>& initConditions, double dx=0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero);

    Curve computeGeodesic(double T, std::vector<double>& initConditions, double dx = 0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero);


private:
    std::vector<double> geodesicRhs(double time, std::vector<double>& initConditions,
         std::function<std::vector<double>(std::vector<double>)> force = zero);

    ChristoffelSymbols* currentChristoffelSymbols;
};