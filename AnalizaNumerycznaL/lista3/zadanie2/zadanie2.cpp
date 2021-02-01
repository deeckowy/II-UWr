#include <iostream>
#include <cmath>

void del1(double a,double b,double c)
{
    double d1=(-b+(std::sqrt(std::pow(b,2)-4*a*c))*b<0.0?1:-1);
    std::cout<<"x1 = "<<d1/2*a<<std::endl;
    std::cout<<"x2 = "<<2*c/d1<<std::endl;
}

void del2(double a,double b,double c)
{
    std::cout<<"x1 = "<<(-b-(sqrt(pow(b,2.0)-4.0*a*c)))/2.0*a<<std::endl;
    std::cout<<"x2 = "<<(-b+(sqrt(pow(b,2.0)-4.0*a*c)))/2.0*a<<std::endl;
}

int main()
{
    std::cout<<"Dla zwykłej wersji :"<<std::endl;
    del2(pow(10,-10),-pow(10,10),pow(10,-10));
    std::cout<<"Dla poprawionej wersji :"<<std::endl;
    del1(pow(10,-10),-pow(10,10),pow(10,-10));

    return 0;
}