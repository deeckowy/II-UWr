#include <stdio.h>
#include <stdlib.h>
#include "figura.h"

int main()
{
    figura *f;
    f = nowy_kwadrat(1.0, -1.0, 3.0);
    printf("%f\n",pole(f));
    return 0;
}