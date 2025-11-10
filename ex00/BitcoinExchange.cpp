#include "BitcoinExchange.hpp"


const char* BitcoinExchange::DataBaseFileNotFoundException::what() const throw()
{
    return "BitcoinExchange:: Could not open Datbase file";
}

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& Cdb) : _db(Cdb._db)
{}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& Cdb)
{
    if(this != &Cdb)
        _db = Cdb._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{}

void BitcoinExchange::openFile(char* filename)
{
    _inputFile.open(filename);
    if(!_inputFile.is_open())
        throw DataBaseFileNotFoundException();
}

void BitcoinExchange::readData()
{
    std::ifstream dbFile;
    dbFile.open("data.csv");
    if(!dbFile.is_open())
        throw DataBaseFileNotFoundException();
    std::string line;
    getline(dbFile, line);
    while (dbFile.eof() == false)
    {
        getline(dbFile, line);
        std::string data;
        std::string rate;
        size_t comma  = line.find(',');
        if(comma == std::string::npos)
            continue;
        data = line.substr(0, comma);
        rate = line.substr(comma + 1);
        _db[data] = std::atof(rate.c_str());
    }
    dbFile.close();
}

bool BitcoinExchange::isNumber(const std::string& str)
{
    std::string::const_iterator it = str.begin();
    while(it != str.end())
    {
        if(!std::isdigit(*it))
            return false;
        it++;
    }
    return true;
}

bool BitcoinExchange::isValidDate(std::string& date)
{
    if(!date.empty() && date[date.length() - 1] == ' ')
    date.erase(date.length() - 1);
    if(date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    struct tm time = {};
    char * result = strptime(date.c_str(), "%Y-%m-%d", &time);
    if(!result || *result != '\0')
        return false;
    time.tm_isdst = -1;
    time_t t = mktime(&time);
    if(t == -1)
        return false;
    try
    {
        int year = std::atoi(date.substr(0,4).c_str());
        int month = std::atoi(date.substr(5,2).c_str());
        int day = std::atoi(date.substr(8,2).c_str());
        if(time.tm_year + 1900 != year || time.tm_mon+1 != month || time.tm_mday != day)
            return false;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return true;
    
}

bool BitcoinExchange::isDecimal(std::string& str)
{
	size_t i = 0;

	if (str.empty())
		return false;
	while (str[i] && std::isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (std::isdigit(str[i]))
		i++;
	if (i && str[i] == '.' && std::isdigit(str[i - 1]))
		i++;
	while (i && std::isdigit(str[i]))
		i++;
	if (i && !std::isdigit(str[i - 1]))
		return false;
	while (std::isspace(str[i]))
        i++; 
	return (i >= str.length());
}

void BitcoinExchange::predict()
{
	std::string line;
	std::string date;
	std::string rate;

	if (!_inputFile.is_open())
		throw DataBaseFileNotFoundException();
	while (_inputFile.eof() == false)
	{
		getline(_inputFile, line);
		if (line == "date | value")
			continue;
		size_t pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		date = line.substr(0, pipe);
		rate = line.substr(pipe + 1);
		if (!isValidDate(date))
		{
			std::cout << "Error: bad date  => " << date <<  std::endl;
			continue;
		}
		if (!isDecimal(rate))
		{
			std::cout << "Error: bad value => " << rate << std::endl;
			continue;
		}
		float value = std::strtof(rate.c_str(), NULL);
		if (value < 0)
		{
			std::cout << "Error: not a positive number."<< std::endl;
			continue;
		}
		if (value > 1000.0f)
        {
            std::cout << "Error: too large a number." << '\n';
            continue;
        }
		std::map<std::string, float>::iterator it = _db.lower_bound(date);
		if (it != _db.begin() && it->first != date)
			--it;
		std::cout << date << " => " << value << " = " << it->second * value << std::endl;
    }
}
