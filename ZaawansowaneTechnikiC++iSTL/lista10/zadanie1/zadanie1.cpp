#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <cmath>

int main()
{
    auto vec=std::vector<double>(std::istream_iterator<double>(std::cin),{});
    std::cout<<std::setprecision(3)<<std::fixed;
    auto av=std::accumulate(vec.begin(),vec.end(),0.0)/vec.size();
    std::cout<<"Average = "<<av<<std::endl;
    auto dev=0.0;
    std::for_each(vec.begin(),vec.end(),[&](const auto &x)
    {
        dev+=std::pow(x-av,2);
    });
    dev/=vec.size();
    dev=std::sqrt(dev);
    std::cout<<"Standard deviation = "<<dev<<std::endl;
    return 0;
}