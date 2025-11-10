#include "RPN.hpp"

int main(int c, char** v)
{
    if (c == 2)
    {
        RPN rpn;
        std::istringstream sstr(v[1]);
        rpn.solve(sstr);
        return 0;
    }
    std::cout << "Bad arguments.\n"
              << "Usage: " << v[0] << " [rpn string example \"4 5 -\" or \"4 8 + 2 -\"]"
              << std::endl;
    return 1;
}