#include <iostream>
#include <cmath>

auto rfun(auto x)
{
    return 1.22*pow(x,3.0);
}

auto afun(auto x)
{
    return 0.0922*pow(x,1.02);
}

auto main()->int
{
    auto starta=0.000399783;
    auto startr=0.009220859;
    auto rn=4;
    while((startr=rfun(startr))>pow(10,-100))rn++;
    auto an=4;
    while((starta=afun(starta))>pow(10,-100))an++;
    std::cout<<"Ilosc wyrazow potrzebnych do osiagniecia dokladnosci dla {rn}= "<<rn<<std::endl;
    std::cout<<"Ilosc wyrazow potrzebnych do osiagniecia dokladnosci dla {an}= "<<an<<std::endl;
    return 0;
}