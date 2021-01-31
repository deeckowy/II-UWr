#include <iostream>
#include "inf.hpp"
#include "outf.hpp"
#include <cstdlib>

using namespace std;

static const string file ="dane.txt";
//aby sprawdzic funkcjonalnosc dla innych typow wystarczy zmienic inta np na chara
#define test_type int
#define test_max 100

void test_uno(int amount)//test generuje amount intow i wpisuje je do pliku a nastepnie je odczytuje
{
    outf* t1=new outf(file);
    for(int i=0;i<amount;i++)
    {
        size_t* random_number=new size_t(rand()%test_max);
        t1->write(sizeof(test_type),(char*)random_number);
    }
    delete t1;
    inf* temp=new inf(file);
    for(int i=0;i<amount;i++)
    {
        test_type x;
        temp->read(sizeof x,(char*)&x);
        cout<<x<<endl;
    }
    delete temp;
}

void test_dos(int amount)
{
    inf* temp=new inf(file);
    for(int i=0;i<amount*sizeof(test_type);i++)
    {
        char x;
        temp->read(sizeof x,(char*)&x);
        if(x>31)
        {
            cout<<"in dec: "<<dec<<(int)x<<endl;
            cout<<"in hex: "<<hex<<(int)x<<endl;
        }
    }
    cout<<dec;
    delete temp;
}

int main()
{
    test_uno(12);    
    test_dos(12);
    return 0;
}