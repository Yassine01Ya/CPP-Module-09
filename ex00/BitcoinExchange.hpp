#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <exception>
#include <ctime>
#include <string>


class BitcoinExchange
{
private:
    std::map<std::string, float> _db;
    std::ifstream _inputFile;
    bool    isValidDate(std::string& date);
    bool    isNumber(const std::string& str);
    bool    isDecimal(std::string& str);

public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange& Cdb);
    BitcoinExchange& operator=(const BitcoinExchange& Cdb);
    ~BitcoinExchange();
    void    openFile(char* filename);
    void    readData();
    void    predict();
    class DataBaseFileNotFoundException:public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
};
