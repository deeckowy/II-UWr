#include <iostream>


int main() 
{
    int n=4;
    float x[n]={-3,-1,0,2};
    float f[n]={3,4,2,3};

    for(auto i=1;i<n;i++)
        for(auto j=n-1;j>=i;j--)
        {
            f[j]=(f[j]-f[j-1])/(x[j]-x[j-i]);
            std::cout<<f[j]<<std::endl;
        }
    for(auto i=0;i<n;i++)
        std::cout<<f[i]<<std::endl;
    
    return 0;
}