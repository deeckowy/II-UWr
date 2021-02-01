#include <iostream>
#include <iomanip>
#include <cmath>

float fun(float x)
{
    return 12120.0*(x-sinf32(x))/pow(x,3.0);
}

double funx(double x)
{
    return 12120.0*(x-sin(x))/pow(x,3.0);
}


int main()
{
    std::cout<<std::setprecision(18)<<std::fixed;
    for(int i=0;i<21;i++)
    {
        std::cout<<"Wynik float dla i= "<<i<<" "<<fun(pow(10,(-1.0*i)))<<std::endl;
        std::cout<<"Wynik double dla i= "<<i<<" "<<funx(pow(10,(-1.0*i)))<<std::endl;
    }
    return 0;
}

