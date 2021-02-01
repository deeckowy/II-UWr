#include <iostream>
#include <cmath>

double fun(double x)
{
    return 4.0*pow(cos(x),2.0)-3.0;
}


double fun1(double x)
{
    return cos(3*x)/cos(x);
}

double fun2(double x)
{
    return pow(x,-3.0)*(M_PI/2.0-x-atan(1/x));
}

double fun2b(double x)
{
    return pow(x,-3.0)*(atan(x)-x);
}
int main()
{
    std::cout<<fun(5*M_PI/6)<<std::endl;
    std::cout<<fun1(5*M_PI/6)<<std::endl;
    std::cout<<fun2(0.0000001)<<std::endl;
    std::cout<<fun2b(0.0000001)<<std::endl;

    return 0;
}