#include<vector>
#include <functional>

double diffBy(std::function<double(const std::vector<double>&)> func, 
             const std::vector<double>& point,
                int p_index,
                double dx=1e-4);