#pragma once

#include<diffgeomeng/classes/diff/ChristoffelSymbols.hpp>
#include<diffgeomeng/utility/types.hpp>

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);
    ~Geodesic();

    State computeGeodesicNextState(double time, State& initState, double dx=0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero, bool isLogging = false);

    Curve computeGeodesic(double T, State& initState, double dx = 0.02,
         std::function<std::vector<double>(std::vector<double>)> force = zero);

     ChristoffelSymbols* getChristoffelSymbols();

private:
    State geodesicRhs(double time, State& initState,
         std::function<std::vector<double>(std::vector<double>)> force = zero, bool isLogging = false);

    ChristoffelSymbols* christoffelSymbols;
};