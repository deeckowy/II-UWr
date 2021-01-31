#include "inf.hpp"

inf::inf(string filename)
{   
    try
    {
        in=new ifstream(filename.c_str(),ios::binary|ios::in);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
}

void inf::read(int size,char* dest)
{
    try
    {
        in->read(dest,size);
        if(in->bad())
            __throw_ios_failure("Fail");
        if(in->fail())
            __throw_ios_failure("Fail");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

inf::~inf()
{
    in->close();
    delete in;
}
