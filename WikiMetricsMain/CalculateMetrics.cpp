#include <iostream>
#include "CalculateMetrics.h"

std::string CalculateMetrics::genderRatio(const std::vector<Human> &humans)
{
    int men = 0;
    int woman = 0;
    int other = 0;
    for (Human human : humans)
    {
        if (human.getGender() == "masculino")
        {
            men++;
        }
        else if (human.getGender() == "feminino")
        {
            woman++;
        }
        else
        {
            other++;
        }
    }
    return "men," + std::to_string(men) + ",woman," + std::to_string(woman) + ",other," + std::to_string(other);
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
