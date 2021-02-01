#include <iostream>
#include <random>
#include <fstream>

int main()
{
    auto gen=std::mt19937{std::random_device{}()};
    auto ug=std::uniform_real_distribution<double>{0,100};
    auto bg=std::binomial_distribution<int>{100,0.5};
    auto ng=std::normal_distribution<double>{10,3};

    std::ofstream uf("uf.csv");
    std::ofstream bf("bf.csv");
    std::ofstream nf("nf.csv");


    for(int i=0;i<1000;i++)
    {
        uf<<ug(gen)<<std::endl;
        bf<<bg(gen)<<std::endl;
        nf<<ng(gen)<<std::endl;
    }

    return 0;
}