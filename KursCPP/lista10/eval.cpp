#include "eval.hpp"

stack::stack(){}

void stack::push(calc::symbol* item)
{
    stac.push_back(item);
}

calc::symbol* stack::pull()
{
    if(!stac.empty())
    {
        long t1=stac.size()-1;
        calc::symbol* item=stac[t1];
        stac.erase(stac.begin()+t1);
        return item;
    }
    else 
        std::clog<<"Bad expresion\n";
        return new calc::symbol();
} 

double evall(std::vector<calc::symbol*> exprr)
{
    stack ex;
    for(auto i:exprr)
    {
        if(dynamic_cast<calc::number*>(i))
            ex.push(i);
        else if(dynamic_cast<calc::constt*>(i))
            ex.push(i);
        else if(dynamic_cast<calc::funbin*>(i))
        {
            double y=ex.pull()->eval();
            double x=ex.pull()->eval();            
            ex.push(new calc::number(i->eval(x,y)));
        }
        else if(dynamic_cast<calc::funun*>(i))
        {
            calc::number* x=dynamic_cast<calc::number*>(ex.pull());
            ex.push(new calc::number(i->eval(x->eval())));
        }
        else 
            std::clog<<"Invalid expression\n";
    }
    return ex.pull()->eval();
}