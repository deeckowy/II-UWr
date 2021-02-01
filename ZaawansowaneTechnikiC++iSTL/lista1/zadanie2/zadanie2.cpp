#include <iostream>
#include <string>


int main()
{
    std::string adres(R"(Instytut Informatyki Uniwersytetu Wrocławskiego
Fryderyka Joliot-Curie 15,
50-383 Wrocław)");

    std::string path(R"(C:\Program Files\)");
    std::string quotes(R"slowo()")slowo");
    std::cout<<adres<<std::endl;
    std::cout<<path<<std::endl;
    std::cout<<quotes<<std::endl;
    return 0;
}