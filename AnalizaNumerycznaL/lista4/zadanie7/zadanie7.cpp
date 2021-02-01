#include <iostream>
#include <cmath>

double fun(double x,double a)
{
    return (x/2)+(a/(2*x));
}

int main()
{
    double a=2.0;
    double x=0.1;
    while(x<10.0)
    {
        int s=0;
        double cx=x;
        while((fun(x,a)!=x)&&s<5)
        {
            x=fun(x,a);
            s++;
        }
        if(s<5||(fabs(x-sqrt(2))<0.0001&&x>0))
            std::cout<<"Metoda jest zbiezna dla x ="<<cx<<" Wynik = "<<x<<std::endl;
        x=cx+0.1;
    }
    return 0;
}