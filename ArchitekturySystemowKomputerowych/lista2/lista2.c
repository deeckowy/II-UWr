#include <stdio.h>
#include <stdbool.h>
/*
    -INT_MIN
    -#t
    -sqrt(INT_MAX+1)
    -#t
    -INT_MIN
    -#t
    -x,y<0
    -#t
    -#t
    -#t
*/


bool test(int x,int y){return x+y==(__uint32_t)x+(__uint32_t)y;}

bool test2(int x,int y){return x*~y+(__int32_t)y*(__int32_t)x==-x;}

//2
void swapp(int* x,int* y)
{
    *x^=*y;
    *y^=*x;
    *x^=*y;
}

//3
bool whaaa(int x,int y)
{
    int s=x+y;
    return ((~(x^y))&(1<<31))&(s^x);
}


//7
__int32_t abs(__int32_t x){return (x&(1<<31))*x+!(x&(1<<31))*x;}

//5
__int32_t threefours(__int32_t x)
{
    return (x&(1<<31))*((abs(x)>>2)*3)+!(x&(1<<31))*((x>>2)*3);
}

//9
__int32_t odd_ones(__uint32_t x)
{
    x=(x&0x55555555)+((x>>1)&0x55555555);
    x=(x&0x33333333)+((x>>2)&0x33333333);
    x=(x&0x0F0F0F0F)+((x>>4)&0x0F0F0F0F);
    x=(x&0x00FF00FF)+((x>>8)&0x00FF00FF);
    x=(x&0xFF)+(x>>16);
    return x&1;
}


int main()
{
    int x=55,y=5;
    int *z,*zz;
    z=&x;
    zz=&y;
    // scanf("%d",&x);
    // scanf("%d",&y);
    //printf("%d\n",test(x,y));
    printf("%d\n",test2(__INT_MAX__,__WINT_MIN__));
    printf("%d %d\n",*z,*zz);
    swapp(z,zz);
    printf("%d %d\n",*z,*zz);
    printf("%d\n",whaaa(-32198,__INT_MAX__));    
    printf("%d\n",__WINT_MIN__);
    printf("%d\n",odd_ones(3));
    printf("%d\n",abs(-12));
    printf("%d\n",threefours(-12));
    return 0;
}