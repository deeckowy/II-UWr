#include <iostream>
#include <cmath>
#include <random>
double fRand(double fMin, double fMax)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(fMin,fMax);
    return dist(gen);
}

double fun(double x,double r)
{
    return x*(2.0-x*r);
}

int main()
{
    for(int i=0;i<10;i++)
    {
        double r=(double)((rand()%10)+1);
        double x=fRand(0.0,2.0/r);
        int s=0;
        std::cout<<"x = "<<r<<std::endl;
        std::cout<<"x0 = "<<x<<std::endl;

        while(x!=fun(x,r))
        {
            x=fun(x,r);
            s++;
        }
        std::cout<<"wynik = "<<x<<" po "<<s<<" iteracjach"<<std::endl;
    }
    return 0;
}