#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#ifndef _NIFS3_HPP_
#define _NIFS3_HPP_

class nifs3
{
    private:
        std::vector<double> xs;       
        std::vector<double> ys;
        std::vector<double> M;
        double h;
        int size;

    public:
        nifs3(const std::vector<double>& x,const std::vector<double>& y);
        double get_val(const double& x);
};


#endif