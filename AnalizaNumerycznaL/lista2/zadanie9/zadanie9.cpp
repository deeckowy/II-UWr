#include <iostream>
#include <cmath>
#include <vector>

static std::vector<double> ar{2.0};

double funf(int k)
{
    double arr[40];
    double x=2.0; 
    for(int i=2;i<k+1;i++)
        x=pow(2.0,i-1.0)*sqrt(2.0*(1-sqrt(1-pow(x/pow(2.0,i-1.0),2.0))));
    return x;
}

double funs(int k)
{
    double x=2.0; 
    for(int i=2;i<k+1;i++)
        x=sqrt(2*pow(x,2)/(1.0+sqrt(1-pow(x/pow(2.0,i-1.0),2.0))));
    return x;
}

int main() 
{
    int x=1;
    while(funf(x))x++;
    std::cout<<x<<std::endl;
    int s=1;
    while(funs(s)!=funs(s+1))s++;
    std::cout<<s<<std::endl;

    

    return 0;
}