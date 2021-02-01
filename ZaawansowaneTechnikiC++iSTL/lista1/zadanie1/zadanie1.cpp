#include <iostream>

int main()
{
    std::cout<<"??="<<std::endl;// ??= tluamczy sie na #
    std::cout<<"??-"<<std::endl;// ~ jest tluamczona z ??-
    //aby kompilator wlasciwie interpretowal trojznaki potrzebuje flagi -trigraphs 
    return 0;
}