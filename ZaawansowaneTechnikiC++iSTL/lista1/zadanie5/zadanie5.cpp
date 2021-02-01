#include <iostream>
#include <cstdint>

auto lucas(uint32_t n)
{
    if(!n)
        return 2;
    else if(n==1)
        return 1;
    else 
        return lucas(n-1)+lucas(n-2);
}

int main()
{
    for(int i=0;i<20;i++)
        std::cout<<i<<" liczba Lucasa = "<<lucas(i)<<std::endl;
    return 0;
}