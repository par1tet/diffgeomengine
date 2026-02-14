#include<vector>
#include<functional>

class Metric{
public:
    Metric(const std::vector<std::vector<std::function<double(const std::vector<double>&)>>>&);
    Metric(const std::vector<std::function<double(const std::vector<double>&)>>&);

    std::function<double(const std::vector<double>&)> getComponent(int i, int j);
    int getSize();
private:
    std::vector<std::vector<std::function<double(const std::vector<double>&)>>> metricComponents;
};