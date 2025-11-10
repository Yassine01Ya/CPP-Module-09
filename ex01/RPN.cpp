#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN& rpn): _rpnOp(rpn._rpnOp)
{}

RPN& RPN::operator=(const RPN rpn)
{
    if(this != &rpn)
        _rpnOp = rpn._rpnOp;
    return *this;
}

RPN::~RPN()
{}

static inline bool isNumeric(std::string& str)
{
    size_t i = 0;
    for(;i < str.length() && std::isdigit(str[i]); i++)
        ;
    if(i > 0 && i == str.length())
        return true;
    return false;
}

static bool implOperation(std::stack<double>& _stack, std::string op)
{
    double num1 = _stack.top();
    _stack.pop();
    double num2 = _stack.top();
    _stack.pop();
    if(op == "+")
        _stack.push(num2 + num1);
    else if(op == "-")
        _stack.push(num2 - num1);
    else if(op == "*")
        _stack.push(num2 * num1);
    else if(op == "/")
    {
        if(num1 == 0)
        {
            std::cout << "Error: Dividing by zero\n";
            return false;
        }
        _stack.push(num2 / num1);
    }
    return true;
}

void RPN::solve(std::istringstream& op)
{
    while(_rpnOp.size())
        _rpnOp.pop();
    while(op.eof() == false)
    {
        std::string str;
        op >> str;
        if(str.length() == 0)
            break;
        if(isNumeric(str))
            _rpnOp.push(std::strtol(str.c_str(), NULL, 10));
        else if (_rpnOp.size() > 1 && (str == "+" || str == "-" || str == "*" || str == "/") && implOperation(_rpnOp,str))
            ;
        else
        {
            std::cout << "Error\n";
            return;
        }
    }
    if(_rpnOp.size() == 1)
        std::cout << _rpnOp.top() << '\n';
    else
        std::cout << "Error\n";
}