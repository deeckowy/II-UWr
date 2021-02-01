#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

auto fun(const auto& vec)
{
    std::unordered_map<int,int> output;
    for(const auto& x:vec)
        output[x]++;
    auto max=std::max_element(output.begin(),output.end(),[](const auto& p1,const auto& p2)
    {
        return p1.second<p2.second;
    });
    auto it=output.begin();
    while(it!=output.end())
    {
        if(it->second!=max->second)
            it=output.erase(it);
        else it++;
    }
    return std::move(output);
}


int main()
{
    std::vector<int> vec{1,1,3,5,8,9,5,8,8,5};
    auto out=fun(vec);
    for(auto x:out)
        std::cout<<"{"<<x.first<<", "<<x.second<<"}"<<std::endl;
    std::vector<int> vec2;
    for(int i=0;i<100;i++)
        vec2.push_back(rand()%10);


    std::cout<<"\n\nLosowo wygenerowany wektor : \n";

    auto out2=fun(vec2);
    for(auto x:out2)
        std::cout<<"{"<<x.first<<", "<<x.second<<"}"<<std::endl;
    return 0;
}