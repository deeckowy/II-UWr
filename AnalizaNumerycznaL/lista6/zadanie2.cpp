#include <iostream>

/*
* Program liczby wspolczynniki dla 
wielomianu przedstawionego tutaj: https://www.desmos.com/calculator/cb6c0gokna
i wyswietla je w kolejnosci od najwiekszej potegi x-a,
wyniki otrzymuje stosując algorytm opisany w pdf-ie
*/




int main() 
{
    int x[3]={1,2,3};
    int b[4]={4,1,2,3};
    int a[4];
    auto n=3;

    a[n]=b[n];
    for(auto i=n-1;i>=0;i--)
    {
        a[i]=b[i];
        for(auto k=i;k<n;k++)
            a[k]=a[k]-x[i]*a[k+1];
    }
    for(auto i=n;i>=0;i--)
    {
        std::cout<<a[i]<<std::endl;
    }
    return 0;
}