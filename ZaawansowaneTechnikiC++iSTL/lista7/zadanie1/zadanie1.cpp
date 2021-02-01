#include <iostream>
#include <cmath>
#include <vector>
#include <random>

template<typename Collection>
auto perm(Collection& vec)
{
    std::mt19937 gen{std::random_device{}()};
    auto dist=std::uniform_int_distribution<>{0,vec.size()}(gen);
    for(unsigned int i=1;i<vec.size();i++)
        std::swap(vec[i],vec[dist(gen)]);
}

int main()
{
    std::string s="SAMPLE STRING";
    std::vector<int> v{1,2,3,4,5,6,7,8,9};
    perm(s);
    std::cout<<s<<std::endl;
    perm(v);
    for(auto x:v)
        std::cout<<x<<std::endl;

    return 0;
}