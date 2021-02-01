#include <iostream>
#include <cmath>

int main()
{
    float sum=0.0;
    int k=0;
    while(fabs(4*sum-M_PI)>pow(10,-4))
    {
        float x=(k%2?-1.0:1.0)/(2.0*(float)k+1.0);
        sum+=x;
        std::cout<<x<<std::endl;
        k++;
    }    
    std::cout<<sum<<std::endl;
    std::cout<<k<<std::endl;
    return 0;
}