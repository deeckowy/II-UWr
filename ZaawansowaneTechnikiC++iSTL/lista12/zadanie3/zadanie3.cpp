#include <iostream>

template<int A,int B>
class nwd
{
    public:
        constexpr int operator()()
        {
            return nwd<B,A%B>()();
        }
};

template<int A>
class nwd<A,0>
{
    public:
        constexpr int operator()()
        {
            return A;
        }
};


int main()
{
    std::cout<<nwd<12,4>()()<<std::endl;
}