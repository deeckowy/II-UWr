#include <iostream>


template<size_t N,typename T>
double inner(T *x,T *y)
{
    double sum=0.0;
    for(int i=0;i<N;i++)
        sum+=x[i]*y[i];
    return sum;
}

int main()
{
    int *x=new int[2]();
    int *y=new int[2]();
    x[0]=1;
    y[0]=2;
    x[1]=9;
    y[1]=10;
    std::cout<<inner<2,int>(x,y)<<std::endl;
    return 0;
}