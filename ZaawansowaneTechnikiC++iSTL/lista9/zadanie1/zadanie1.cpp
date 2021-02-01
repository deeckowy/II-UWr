#include <regex>
#include <iostream>

int main()
{
    std::string time="";
    auto rx=std::regex( "^([0-1][0-9]|2[0-3]):([0-5][0-9])(:[0-5]?[0-9])?$");
    while(time!="\n")
    {
        std::cin>>time;
        auto x=std::regex_match(time,rx);
        std::cout<<x<<std::endl;
    }
    return 0;
}