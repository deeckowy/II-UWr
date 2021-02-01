#include <iostream>
#include <cmath>
#include <climits>

double funf(double x)
{
    return (cos(x)-1.0+(pow(x,2.0)/2.0))/pow(x,4.0);
}

double factorial(double x)
{
    if(x)
        return x*factorial(x-1.0);
    else 
        return 1.0;
}

double funs(double x)
{
    double sum=1.0/factorial(4.0);
    for(int i=4;i<=200;i+=4)
        sum+=pow(x,(double)i)/factorial(i+4);
    for(int i=2;i<=200;i+=4)
        sum-=pow(x,(double)i)/factorial(i+4);
    
    return sum;
}


int main()
{
    double w=-1.0;
    while(funf(pow(10.0,w))<1.0)w-=1.0;
    std::cout<<w<<std::endl;
    double p=-1.0;
    while(funs(pow(10.0,p)))p-=1.0;
    std::cout<<p<<std::endl;

        
    return 0;
}