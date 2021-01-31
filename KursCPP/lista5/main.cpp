#include <iostream>
#include "bitarr.hpp"

int main()
{
    bitarr t(46);// tablica 46-bitowa (zainicjalizowana zerami)
    bitarr u((uint64_t)45);// tablica 64-bitowa (sizeof(uint64_t)*8)
    bitarr v(t);// tablica 46-bitowa (skopiowana z t)
    bitarr w({1, 0, 1, 1, 0, 0, 0, 1}); // tablica 8-bitowa (przeniesiona)
    v[0] = 1;// ustawienie bitu 0-go bitu na 1
    t[45] = true;// ustawienie bitu 45-go bitu na 1
    bool b = v[1];// odczytanie bitu 1-go
    u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
    cout<<t<<endl;// wysietlenie zawartości tablicy bitów naekranie
    return 0;
}