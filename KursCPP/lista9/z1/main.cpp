#include <iostream>
#include "manip.hpp"
#include <vector>

using namespace std;

void test1()
{
    vector<pair<string,int>> cont;
    string x;
    int i=0;
    while(getline(cin,x))
    {
        cont.push_back(pair<string,int>(x,i));
        i++;
    }    
    int z=i;
    while(z--)
    {
        for(int k=0;k<i-1;k++)
        {
            if(cont[k].first>cont[k+1].first)
                swap(cont[k],cont[k+1]);
        }
    }
    for(int k=0;k<i;k++)
    {
        cout<<index(cont[k].second,2)<<cont[k].first<<endl;
    }
}


int main()
{
    char c;
    cout<<"Test ignore(1) ~ zostanie wypisany drugi znak z wejscia"<<colon;
    cin>>ignore(1)>>c;
    cout<<c<<endl;
    cout<<"Test przecinka i dwukropka";
    cout<<comma<<colon<<endl;
    cout<<"Test index ~ zostanie wypisany index 1 na 10 pozycji";
    cout<<endl<<index(1,10)<<endl;
    cout<<"Test z wektorem "<<colon<<endl;
    test1();
    return 0;
}