#include <iostream>
#include <regex>

int main()
{
    auto rx=std::regex
    (
        "^("
        "[A-Z]"
        "[a-z]{2,}"
        "\\s?"
        ")*"
        "|"
        "("
        "[A-Z]"
        "[a-z]{2,}"
        "-"
        "[A-Z]"
        "[a-z]{2,}"
        "\\s?)*"
    );
    std::string phrase="";
    std::cout<<"Pass your city name: ";
    std::cin>>phrase;
    std::cout<<"Your city name is "<<(std::regex_match(phrase,rx)?"":"in")<<"correct!"<<std::endl;    

    return 0;
}