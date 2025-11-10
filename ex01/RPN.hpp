#pragma once 

#include<stack>
#include<string>
#include<iostream>
#include<cstdlib>
#include<sstream>

class RPN
{
private:
    std::stack<double>_rpnOp;
public:
    RPN();
    RPN(const RPN& rpn);
    RPN& operator=(const RPN rpn);
    ~RPN();
    void solve(std::istringstream& op);
};
