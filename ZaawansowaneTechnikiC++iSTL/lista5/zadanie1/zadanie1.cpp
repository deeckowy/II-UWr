#include <iostream>
#include <list>
#include <forward_list>
#include <cctype>
#include <vector>

auto op_prio(auto c)
{
    if(c=='+'||c=='-')
        return 1;
    else if(c=='*'||c=='/'||c=='%')
        return 2;
    else if(c=='^')
        return 3;
    else 
        return 0;
}

auto make_list(auto expr)
{
    std::list<char> out{};
    for(int i=0;i<expr.size();i++)
        out.push_back(expr[i]);
    return std::move(out);
}

auto make_onp(auto list)
{
    std::vector<char> stack;
    std::vector<char> onp_expr;
    for(auto& l:list)
    {
        if(isalnum(l))
            onp_expr.push_back(l);
        else if(l=='(')
            stack.push_back(l);
        else if(op_prio(l))
        {
            while(!stack.empty()&&(op_prio(stack.back())>=op_prio(l)))
            {
                onp_expr.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(l);
        }
        else
        {
            while(!stack.empty()&&stack.back()!='(')
            {
                onp_expr.push_back(stack.back());
                stack.pop_back();
            }
            stack.pop_back();
        }
    }
    while(!stack.empty())
    {
        onp_expr.push_back(stack.back());
        stack.pop_back();
    }

    return std::move(onp_expr);
}




int main()
{
    std::string expr;
    std::cout<<"Podaj wyrazenie arytmetyczne: "<<std::endl;
    std::cin>>expr;
    std::cin.ignore();
    auto li=make_list(expr);
    auto onp=make_onp(li);
    for(auto& x:onp)
        std::cout<<x<<" ";
    std::cout<<std::endl;
    return 0;
}