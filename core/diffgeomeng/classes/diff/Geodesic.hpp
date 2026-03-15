#pragma once

#include<diffgeomeng/classes/diff/ChristoffelSymbols.hpp>
#include<diffgeomeng/utility/types.hpp>

class Geodesic{
public:
    Geodesic(ChristoffelSymbols* christo);
    ~Geodesic();

    template<size_t N>
    State<N> computeGeodesicNextState(double time, State<N>& initState, double dx=0.02,
         std::function<std::array<double, N>(std::array<double, N>)> force = zero, bool isLogging = false);

    template<size_t N>
    Curve computeGeodesic(double T, State<N>& initState, double dx = 0.02,
         std::function<std::array<double, N>(std::array<double, N>)> force = zero);

     ChristoffelSymbols* getChristoffelSymbols();

private:
    template<size_t N>
    State<N> geodesicRhs(double time, State<N>& initState,
         std::function<std::array<double, N>(std::array<double, N>)> force = zero, bool isLogging = false);

    ChristoffelSymbols* christoffelSymbols;
};