#include "expre.hpp"
#include "numconvar.hpp"
#include <iostream>
#include "unops.hpp"
#include "binops.hpp"

using namespace std;

int main()
{

    expre* fs=new divv(
            new mult(
                new sub(
                    new var("x"),new number(1)),
                    new var("x")),
                new number(2));

    cout<<fs->print()<<endl;

    expre* ss=new divv(new add(new number(3),new number(5)),new add(new number(2),new mult(new var("x"),new number(7))));
    cout<<ss->print()<<endl;

    for(double i=0.01;i<1.0;i+=0.01)
    {
        var::addval("x",i);
        cout<<fs->eval()<<endl;
        cout<<ss->eval()<<endl;
    }

    return 0;
}