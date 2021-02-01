#include <iostream>
#include <cmath>


int main()
{
    double tab[3];
    for(int i=0;i<3;i++)
    {
        std::cout<<"Podaj "<<i+1<<" wspolczynnik rownania - "<<std::endl;
        std::cin>>tab[i];
        std::cin.ignore();
    }
    if(double del=tab[1]*tab[1]-4*tab[0]*tab[2];del>0.0)
    {
        std::cout<<"x1 = "<<(-tab[1]-std::sqrt(del))/(2*tab[0])<<std::endl;
        std::cout<<"x2 = "<<(-tab[1]+std::sqrt(del))/(2*tab[0])<<std::endl;
    }
    else if(del==0.0)
        std::cout<<"x1 = "<<(-tab[1]-std::sqrt(del))/(2*tab[0])<<std::endl;
    else 
        std::cout<<"Miejsca zerowe twojego rownania nie istnieja! \n";

    return 0;
}