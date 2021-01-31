#include "parse.hpp"

bool is_number(std::string x)
{
    int i=0;
    int len=x.size();
    if(x[0]=='-'&&len!=1)i=1;
    else if(x[0]=='-')return false;
    for(;i<len;i++)
    {
        if(!isdigit(x[i])&&x[i]!='.')
            return false;
    }
    return true;
}

bool is_funun(std::string x){return x=="abs"||x=="sgn"||x=="floor"||x=="ceil"||x=="frac"||x=="sin"||x=="cos"||x=="atan"||x=="acot"||x=="ln"||x=="exp";}

bool is_funbin(std::string x){return x=="+"||x=="-"||x=="*"||x=="/"||x=="mod"||x=="min"||x=="max"||x=="pow";}

bool is_const(std::string x){return x=="pi"||x=="fi"||x=="e";}

calc::symbol* stofu(std::string x)
{      
    if(x=="abs")
        return new calc::abs();
    else if(x=="sgn")
        return new calc::sgn();
    else if(x=="floor")
        return new calc::floor();
    else if(x=="ceil")
        return new calc::ceil();
    else if(x=="sin")
        return new calc::sin();
    else if(x=="cos")
        return new calc::cos();
    else if(x=="atan")
        return new calc::atan();
    else if(x=="acot")
        return new calc::acot();
    else if(x=="ln")
        return new calc::ln();
    else 
        return new calc::exp();
}

calc::symbol* stofb(std::string x)
{
    if(x=="+")
        return new calc::add();
    else if(x=="-")
        return new calc::sub();
    else if(x=="*")
        return new calc::mult();
    else if(x=="/")
        return new calc::div();
    else if(x=="mod")
        return new calc::mod();
    else if(x=="min")
        return new calc::min();
    else if(x=="max")
        return new calc::max();
}


std::vector<calc::symbol*> parse()
{
    std::vector<calc::symbol*> exprrr;
    std::string x;
    while(std::cin>>x)
    {
        if(x=="|")break;
        calc::symbol* actsym;
        if(is_number(x))
            actsym=new calc::number(std::stod(x));
        else if(is_funun(x))
            actsym=stofu(x);
        else if(is_funbin(x))
            actsym=stofb(x);
        else if(is_const(x))
            actsym=new calc::constt(x);
        else if(calc::var().is_var(x))
            actsym=new calc::number(calc::var().eval(x));
        else 
            std::clog<<"Parse error!\n";

        exprrr.push_back(actsym);
    }
    return exprrr;
}