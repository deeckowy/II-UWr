#include <iostream>
#include <cmath>

int main()
{
    double tab[40];
    tab[0]=log(2021.0/2020.0);
    for(int i=1;i<21;i++)
    {
        tab[i]=1.0/i-2020*tab[i-1];
        std::cout<<tab[i]<<std::endl;
    }
    return 0;
}