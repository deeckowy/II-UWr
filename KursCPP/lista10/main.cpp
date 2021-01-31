#include <iostream>
#include "eval.hpp"
#include "parse.hpp"

using namespace std;

void show_menu()
{
    cout<<"Possible options:"<<endl;
    cout<<"print <expr> '|' ~ eval your expr"<<endl;// uzywam znaku | do zakonczenia wyrazenia 
    cout<<"assign <expr> '|' to <variable name> ~ save your expr for later use"<<endl;
    cout<<"clear ~ delete saved expr"<<endl;
    cout<<"exit"<<endl;
    cout<<">";
}



int main()
{
    string x;
    while(cin>>x)
    {
        if(x=="print")
        {
            cout<<evall(parse())<<endl;
        }
        else if(x=="clear")
        {
            calc::var().clean();
        }
        else if(x=="assign")
        {
            double p=evall(parse());
            cin>>x;
            cin>>x;
            calc::var(x,p);
        }
        else if(x=="exit")
            x=EOF;
    }
    return 0;
}