#include "calc.hpp"
#include <vector>
#include <typeinfo>

#ifndef _EVAL_HPP_
#define _EVAL_HPP_

class stack
{
    private:
        std::vector<calc::symbol*> stac;
    public:
        stack();
        void push(calc::symbol* item);
        calc::symbol* pull();
};



double evall(std::vector<calc::symbol*> exprr);

#endif 