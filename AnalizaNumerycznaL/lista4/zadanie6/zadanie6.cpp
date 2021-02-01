#include <iostream>
#include <cmath>

double fun(double x,double r)
{
    return x*(2-x*r);
}

int main()
{
    double r=sqrt(4);
    double x=0.49;
    int s=0;
    while(x!=fun(x,r))
    {
        x=fun(x,r);
        s++;
    }
    std::cout<<s<<std::endl;
    std::cout<<x<<std::endl;
    return 0;
}