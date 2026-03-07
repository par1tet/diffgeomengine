#pragma once

#include<diffgeomeng/classes/diff/ChristoffelSymbols.hpp>
#include<diffgeomeng/utility/types.hpp>

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);
    ~Geodesic();

    State computeGeodesicNextState(double time, State& initState, double dx=0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero);

    Curve computeGeodesic(double T, State& initState, double dx = 0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero);


private:
    State geodesicRhs(double time, State& initState,
         std::function<std::vector<double>(std::vector<double>)> force = zero);

    ChristoffelSymbols* christoffelSymbols;
};