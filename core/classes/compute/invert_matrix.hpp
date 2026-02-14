#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <algorithm>
std::vector<std::vector<double>> invertComponentMatrix(
    const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>& componentMatrix,
    const std::vector<double>& point);
 