#include "wym_wyj.hpp"

using namespace std;

dzielenie_przez_0::dzielenie_przez_0(const int &a,const int &b)
{
    blad="Twoja liczba to "+to_string(a)+"/"+to_string(b)+" mianownik nie moze byc rowny 0 !'\n"
    +" Czy miales na mysli "+to_string(b)+"/"+to_string(a)+"?\n";
}

przekroczenie_zakresu::przekroczenie_zakresu(const obliczenia::wymierna &a,const obliczenia::wymierna &b,char typ)
{
    string t1="Twoje dzialania arytmetyczne przekroczyly zakres int-a\n"; 
    string t2="wyniki nie zostaly zapisane sprobuj najpierw wykonac inne dzialania !\n";
    string t3="Twoje dzialanie : "+to_string(a.getLiczn())+"/"+to_string(a.getMian());
    string t4=typ+to_string(b.getLiczn())+"/"+to_string(b.getMian())+"\n"; 
    blad=t1+t2+t3+t4;
}



  
