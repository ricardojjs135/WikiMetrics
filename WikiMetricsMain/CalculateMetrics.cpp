#include <iostream>
#include <unordered_map>
#include <sstream>
#include "CalculateMetrics.h"

std::unordered_map<std::string, int> CalculateMetrics::simpleItemRatio(const std::vector<Human> &humans)
{
    std::unordered_map<std::string, int> genderCount;

    for (const Human &human : humans)
    {
        if (human.getGender().empty())
        {
            continue;
        }
        genderCount[human.getGender()]++;
    }
    return genderCount;
}

std::unordered_map<std::string, int> CalculateMetrics::compositeItemRatio(const std::vector<Human> &humans, std::string item)
{
    std::unordered_map<std::string, int> itemCount;

    for (const Human &human : humans)
    {
        std::string itens;
        if(item == "religion"){
            itens = human.getReligions();
        }
        else if(item == "profession"){
            itens = human.getProfessions();
        }
        else if(item == "education"){
            itens = human.getEducations();
        }

        if (itens.empty())
        {
            continue;
        }

        std::istringstream ss(itens);
        std::string itemFormated;
        while (std::getline(ss, itemFormated, ','))
        {
            itemFormated.erase(0, itemFormated.find_first_not_of(" \t"));
            itemFormated.erase(itemFormated.find_last_not_of(" \t") + 1);

            if (!itemFormated.empty())
            {
                itemCount[itemFormated]++;
            }
        }
    }

    return itemCount;
}

int CalculateMetrics::averageAge(const std::vector<Human> &humans)
{
    if (humans.empty())
    {
        std::cerr << "Erro: O vetor está vazio. Não é possível calcular a média." << std::endl;
        return 0;
    }

    int sumAge = 0;
    int humansValideAgeSize = 0;

    for (const Human &human : humans)
    {
        if (sumAge > -1)
        {
            sumAge += human.calculateAge();
            humansValideAgeSize++;
        }
    }

    return sumAge / humansValideAgeSize;
}
