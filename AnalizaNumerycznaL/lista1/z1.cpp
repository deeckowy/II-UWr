#include <iostream>
#include <cmath>
#include <iomanip>


long double fun1(long double x)
{
    return (4040.0*(sqrtf128(powf128(x,11.0)+1.0)-1.0))/powf128(x,11.0);
}



int main()
{
    std::cout<<std::setprecision(18)<<std::fixed;
    double i=1.0;
    while(i>0.001)
    {
        std::cout<<fun1(i)<<std::endl;
        i-=0.001;
    }
    return 0;
}

