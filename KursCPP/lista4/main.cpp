#include <iostream>
#include "stos.hpp"

using namespace std;

#define blad cerr<<"Stos nie istnieje/jest pusty!"<<endl<<endl;                

void show_menu()
{
    cout<<endl<<"a - stworz stos "<<endl;
    cout<<"b - dodaj wyraz na stos"<<endl;
    cout<<"c - zdejmij wyraz ze stosu"<<endl;
    cout<<"d - pokaz ostatni dodany na stos wyraz"<<endl;
    cout<<"e - wyjdz z programu"<<endl;
    cout<<"f - odwroc stos"<<endl;
    cout<<"x - pokaz stos"<<endl;
}

int main()
{
    char control='0';
    stos *X=nullptr;
    while(control!='e')
    {
        show_menu();
        if(X==nullptr)
            cout<<endl<<"Twoj stos nie zostal stworzony"<<endl;
        else
            cout<<endl<<"Twoj stos ma "<<X->rozmiar()<<" elementow"<<endl;        
        
        cin>>control;
        cout<<endl;
        switch(control)
        {
            case 'a':
            {
                int i=0;
                if(X!=nullptr)
                    X->~stos();
                cout<<"Podaj rozmiar stosu :"<<endl;
                cin>>i;
                if(i<100)
                    X=new stos(i);
                else
                    X=new stos();
                break;                
            }
            case 'b':
            {
                string x;
                cout<<"Podaj wyraz ktory ma byc dodany na stos"<<endl;
                cin>>x;
                if(X!=nullptr)
                    X->wloz(x);
                else
                    blad
                break;
            }
            case 'c':
            {
                if(X!=nullptr&&X->rozmiar()!=0)
                    cout<<"Wyraz "<<X->zdejmij()<<" zostal zdjety ze stosu"<<endl;
                else
                    blad
                break;
            }
            case 'd':
            {
                if(X!=nullptr&&X->rozmiar()!=0)
                    cout<<"Ostatni wyraz dodany na stos to "<<X->sprawdz()<<endl;
                else
                    blad
                break;                
            }
            case 'f':
            {
                if(X!=nullptr)
                {
                    stos XD=X->odwroc();
                    X=&XD;
                }
                else
                    blad
                break;                
            }
            case 'x':
            {
                cout<<"Twoj stos:"<<endl;
                cout<<*X;
                break;  
            }
        }
    }
    delete X;
    return 0;
}