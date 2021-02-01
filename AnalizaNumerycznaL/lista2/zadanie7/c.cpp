#include <iostream>
#include <cmath>
#include <iomanip>


union myUnion {
    double dValue;
    uint64_t iValue;
};

myUnion myValue;


double fn(double x)
{
    return (log(x)/log(5))-6;
}


double fne(double x)
{
    return log(x/pow(5,6))/log(5);
}


int main()
{
    std::cout<<std::setprecision(120)<<std::fixed;
    double x=pow(5,6);
    for(int i=0;i<13;i++) {
        myValue.dValue = fn(x - pow(10, -i));
        std::cout << std::hex <<"Gorsza funkcja bity: "<< myValue.iValue <<" dziesietnie "<<std::dec<<myValue.dValue<< std::endl;
        myValue.dValue = fne(x - pow(10, -i));
        std::cout << std::hex <<"Lepsza funkcja bity: "<< myValue.iValue <<" dziesietnie "<<std::dec<<myValue.dValue<< std::endl;
    }

    return 0;
}