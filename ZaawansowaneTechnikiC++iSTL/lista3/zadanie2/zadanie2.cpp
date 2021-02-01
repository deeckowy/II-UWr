#include <iostream>
#include <limits>

int main()
{
    std::cout<<"Najmniejsza wartość dla float = "<<std::numeric_limits<float>::min()<<std::endl;
    std::cout<<"Najmniejsza wartość dla double = "<<std::numeric_limits<double>::min()<<std::endl;
    std::cout<<"Największa wartość dla float = "<<std::numeric_limits<float>::max()<<std::endl;
    std::cout<<"Największa wartość dla double = "<<std::numeric_limits<double>::max()<<std::endl;
    std::cout<<"Epsilon dla float = "<<std::numeric_limits<float>::epsilon()<<std::endl;
    std::cout<<"Epsilon dla double = "<<std::numeric_limits<double>::epsilon()<<std::endl;
    return 0;
}