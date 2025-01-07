#include <iostream>
#include <vector>
#include <unordered_map>
#include "JsonReader.h"
#include "Human.h"
#include "CalculateMetrics.h"
#include "GenerateGraphics.h"

int main()
{
    std::string filePath = "../wikidata_final_results.json";
    std::vector<Human> humans = JsonReader::parseHumans(filePath);
    std::unordered_map<std::string, int> genders = CalculateMetrics::simpleItemRatio(humans);
    std::unordered_map<std::string, int> religions = CalculateMetrics::compositeItemRatio(humans, "religion");
    std::unordered_map<std::string, int> professions = CalculateMetrics::compositeItemRatio(humans, "profession");

    GenerateGraphics::generateBarChart(genders, "barchart.txt");
    GenerateGraphics::generatePieChart(religions, "piechartReligions.txt");
    GenerateGraphics::generatePieChart(professions, "piechartProfessions.txt");

    std::cout << "Média de idade: " << CalculateMetrics::averageAge(humans) << std::endl;
    std::cout << "\n";

    std::cout << "Gêneros: " << std::endl;
    for (const auto &pair : genders)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "\n";

    std::cout << "Profissões: " << std::endl;
    for (const auto &pair : professions)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::cout << "\n";

    std::cout << "Religiões: " << std::endl;
    for (const auto &pair : religions)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}