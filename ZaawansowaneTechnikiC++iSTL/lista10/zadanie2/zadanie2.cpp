#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <fstream>
#include <iterator>

auto phi(auto& n)
{
    auto res=n;
    for(auto i=2;i*i<=n;i++)
        if(!(n%i))
        {
            while(n%i)
                n/=i;
            res-=res/i;
        }
    if(n>1)
        res-=res/n;
    return res;
}



int main()
{
    auto vec=std::vector<long>();
    auto k=0;
    std::cin>>k;
    for(auto i=1;i<k;i++)
        vec.push_back(phi(i));
    auto fs=std::fstream("phi.txt",std::fstream::out);
    auto it=std::ostream_iterator<int>(fs,";");   
    std::copy(vec.begin(),vec.end(),it);
    return 0;
}