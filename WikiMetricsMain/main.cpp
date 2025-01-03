#include <iostream>
#include <vector>
#include "JsonReader.h"
#include "Human.h"
#include "CalculateMetrics.h"

int main()
{
    std::string filePath = "../wikidata_final_results.json";
    std::vector<Human> humans = JsonReader::parseHumans(filePath);
    
    std::cout << "Gênero: " << CalculateMetrics::genderRatio(humans) << std::endl;
    std::cout << "Média: " << CalculateMetrics::averageAge(humans) << std::endl;

    return 0;
}