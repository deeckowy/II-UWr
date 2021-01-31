#include <iostream>
#include <fstream>

using namespace std;

#ifndef _OUTF_HPP
#define _OUTF_HPP

class outf
{
        ofstream* out;
    public:
        outf(string filename);
        void write(int size,char* source);
        ~outf();
};


#endif