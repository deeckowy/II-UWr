#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int main()
{
    std::cout<<std::setprecision(18)<<std::fixed;
    double tab[100];
    tab[0]=1.0;
    tab[1]=-(1.0/7.0);
    for(int i=2;i<51;i++)
    {
        tab[i]=(1.0/7.0)*((69*tab[i-1])+(10*tab[i-2]));
        std::cout<<tab[i-1]<<std::endl;
    }
    return 0;
}