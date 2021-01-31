#include <stdio.h>
#include <limits.h>

/////1

__int64_t divby3(__int32_t x)
{
    __int64_t out=x;
    out=(out<<31);
    __int64_t div=0x55555555;
    return((out*div));
}   

////2
/*
    0.15625 == 0 01100 01000000000 == (-1)^0 * 2 ^ -3 * 1,25 ;; BIAS = exp - E
    0.15625 == 0 01111100 01000000000000000 = (-1)^0*2^-3*1,25 

    Half Float (16 bits) =  min -2^16+e maks 2^16-e  1.9990234375
    Single Float (32 bits ) min -2^128+e maks 2^128-e  1.9999998807907104
*/

///4
/*
    1 == #t
    2 == x=ujemna y=int max
    3 == #t
    4 == #t
    5 == dx=0 dy=1
*/

////5
//a
__uint32_t rev(__uint32_t x)
{
    return x^(1<<31);
}
//b
int flor(__uint32_t x)
{
    __uint32_t abs=0x7F800000;//0 11111111 0000..00
    x&=abs;
    return x=(x>>23)-127;
}
//c
_Bool Is_Equal(__uint32_t x,__uint32_t y){return (x==y)|((x|y)==INT_MIN);}
//d
_Bool Is_Greater(__uint32_t x,__uint32_t y){return ((x<y&((x>>31)==0))|(((x>>31)==1)&x>=y))&((x|y)!=INT_MIN);}//1000000000000...

///6
__uint32_t mult2(__uint32_t x,int i)
{
    if(x>=INT_MIN)
        return x;
    else
        return x;
}

__int32_t float2int(__int32_t x)
{
    
}


int main()
{
    printf("%d",divby3(-8));
    printf("\n%u\n",__INT32_MAX__-rev(-1));
    printf("%u\n",flor(__INT32_MAX__));
    printf("%d\n",Is_Equal(INT_MIN,0));
    printf("%d\n",Is_Greater(INT_MIN,0));
    mult2(,2);
    return 0;
}