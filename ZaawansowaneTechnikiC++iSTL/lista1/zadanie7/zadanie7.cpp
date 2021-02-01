#include <iostream>
#include <string>

void escape()
{
    std::cout<<"Usage ./zadanie7 DD.MM.YYYY"<<std::endl;
    exit(0);
}

std::string fix_day(int day)
{
    std::string out="";
    switch(day)
    {
        case 1:
            out="st";
        break;
        case 2:
            out="nd";
        break;
        case 3:
            out="rd";
        break;
        default:
            out="th";
        break;
    }
    return out;
}

int main(int argc,char* argv[])
{
    if(argc<2)
        escape();
    std::string d="";
    d+=argv[1][0];
    d+=argv[1][1];
    int day=std::stoi(d);
    if(day>30)
        escape();
    std::string y="";
    for(int i=6;i<9;i++)
        y+=argv[1][i];
    int year=std::stoi(y);
    std::string m(argv[1][3]);
    m+=argv[1][4];
    switch (int month=std::stoi(m))
    {
        case 1:
            std::cout<<day<<fix_day(day)<<" January ";
        break;
        case 2:
            std::cout<<day<<fix_day(day)<<" February ";
        break;
        case 3:
            std::cout<<day<<fix_day(day)<<" March ";
        break;
        case 4:
            std::cout<<day<<fix_day(day)<<" April ";
        break;
        case 5:
            std::cout<<day<<fix_day(day)<<" May ";
        break;
        case 6:
            std::cout<<day<<fix_day(day)<<" June ";
        break;
        case 7:
            std::cout<<day<<fix_day(day)<<" July ";
        break;
        case 8:
            std::cout<<day<<fix_day(day)<<" August ";
        break;
        case 9:
            std::cout<<day<<fix_day(day)<<" September ";
        break;
        case 10:
            std::cout<<day<<fix_day(day)<<" October ";
        break;
        case 11:
            std::cout<<day<<fix_day(day)<<" November ";
        break;
        case 12:
            std::cout<<day<<fix_day(day)<<" December ";
        break;
        default:
            escape();
        break;
    }
    std::cout<<year<<std::endl;
    return 0;
}