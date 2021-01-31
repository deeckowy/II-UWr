#include <iostream>

using namespace std;

#ifndef _EXPRE_HPP
#define _EXPRE_HPP

class expre
{   
    public: 
        virtual string print(int prior=0)=0;
        virtual double eval()=0;
    protected:
        int priority;
};

#endif