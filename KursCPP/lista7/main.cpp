#include <iostream>
#include "obliczenia.hpp"

using namespace std;

int main()
{
    obliczenia::wymierna x(1,2<<16);
    cout<<(-x);
    obliczenia::wymierna f(2,2<<16);
    cout<<f+x;
    cout<<!(-x);
    obliczenia::wymierna g(2,0);
    
    obliczenia::wymierna r(9,3);
    obliczenia::wymierna d(3,9);
    cout<<r<<"/"<<d<<"="<<r/d;
    return 0;
}