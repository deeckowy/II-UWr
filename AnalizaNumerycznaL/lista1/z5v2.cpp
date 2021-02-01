#include <iostream>
#include <cmath>

int main()
{
    double sum=0.0;
    for(int i=0;i<20000;i++)
        sum+=(i%2?-1.0:1.0)/(2.0*(double)i+1.0);
    std::cout<<4*sum-M_PI<<std::endl;
    return 0;
}