#include <iostream>
#include <cmath>

double funf(double x)
{
    return pow(x,3.0)-sqrt(pow(x,6)+2020.0);
}

double funs(double x)
{
    return -2020.0/(pow(x,3.0)+sqrt(pow(x,6.0)+2020.0));
}

int main()
{
    double x=300.0;
    while(funf(x))x+=1.0;
    std::cout<<"funf = "<<x<<std::endl;
    double y=pow(10.0,51.0);
    while(funs(y))y+=pow(10.0,50.0);
    std::cout<<"funs = "<<y<<std::endl;

    return 0;
}