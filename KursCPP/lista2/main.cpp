#include <iostream>
#include "prosta.hpp"

using namespace std;

int main()
{
    try
    { 
        wektor w(1.0,1.0);
        wektor y(w);
        cout<<dodaj(w,y).dx<<" "<<dodaj(w,y).dy<<endl;
        
        punkt o(69.0,69.0);
        punkt p(o);
        punkt x(p,y);
        cout<<x.x<<" "<<x.y<<endl;

        prosta po(o,x);
        cout<<po.getter_A()<<" "<<po.getter_B()<<" "<<po.getter_C()<<endl;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    return 0;
}