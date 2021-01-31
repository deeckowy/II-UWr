#include "calc.hpp"
#include <cmath>

double calc::symbol::eval(){return -1.0;}
double calc::symbol::eval(double x){return -1.0;}
double calc::symbol::eval(double x,double y){return -1.0;}


double calc::number::eval()
{
    return val;
}

calc::var::var(std::string name,double val)
{
    var_map.insert(make_pair(name,val));
}

std::unordered_map<std::string,double> calc::var::var_map;

calc::var::var(){}


bool calc::var::is_var(std::string name)
{
    auto hit=var_map.find(name);
    return hit!=var_map.end();
}

double calc::var::eval(std::string name)
{
    auto hit=var_map.find(name);
    if(hit!=var_map.end())
    {
        return hit->second;
    }
    else 
    {
        std::clog<<"Variable not found\n";
        return -1.0;
    }
}

void calc::var::clean()
{
    var_map.clear();
}

calc::constt::constt(std::string name)
{
    double e=2.718281828459;
    double pi=3.141592653589;
    double fi=1.618033988750;
    if(name=="e")
        val=e;
    else if(name=="fi")
        val=fi;
    else if(name=="pi")
        val=pi;
    else 
        std::clog<<"Invalid const name\n";
}

double calc::constt::eval(){return val;}


double calc::funbin::eval(double x,double y)
{
    std::clog<<"Invalid binary function name\n";
    return -1.0;
}

double calc::add::eval(double x,double y){return x+y;}

double calc::sub::eval(double x,double y){return x-y;}

double calc::mult::eval(double x,double y){return x*y;}

double calc::div::eval(double x,double y){return x/y;}

double calc::mod::eval(double x,double y){return std::fmod(x,y);}

double calc::min::eval(double x,double y){return x>y?y:x;}

double calc::max::eval(double x,double y){return x<y?y:x;}

double calc::pow::eval(double x,double y){return std::pow(x,y);}

double calc::funun::eval(double x)
{
    std::clog<<"Inavalid unary function name\n";
    return -1.0;
}

double calc::abs::eval(double x){return x>=0?x:x*-1.0;}

double calc::sgn::eval(double x){return x>0?1.0:x==0?0.0:-1.0;}

double calc::floor::eval(double x){return std::floor(x);}

double calc::ceil::eval(double x){return std::ceil(x);}

double calc::sin::eval(double x){return std::sin(x);}

double calc::cos::eval(double x){return std::cos(x);}

double calc::atan::eval(double x){return std::atan(x);}

double calc::acot::eval(double x){return std::pow(std::atan(x),-1.0);}

double calc::ln::eval(double x){return std::log(x);}

double calc::exp::eval(double x){return std::exp(x);}