#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define uli unsigned int  

//3
typedef struct A
{
    char a;
    char b;
    char c;
    char d;
    char e;
}A;
/* procesor zapisuje dane w 8 bajtowych blokach i dopelnia bloki
jesli nastepny obiekt zajmuje wiecej niz pozostale miejsce zapisujac
zmienna w nastepnym bloku */
typedef struct B
{
    uint16_t a;//2 bajty
    //A x;//16 bajtow
    void* c;// 8 bajtow
    double b;// 8 bajtow
}B;

//4 
/*
- <<volatile>> - zmienna ulotna - dodanie violatile do zmiennej
powoduje ze kompilator wezmie pod uwage ze zmienna moze zostac zmieniona
nie tylko przez nasz kod
- <<static>> - zmienna nie usuwana przy zakonczeniu funkcji i zachowuje
swoja wartosc  - jest zapisywana w tej samej pamieci co zmienne globalne
i inicjowana wartoscia 0, zmienna ta jest dostepna tylko w obrebie funkcji
- <<restrict>> - wskaznik, ktory jest jedynym wskaznikiem na dany obszar
pamieci 
*/

//5
/*
    s+=b[j+1]+b[--j];

        |
        V

    t := j+1
    t1 := t*4
    t2 := b[t1]
    j := j-1
    t3:= j*4
    t4 := b[t3]
    s := s+t2
    s := s+t5

    a[i++]-=*b*(c[j*2]+1);

            |
            V

    t := j*2
    t1 := j*4
    t2 := c[t1]
    t3 := t2 + 1
    t4 := &b 
    t5 := t3 * t4
    t6 := i * 4
    t7 := a[t6]
    a[t6] := t7 - t5
    i= i + 1
*/

//6 
/*
    t=us
    t1=1*8
    t2=t+t1
    t3=t2+0
    t4=*t3
    t5=us
    t6=j*8
    t7=t5+t6
    t8=t7+5
    t9=*t8
    t10=t9+t4
    t11=vs
    t12=t11+6
    *t12=t10
*/


uli doin(uli x,uli k,uli i)//1
{
    x=x&(1<<i)?x|(1<<k):x&~(1<<k);
    return x;
}

int nbits(uli n)//z2 - sumowanie bitow po 2,4,8,16
{
    n=(n&0x55555555)+((n>>1)&0x55555555);
    n=(n&0x33333333)+((n>>2)&0x33333333);
    n=(n&0x0F0F0F0F)+((n>>4)&0x0F0F0F0F);
    n=(n&0x00FF00FF)+((n>>8)&0x00FF00FF);
    return (n&0xFF)+(n>>16);
}

void secret(uint8_t *to, uint8_t *from, size_t count) 
{
    size_t n = (count + 7) / 8;
    switch (count % 8) 
    {
        case 0: do 
        { 
            *to++ = *from++;
            case 7:      {printf("XD");*to++ = *from++;}
            case 6:      *to++ = *from++;
            case 5:      *to++ = *from++;
            case 4:      *to++ = *from++;
            case 3:      *to++ = *from++;
            case 2:      *to++ = *from++;
            case 1:      *to++ = *from++;
        } while (--n > 0);
    }
}
int main()
{
    printf("%u\n",doin(2,1,0));
    printf("%i\n",nbits(3274108));
    printf("%lu\n",sizeof(A));
    printf("%lu\n",sizeof(B));

    return 0;
}
