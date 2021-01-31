#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<pair<int,string>> rzym=
{
    {1000,"M"},
    {900,"CM"},
    {500,"D"},
    {400,"CD"},
    {100,"C"},
    {90,"XC"},
    {50,"L"},
    {40,"XL"},
    {10,"X"},
    {9,"IX"},
    {5,"V"},
    {4,"IV"},
    {1,"I"}
};

string bin2rom(int x)
{
    string out="";
    for(int i=0;i<rzym.size();i++)
    {
        while(x!=x%rzym[i].first)
        {
            x-=rzym[i].first;
            out+=rzym[i].second;
        }
    }
    return out;
}

int main(int argc,char* argv[])
{
    for(int i=1;i<argc;i++)
    {
        try
        {
            int x=0;
            string xd(argv[i]);
            for(int p=0;p<xd.size();p++){if(xd[p]>'9'||xd[p]<'0')throw invalid_argument(" - to nie jest liczba -> "+xd);}
            x=stoi(argv[i]);
            if(x>3999||x<1)throw invalid_argument(" - liczba jest spoza przedzialu 1-3999 ->"+xd);
            cout<<x<<" = "<<bin2rom(x)<<endl;
        }
        catch(const exception& e)
        {
            clog<<"Nieodpowiedni ciag znakow "<<e.what()<<endl;
        }
    }
    return 0;
}