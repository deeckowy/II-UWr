#include <iostream>
#include <cmath>

auto rowno(auto n)
{
    double step=2.0/n;
    double start=-1.0;
    while(start<=1.0)
    {
        std::cout<<"(x"<<(start>=0.0?"-":"+")<<std::fabs(start)<<")";
        start+=step;
    }
    std::cout<<std::endl;
}

auto czybyszew(int n)
{
    double k=1;
    while(k<=n)
    {
        double start=std::cos((2*k-1)*M_PI/(2*n));
        std::cout<<"(x"<<(start>=0.0?"-":"+")<<std::fabs(start)<<")";        
        k+=1;
    }
    std::cout<<std::endl;
}

int main()
{
    for(auto i=4;i<21;i++)
        rowno(i);
    for(auto i=4;i<21;i++)
        czybyszew(i);
    
    return 0;
}