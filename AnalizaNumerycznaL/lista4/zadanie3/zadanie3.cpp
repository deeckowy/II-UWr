#include <iostream>
#include <cmath>

double eps(int n)
{
    return 1/pow(2,n+1);
}

double fun(double x)
{
    return x-0.49;
}

int main()
{
    double bbound=1.0;
    double abound=0.0;
    for(int i=0;i<5;i++)
    {
        double m=(bbound+abound)/2.0;
        if(fun(m)>0.0)
            bbound=m;
        else
            abound=m;
        std::cout<<"Wartosc dla n = "<<i<<" ~ "<<fun(m)<<std::endl;
        std::cout<<"Blad faktyczny = "<<fabs(0.49-m)<<"\nBlad z definicji = "<<eps(i)<<std::endl;
    }

    std::cout<<"\n\nZnaleziony x = " <<(bbound-abound)/2.0<<std::endl;
    return 0;
}