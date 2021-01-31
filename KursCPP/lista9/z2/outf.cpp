#include "outf.hpp"

outf::outf(string filename)
{
    try
    {
        out=new ofstream(filename.c_str(),ios::binary|ios::out);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }   
}

void outf::write(int size,char* source)
{
    try
    {
        out->write(source,size);
        if(out->bad())
            __throw_ios_failure("Fail");
        if(out->fail())
            __throw_ios_failure("Fail");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

outf::~outf()
{
    out->close();
    delete out;
}