#include "PmergeMe.hpp"

int main(int c, char **v)
{
    if (c > 1)
    {
        std::string args;
        for (int i = 1; i < c; i++)
        {
            args += v[i];        
            args += " ";        
        }
        PmergeMe p(args);
        return 0;
    }
    std::cout << "Bad arguments\nUsage: " << v[0] << " \"[Numbers ..]\"\n";
    return 1;
}