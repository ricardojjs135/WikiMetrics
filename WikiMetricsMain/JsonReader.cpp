#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "JsonReader.h"

using json = nlohmann::json;

std::vector<Human> JsonReader::parseHumans(const std::string &filePath)
{
    std::vector<Human> humans;
    std::ifstream file(filePath);

    if (file.is_open())
    {
        json j;
        file >> j;

        // Itera sobre as chaves principais (URLs das pessoas)
        for (const auto &item : j.items()) 
        {
            // A chave é a URL da pessoa, mas não precisa ser usada diretamente
            const std::string &human_id = item.key();

            // Dentro de cada chave, os dados da pessoa estão na estrutura associada
            const auto &person_data = item.value();

            // Verificando se o campo existe e não é null
            std::string name = person_data.contains("humanLabel") && !person_data["humanLabel"].is_null() ? person_data["humanLabel"] : "";
            std::string gender = person_data.contains("sex_or_genderLabel") && !person_data["sex_or_genderLabel"].is_null() ? person_data["sex_or_genderLabel"] : "";
            std::string birthDate = person_data.contains("date_of_birth") && !person_data["date_of_birth"].is_null() ? person_data["date_of_birth"] : "";
            std::string deathDate = person_data.contains("date_of_death") && !person_data["date_of_death"].is_null() ? person_data["date_of_death"] : "";

            // Profissões e religiões, pode ser uma string ou uma lista
            std::string professions = person_data.contains("professions") && !person_data["professions"].is_null() ? person_data["professions"] : "";
            std::string religions = person_data.contains("religions") && !person_data["religions"].is_null() ? person_data["religions"] : "";

            // Criando o objeto Human e adicionando ao vetor
            humans.push_back(Human(name, gender, birthDate, deathDate, professions, religions));
        }
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo!" << std::endl;
    }

    return humans;
}
