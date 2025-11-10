#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>

class PmergeMe
{

private:
    std::deque<long>  _deque;
    std::vector<long> _vector;

public:
    PmergeMe(std::string numbers);
    PmergeMe(const PmergeMe& pmm);
    PmergeMe& operator=(const PmergeMe& pmm);
    ~PmergeMe();

private:
    template <class PairIterator>
    PairIterator BinarySearchPair(PairIterator begin, PairIterator end, std::pair<long, long> pair);
    template <class Container>
    typename Container::iterator BinarySearch(Container& container, long number);
    template <class Container, class PairContainer>
    bool MergeInsert(Container& container, std::string string);
    bool AreSorted();
    void PrintDeque(std::string numbers);
    void PrintVector(std::string numbers);
};