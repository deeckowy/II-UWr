#include <iostream>
#include <ratio>

template<int n> 
struct harmonic: public std::ratio_add<std::ratio<1,n>,harmonic<n-1>>{};

template<>
struct harmonic<1>: public std::ratio<1,1>{};

int main()
{
    //przy 47 kompilator odmawia kompilacji przez overflow
    std::cout<<harmonic<46>::den<<"/"<<harmonic<46>::num<<std::endl;
    return 0;
}