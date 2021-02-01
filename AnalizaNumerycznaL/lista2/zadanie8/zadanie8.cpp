#include <iostream>
#include <cmath>

double funf(double x)
{
    return 4040.0*((sqrt(pow(x,11.0)+1.0))-1.0)/pow(x,11.0);
}

double funs(double x)
{
    return 4040.0/((sqrt(pow(x,11.0)+1.0))+1.0);
}


int main()
{
    double p=-1.0;
    while(funf(pow(10.0,p)))p-=1.0;
    std::cout<<p<<std::endl;
    double s=-1.0;
    while(funs(pow(10.0,s)))s-=1.0;
    std::cout<<s<<std::endl;

    return 0;
}