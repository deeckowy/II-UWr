#include <iostream>
#include <limits>

int main()
{
    std::numeric_limits<long long int> x;
    std::cout<<"Liczba bitów w long long int = "<<sizeof(long long int)*8<<std::endl;
    std::cout<<"Liczba cyfr dla long long int = "<<x.digits10<<std::endl;
    std::cout<<"Maksymalna wartość dla long long int = "<<x.max()<<std::endl;
    return 0;
}