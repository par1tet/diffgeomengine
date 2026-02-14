#include<vector>
#include<functional>
#include<string>
typedef std::vector<std::vector<std::function<double(const std::vector<double>&)>>> Components;

class Metric{
public:
    Metric(const Components&);
    Metric(const std::vector<std::function<double(const std::vector<double>&)>>&);

    std::function<double(const std::vector<double>&)> getComponent(int i, int j);
    double getReverseInPoint(std::vector<double> point, int i, int j);
    int getSize();
private:
    Components metricComponents;
};