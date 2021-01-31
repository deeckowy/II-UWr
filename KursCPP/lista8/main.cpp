#include <iostream>
#include "list.hpp"
using namespace std;


void print_menu()
{
    cout<<endl;
    cout<<"Menu:"<<endl;
    cout<<"a - add elem to list"<<endl;
    cout<<"r - remove elem from list"<<endl;
    cout<<"c - check if list is sorted"<<endl;
    cout<<"s - sort list"<<endl;
    cout<<"d - delete list"<<endl;
    cout<<"l - show length of list"<<endl;
    cout<<"p - print list"<<endl;
    cout<<"e - exit"<<endl;
    cout<<">";
}


int main()
{
    list<int>* ll= new list<int>();
    char x='n';
    while (x!='e')
    {
        print_menu();
        cin>>x;
        cout<<endl;
        switch (x)
        {
            case 'a':
            {
                int z;
                cout<<"give a number: ";
                cin>>z;
                ll->add(z);
                break;
            }
            case 'r':
            {
                int z;
                cout<<"what elem should be removed ?";
                cin>>z;
                ll->rem(z);
                break;
            }
            case 'c':
            {
                if(check<int,checker<int>>(*ll))
                    cout<<"list is sorted";
                else 
                    cout<<"list isn't sorted";
                break;
            }
            case 's':
            {
                sort<int,checker2<int>>(ll);
                break;
            }
            case 'd':
            {
                delete ll;
                list<int>* ll= new list<int>();
                break;
            }
            case 'l':
            {
                cout<<"length of list - "<<ll->size();
                break;
            }
            case 'p':
            {
                cout<<*ll;
                break;
            }
        }
    }
    delete ll;
    return 0;
}