#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
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

        std::regex invalidProfessionRegex("^Q\\d+$");

        for (const auto &item : j.items())
        {
            const std::string &human_id = item.key();
            const auto &person_data = item.value();

            std::string name = person_data.contains("humanLabel") && !person_data["humanLabel"].is_null() ? person_data["humanLabel"] : "";
            std::string gender = person_data.contains("sex_or_genderLabel") && !person_data["sex_or_genderLabel"].is_null() ? person_data["sex_or_genderLabel"] : "";
            std::string birthDate = person_data.contains("date_of_birth") && !person_data["date_of_birth"].is_null() ? person_data["date_of_birth"] : "";
            std::string deathDate = person_data.contains("date_of_death") && !person_data["date_of_death"].is_null() ? person_data["date_of_death"] : "";
            std::string professions = person_data.contains("professions") && !person_data["professions"].is_null() ? person_data["professions"] : "";
            std::string religions = person_data.contains("religions") && !person_data["religions"].is_null() ? person_data["religions"] : "";

            if (professions.find("Q36180") != std::string::npos || professions.find("Q628099") != std::string::npos)
            {
                std::string new_professions;
                std::istringstream stream(professions);
                std::string profession;
                bool first = true;

                while (std::getline(stream, profession, ','))
                {
                    if (!first)
                    {
                        new_professions += ", ";
                    }
                    first = false;
                    profession = profession.substr(profession.find_first_not_of(" "), profession.find_last_not_of(" ") + 1);
                    if (profession == "Q36180")
                    {
                        new_professions += "Escritor";
                    }
                    else if (profession == "Q628099")
                    {
                        new_professions += "Treinador de Futebol";
                    }
                    else
                    {
                        new_professions += profession;
                    }
                }

                professions = new_professions;
            }

            if (religions.find("Igreja Católica") != std::string::npos || religions.find("Q5043") != std::string::npos)
            {
                std::string new_religions;
                std::istringstream stream(religions);
                std::string religion;
                bool first = true;

                while (std::getline(stream, religion, ','))
                {
                    if (!first)
                    {
                        new_religions += ", ";
                    }
                    first = false;
                    religion = religion.substr(religion.find_first_not_of(" "), religion.find_last_not_of(" ") + 1);
                    if (religion == "Igreja Católica")
                    {
                        new_religions += "catolicismo";
                    }
                    else if (religion == "Q5043")
                    {
                        new_religions += "Cristianismo";
                    }
                    else
                    {
                        new_religions += religion;
                    }
                }

                religions = new_religions;
            }

            humans.push_back(Human(name, gender, birthDate, deathDate, professions, religions));
        }
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo!" << std::endl;
    }

    return humans;
}
