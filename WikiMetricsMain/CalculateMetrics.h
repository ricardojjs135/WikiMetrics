#ifndef CALCULATEMETRICS_H
#define CALCULATEMETRICS_H

#include <iostream>
#include <vector>
#include "Human.h"

class CalculateMetrics
{
public:
    static std::unordered_map<std::string, int> simpleItemRatio(const std::vector<Human> &humans); 
    static std::unordered_map<std::string, int> compositeItemRatio(const std::vector<Human> &humans, std::string item); 
    static int averageAge(const std::vector<Human> &humans);                 
};

#endif