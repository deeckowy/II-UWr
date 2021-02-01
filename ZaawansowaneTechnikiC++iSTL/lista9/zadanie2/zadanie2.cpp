#include <iostream>
#include <regex>

int main()
{
    auto rx=std::regex
    (
        "^("
        "(31-(01|03|05|07|08|10|12))"
        "|"
        "(30-(01|03|04|05|06|07|08|09|10|11|12))"
        "|"
        "([1-2][0-9]|0[1-9])-(0[1-9]|1[0-2])"
        ")"
        "-"
        "([0-9]{4,})$"
    );
    std::string phrase="";
    std::cout<<"Pass your date: ";
    std::cin>>phrase;
    std::cout<<"Your date is "<<(std::regex_match(phrase,rx)?"":"in")<<"correct!"<<std::endl;    
    return 0;
}