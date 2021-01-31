#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int64_t>(output);

void doin_thins(int64_t in,int64_t prime)
{
    if(in==1)return;
    while(in!=1)
    {
        if(in%prime==0)
        {
            in/=prime;
            output.push_back(prime);    
        }
        else
        {
            prime++;
        }
        if(prime*prime>in)
        {
            output.push_back(in);
            break;
        }
        if(prime*prime<0)
        {
            output.push_back(in);
            break;
        }
    }
}

int64_t make_int(const char* in)
{
    string x(in);
    int i=0;
    string max={};
    if(x[0]=='-'){i=1;max="-9223372036854775808";}
    else max="9223372036854775807";
    if(x>max||x.size()>max.size()){throw invalid_argument(in);}
    for(i;i<x.size();i++)
    {
        if(!isdigit(x[i]))throw invalid_argument(in);
    }
    int64_t out=strtoll(in,NULL,0);
    if(x==max&&x[0]=='-')
    {
        out/=2;
        out*=-1;
        output.push_back(-1);
        output.push_back(2);
    }
    cout<<x<<endl;
    if(out<0)
    {
        out*=-1;
        output.push_back(-1);
    }
    return out;    
}

int main(int argc,char* argv[])
{
    if(argc>=2)
    {
        for(int i=1;i<argc;i++)
        {
            try
            {
                
                const char* tryin(argv[i]);
                int64_t x=make_int(tryin);
                doin_thins(x,2);
                cout<<x<<"=";
                for(auto i=output.begin();i!=output.end();++i)
                {
                    if(i==output.end()-1)
                    {
                        cout<<*i<<endl;
                    }
                    else cout<<*i<<"*";
                }
                output.clear();
            }
            catch(const exception& e)
            {
                cerr<<"invalid argument:"<<e.what()<<endl;
            }
            
        }
    }
    else
    {
        cerr<<"Aby skorzystać z programu po ./a.out wpisz liczbe ktorej rozklad na czynniki pierwsze chcesz uzyskac!"<<endl;
    }
    return 0;
}
