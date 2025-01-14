#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "Human.h"

Human::Human(std::string name, std::string gender,
             std::string birthDate, std::string deathDate,
             std::string professions, std::string religions,
             std::string educations)
    : name(name), gender(gender), birthDate(birthDate),
      professions(professions), religions(religions), educations(educations)
{
    if (deathDate.empty() || deathDate.size() > 20)
    {
        deathDate = "";
    }
    else
    {
        deathDate = this->deathDate;
    }
}

std::string Human::getName() const
{
    return name;
}
std::string Human::getGender() const
{
    return gender;
};
std::string Human::getBirthDate() const
{
    return birthDate;
};
std::string Human::getDeathDate() const
{
    return deathDate;
};
std::string Human::getProfessions() const
{
    return professions;
};
std::string Human::getReligions() const
{
    return religions;
};
std::string Human::getEducations() const
{
    return educations;
};

int Human::calculateAge() const
{
    std::tm tm = {};

    if (strptime(getBirthDate().c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm) != nullptr)
    {
        if (getDeathDate().size() > 20)
        {
            return -1;
        }

        std::time_t t = std::time(nullptr);

        int diaNascimento = tm.tm_mday;
        int mesNascimento = tm.tm_mon + 1;
        int anoNascimento = tm.tm_year + 1900;

        int idade = 0;
        int mesParametro = 0;
        int diaParametro = 0;

        if (!getDeathDate().empty())
        {
            if (strptime(getDeathDate().c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm) != nullptr)
            {
                diaParametro = tm.tm_mday;
                mesParametro = tm.tm_mon + 1;
                int deathYear = tm.tm_year + 1900;

                idade = deathYear - anoNascimento;
            }
            else
            {
                std::cout << "Erro ao converter a data de falecimento: " << getDeathDate() << std::endl;
                return -1;
            }
        }
        else
        {
            std::tm *dataAtual = std::localtime(&t);
            diaParametro = dataAtual->tm_mday;
            mesParametro = dataAtual->tm_mon + 1;
            int anoAtual = dataAtual->tm_year + 1900;

            idade = anoAtual - anoNascimento;
        }

        if (mesParametro < mesNascimento || (mesParametro == mesNascimento && diaParametro < diaNascimento))
        {
            idade--;
        }

        return idade;
    }
    else
    {
        std::cout << "Erro ao converter a data de nascimento." << std::endl;
        return -1;
    }
};

void Human::toString() const
{
    std::cout << "Nome: " << getName() << std::endl;
    std::cout << "Gênero: " << getGender() << std::endl;
    std::cout << "Idade: " << calculateAge() << std::endl;
    std::cout << "Dia do nascimento: " << getBirthDate() << std::endl;
    if (getDeathDate() != "")
    {
        std::cout << "Dia do falecimento: " << getBirthDate() << std::endl;
    }
    std::cout << "Profissão: " << getProfessions() << std::endl;
    std::cout << "Religião: " << getReligions() << std::endl;
    std::cout << "Educação: " << getEducations() << std::endl;

    std::cout << "" << std::endl;
};
