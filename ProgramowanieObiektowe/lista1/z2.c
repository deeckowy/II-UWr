#include <stdio.h>
#include <stdlib.h>
#include "ulamek.h"
int main()
{
    Ulamek *u1;
    Ulamek *u2;
    Ulamek *u;
    u1 = nowy(3, -9);
    u2 = nowy(7, 3);
    odejmijj(u1, u2);
    printf("%d/%d\n",u2->licznik,u2->mianownik);
    return 0;
}