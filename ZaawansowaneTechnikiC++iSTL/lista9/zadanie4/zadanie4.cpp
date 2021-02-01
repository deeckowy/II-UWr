#include <iostream>
#include <regex>

int main()
{
    std::regex rx
    (
        "^\\("
        "[-]?"
        "[0-9]+"
        "(\\.[0-9]+)?"
        "[+|-]"
        "[0-9]+"
        "(\\.[0-9]+)?"
        "[i|I]"
        "\\)$"
    );
    std::string phrase="";
    std::cout<<"Pass your complex number: ";
    std::cin>>phrase;
    std::cout<<"Your complex number is "<<(std::regex_match(phrase,rx)?"":"in")<<"correct!"<<std::endl;    
    return 0;
}