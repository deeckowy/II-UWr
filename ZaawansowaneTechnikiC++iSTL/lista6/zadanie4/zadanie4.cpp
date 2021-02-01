#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

auto fun(const auto& vec)
{
    int output[26]={0};
    long sum=0;
    for(auto& x:vec)  
    { 
        sum+=x.size();
        for(auto& c:x)
        {
            if(c>='a'&&c<='z')
                output[c-'a']++;
            else if(c>='A'&&c<='Z')
                output[c-'A']++;
        }
    }
    for(auto i=0;i<26;i++)
    {
        std::cout<<char(i+'a')<<":[";
        for(auto k=0;k<output[i]*100/sum;k++)
            std::cout<<"*";
        std::cout<<"]\n";
    }
}


int main(int argc,char** argv)
{
    if(argc!=2)
    {
        std::cerr<<"Usage: "<<argv[0]<<" <filename>"<<std::endl;
        exit(1);
    }
    std::fstream fil;
    std::vector<std::string> filcont;
    fil.open(argv[1]);
    std::string line;
    while(std::getline(fil,line))filcont.push_back(line);
    fil.close();
    fun(filcont);
    return 0;
}