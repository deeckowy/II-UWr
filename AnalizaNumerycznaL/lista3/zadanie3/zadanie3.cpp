#include <iostream>
#include <cmath>

void fun(double r,double q)
{
    std::cout<<pow(r+sqrt(pow(q,3)+pow(r,2)),1.0/3.0)+pow(r-sqrt(pow(q,3)+pow(r,2)),1.0/3.0)<<std::endl;
}

void fun1(double r,double q)
{
    double cbrt=pow(r+sqrt(pow(q,3)+pow(r,2)),1.0/3.0);
    std::cout<<cbrt-(q/cbrt)<<std::endl;
}

void fun2(double r,double q)
{
    double cbrt=pow(r+sqrt(pow(q,3)+pow(r,2)),1.0/3.0);
    std::cout<<2*r/(pow(cbrt,2)+pow(-q,3)/pow(cbrt,2)+q);
}

int main()
{
    fun(1,1);
    fun1(1,1);
    fun2(1,1);

    return 0;
}
