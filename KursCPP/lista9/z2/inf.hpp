#include <iostream>
#include <fstream>

using namespace std;

#ifndef _INF_HPP
#define _INF_HPP

class inf
{
        ifstream* in;
    public:
        inf(string filename);
        void read(int size,char* dest);
        ~inf();
};



#endif