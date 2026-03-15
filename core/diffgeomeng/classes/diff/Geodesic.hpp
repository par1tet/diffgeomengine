#pragma once

#include<diffgeomeng/classes/diff/ChristoffelSymbols.hpp>
#include<diffgeomeng/utility/types.hpp>

template<size_t N>
class Geodesic{
public:
    Geodesic(ChristoffelSymbols<N>* christo);
    ~Geodesic();

    State<N> computeGeodesicNextState(double time, State<N>& initState, double dx=0.02,
         std::function<std::array<double, N>(std::array<double, N>)> force = zeroPoint, bool isLogging = false);

    Curve<N> computeGeodesic(double T, State<N>& initState, double dx = 0.02,
         std::function<std::array<double, N>(std::array<double, N>)> force = zeroPoint);

     ChristoffelSymbols<N>* getChristoffelSymbols();

private:
    State<N> geodesicRhs(double time, State<N>& initState,
         std::function<std::array<double, N>(std::array<double, N>)> force = zeroPoint, bool isLogging = false);

    ChristoffelSymbols<N>* christoffelSymbols;
};