#include <iostream>
#include <cmath>

double fun(double x)
{
    return pow(x,2.0)-2.0*cos(3.0*x-1.0);
}

double bisection(double abound,double bbound,int desc)
{
    if(desc)
    {
        double help=abound;
        abound=bbound;
        bbound=help;
    }
    double m=0.0;
    for(int i=0;i<16;i++)
    {
        m=(bbound+abound)/2.0;
        if(fun(m)>0.0)
            bbound=m;
        else
            abound=m;
    }
    return m;
}

int main()
{
    double bound=-M_PI/3.0;
    double fx=bisection(bound,0.0,1);
    std::cout<<"Pierwszy wyznaczony x = "<<fx<<std::endl;
    std::cout<<"Wartosc w pierwszym wyznaczonym miejscu zerowym = "<<fun(fx)<<std::endl;
    
    double ffx=bisection(0.0,-bound,0);
    std::cout<<"Pierwszy wyznaczony x = "<<ffx<<std::endl;
    std::cout<<"Wartosc w pierwszym wyznaczonym miejscu zerowym = "<<fun(ffx)<<std::endl;

    return 0;
}