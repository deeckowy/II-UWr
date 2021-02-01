#include <iostream>
#include <type_traits>

template<int N,int K>
class bin_coeff
{
    public:
        constexpr int operator()()
        {
            return bin_coeff<N-1,K-1>()()*N/K;
        }
};

template<>
class bin_coeff<0,0>
{
    public:
        constexpr int operator()()
        {
            return 0;
        }
};

template<int N>
class bin_coeff<N,0>
{
    public:
        constexpr int operator()()
        {
            return 1;
        }
};

template<int N>
class bin_coeff<N,N>
{
    public:
        constexpr int operator()()
        {
            return 1;
        }
};


int main()
{
    std::cout<<bin_coeff<12,7>()()<<std::endl;
    return 0;
}