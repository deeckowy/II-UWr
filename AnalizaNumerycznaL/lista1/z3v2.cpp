#include <iostream>
#include <cmath>

double fun(int n)
{
    if(n==0)
        return 1.0;
    else if(n==1)
        return -1.0/7.0;
    else 
        return (69*fun(n-1)+10*fun(n-2))/7;
}

int main()
{
    for(int i=2;i<51;i++)
        std::cout<<fun(i)<<std::endl;
    return 0;
}