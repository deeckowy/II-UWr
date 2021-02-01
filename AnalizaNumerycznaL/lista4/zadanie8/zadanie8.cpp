#include <iostream>
#include <cmath>

double fun(double x)
{
    return pow(x-4.0,12);
}

double fderiv(double x)
{
    return 12*pow(x-4.0,11);
}

double gun(double x)
{
    return pow(fun(x),1/12);
}

double newton(double x)
{
    return x-(12*fun(x)/fderiv(x));
}

int main()
{
    double x=2.0;
    for(int i=0;i<5;i++)
    {
        x=newton(x);
        std::cout<<x<<std::endl;
    }
    return 0;
}