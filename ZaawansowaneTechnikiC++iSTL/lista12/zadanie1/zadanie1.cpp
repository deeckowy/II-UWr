#include <iostream>
#include <algorithm>

template<int N>
constexpr int luc()
{
    return luc<N-1>()+luc<N-2>();
}

template<>
constexpr int luc<1>()
{
    return 1;
}

template<>
constexpr int luc<0>()
{
    return 2;
}

constexpr int lucas(int n)
{
    int l=2;
    int k=1;
    for(int i=0;i<n;i++)
    {
        int t=l;
        l=k;
        k+=t;
    }
    return l;
}


int main()
{
    // std::cout<<luc<43>()<<std::endl;
    std::cout<<lucas(43)<<std::endl;
    return 0;
}

