#include <iostream>
#include <set>

using sos=std::set<std::string>;

int main()
{
    sos samplesos{"sample_string1","sample_string2","sample_string3","sample_string3","sample_string4"};
    for(const auto &s:samplesos)
        std::cout<<s<<std::endl;
    return 0;
}