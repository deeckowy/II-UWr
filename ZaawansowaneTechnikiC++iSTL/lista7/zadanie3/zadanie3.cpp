#include <iostream>
#include <random>
#include <algorithm>
#include <fstream>

int main(int argc,char **argv)
{
    if(argc!=3)
    {
        std::cout<<"Usage: "<<argv[0]<<"{number of characters} {name of file}\n";
        return EXIT_FAILURE;
    }
    std::ofstream out(argv[2]);
    std::mt19937 defeng{std::random_device{}()};
    double g=40000.0;
    std::discrete_distribution<int> dist{21912/g,16587/g,14810/g,14003/g,13318/g,12666/g,11450/g,10977/g,10795/g, 	 
        7874/g,7253/g,5246/g,4943/g,4761/g,4200/g,3853/g,3819/g,3693/g,3316/g,2715/g,2019/g,1257/g, 
        315/g,205/g,188/g,128/g};	 
    
    std::string table="ETAOINSRHDLUCMFYWGPBVKXQJZ";
    std::transform(table.begin(),table.end(),table.begin(),[](auto c){return std::tolower(c);});
    std::binomial_distribution<> bdist(11,0.5);
    int n=std::atoi(argv[1]);
    for(int i=0;i<n;i++)
    {
        std::string word="";
        int bound=bdist(defeng)+1;
        for(int i=0;i<bound;i++)
            word+=table[dist(defeng)];
        out<<word<<" ";
    }   
    return 0;
}