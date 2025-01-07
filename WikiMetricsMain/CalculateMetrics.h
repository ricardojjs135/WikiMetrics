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
    static std::string birthChat(const std::vector<Human> &humans);          // Plotar as coordenadas dos locais de nascimento em um mapa
    static std::string mostPopularSchools(const std::vector<Human> &humans); // Escolas mais populares
};

#endif