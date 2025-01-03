#ifndef CALCULATEMETRICS_H
#define CALCULATEMETRICS_H

#include <iostream>
#include <vector>
#include "Human.h"

class CalculateMetrics {
    public:
    static std::string genderRatio(const std::vector<Human>& humans); // Proporção de gêneros (ex: 234 M X 298 H)
    static int averageAge(const std::vector<Human>& humans); // Idade Média das pessoas no geral
    static std::string religionRatio(const std::vector<Human>& humans); // Proporção de religiões (ex: 68 católicos, 56 evangélicos, 29 umbandidstas...)
    static std::string birthChat(const std::vector<Human>& humans); // Plotar as coordenadas dos locais de nascimento em um mapa
    static std::string professionRatio(const std::vector<Human>& humans); // Proporção de profissões (as mais populares)
    static std::string mostPopularSchools(const std::vector<Human>& humans); // Escolas mais populares
};

#endif