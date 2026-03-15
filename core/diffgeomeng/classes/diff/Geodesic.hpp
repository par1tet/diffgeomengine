#pragma once

#include<diffgeomeng/classes/diff/ChristoffelSymbols.hpp>
#include<diffgeomeng/utility/types.hpp>
#include<diffgeomeng/classes/compute/rk4_realize.hpp>
#include<iostream>
#include<cmath>
#include<diffgeomeng/utility/functions.hpp>

template<size_t N>
class Geodesic{
public:
    Geodesic(ChristoffelSymbols<N>* christo);
    ~Geodesic();

    State<N> computeGeodesicNextState(double time, State<N>& initState, double dx=0.02,
         VectorField<N> force = zeroVectorField<N>(), bool isLogging = false);

    Curve<N> computeGeodesic(double T, State<N>& initState, double dx = 0.02,
         VectorField<N> force = zeroVectorField<N>());

     ChristoffelSymbols<N>* getChristoffelSymbols();

private:
    State<N> geodesicRhs(double time, State<N>& initState,
         VectorField<N> force = zeroVectorField<N>(), bool isLogging = false);

    ChristoffelSymbols<N>* christoffelSymbols;
};

#include<src/classes/diff/Geodesic.tpp>