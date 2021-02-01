#include <vector>
#include <algorithm>
#include <iostream>

#ifndef _APPROX_HPP_
#define _APPROX_HPP_



class polynomial 
{
    private:
        std::vector<double> coeff;
    public: 
        polynomial(const auto& cff):coeff(cff){}
        double get_val(const double& x)
        {
            auto s=1;
            auto output=0.0;
            for(auto i=0;i<coeff.size();i++)
            {
                output+=coeff[i]*s;
                s*=x;
            }
            return output;
        }
        polynomial operator+(polynomial p)
        {
            auto pc=p.coeff;
            std::vector<double> outcff;
            auto min=pc.size()<coeff.size()?pc.size():coeff.size();
            auto max=pc.size()>=coeff.size()?pc.size():coeff.size();
            auto rest=pc.size()>=coeff.size()?pc:coeff;
            int i=0;
            for(;i<min;i++)
                outcff.push_back(coeff[i]+pc[i]);
            for(;i<max;i++)
                outcff.push_back(rest[i]);
            return polynomial(outcff);
        }
        polynomial operator-(polynomial p)
        {
            auto pc=p.coeff;
            std::vector<double> outcff;
            bool is_first_greater=pc.size()<coeff.size()?true:false;
            auto min=pc.size()<coeff.size()?pc.size():coeff.size();
            auto max=pc.size()>=coeff.size()?pc.size():coeff.size();
            auto rest=pc.size()>=coeff.size()?pc:coeff;
            int i=0;
            for(;i<min;i++)
                outcff.push_back(coeff[i]-pc[i]);
            for(;i<max;i++)
                outcff.push_back((is_first_greater?rest[i]:-rest[i]));
            return polynomial(outcff);
        }
        polynomial operator*(const double& a)
        {
            auto cff=coeff;
            for(auto &x:cff)
                x*=a;
            return polynomial(cff);
        }     
        polynomial operator*(polynomial p)
        {
            auto pc=p.coeff;
            std::vector<double> outcff(pc.size()+coeff.size()-1,0.0);
            for(int i=0;i<coeff.size();i++)
                for(int j=0;j<pc.size();j++)
                    outcff[i+j]+=coeff[i]*pc[j];
            return polynomial(outcff);
        }
};

class approx
{
    private:
        std::vector<polynomial> polyn;
        std::vector<double> xs;
        std::vector<double> ys;
        std::vector<double> alphas;
        double scalar(polynomial p1,polynomial p2)
        {
            double sum=0.0;
            for(int i=0;i<xs.size();i++)
                sum+=p1.get_val(xs[i])*p2.get_val(xs[i]);
            return sum;
        }
        double scalar(polynomial p)
        {
            double sum=0.0;
            for(int i=0;i<xs.size();i++)
                sum+=p.get_val(xs[i])*ys[i];
            return sum;
        }
    public:
        approx(const auto& x,const auto& y):xs(x),ys(y)
        {
            polyn.push_back(polynomial(std::vector<double>{1}));
            auto tval=scalar(polyn[0],polyn[0]);
            auto c=scalar(polynomial(std::vector<double>{0,1})*polyn[0],polyn[0])/tval;
            polyn.push_back(polynomial(std::vector<double>{-c,1}));
            for(int i=2;i!=xs.size();i++)
            {
                auto d=1.0/tval;
                tval=scalar(polyn[i-1],polyn[i-1]);
                d*=tval;
                c=scalar(polynomial(std::vector<double>{0,1})*polyn[i-1],polyn[i-1])/tval;
                polyn.push_back(polynomial(std::vector<double>{-c,1})*polyn[i-1]+(polyn[i-2]*-d));
            }
            for(int i=0;i<xs.size();i++)
                alphas.push_back(scalar(polyn[i])/scalar(polyn[i],polyn[i]));
        }
        double get_val(double x,int prec)
        {
            auto output=0.0;
            for(int i=0;i<prec;i++)
                output+=alphas[i]*polyn[i].get_val(x);
            return output;
        }
        polynomial get_polyn()
        {
            polynomial output=polyn[0]*alphas[0];
            for(int i=1;i<xs.size()-15;i++)
                output=output+(polyn[i]*alphas[i]);
            return output;
        }

};

#endif // !_APROX_HPP_