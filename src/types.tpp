template <size_t N>
Point<N> zeroPoint(Point<N> x){
    return Point<N>();
}

template <size_t N>
ComponentsType<N> zeroPointComponents(){
    ComponentsType<N> comps;
    
    for(int i = 0;i != N;i++){
        comps[i].fill(zeroPoint);
    }

    return comps;
}