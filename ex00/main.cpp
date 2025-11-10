
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	(void)av;
	if (ac < 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return -1;
	}
	BitcoinExchange bc;
	try
	{
		bc.openFile(av[1]);
		bc.readData();
		bc.predict();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	

}
