#include "GenerateGraphics.h"
#include <fstream>
#include <iomanip> 

void GenerateGraphics::generateBarChart(const std::unordered_map<std::string, int> &data, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << fileName << std::endl;
        return;
    }

    file << "Bar Chart\n";
    file << "==========\n";

    for (const auto &entry : data)
    {
        file << std::setw(15) << std::left << entry.first << " | ";
        for (int i = 0; i < entry.second; ++i)
        {
            file << "#";
        }
        file << " (" << entry.second << ")\n";
    }

    file.close();
    std::cout << "Bar Chart gerado com sucesso em: " << fileName << std::endl;
}

void GenerateGraphics::generatePieChart(const std::unordered_map<std::string, int> &data, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Erro ao abrir o arquivo: " << fileName << std::endl;
        return;
    }

    int total = 0;
    for (const auto &entry : data)
    {
        total += entry.second;
    }

    if (total == 0)
    {
        file << "Não é possível gerar o gráfico de pizza: total dos valores é zero.\n";
        file.close();
        return;
    }

    file << "Pie Chart\n";
    file << "==========\n";

    for (const auto &entry : data)
    {
        double percentage = static_cast<double>(entry.second) / total * 100;
        file << std::setw(15) << std::left << entry.first 
             << " - " << std::fixed << std::setprecision(2) << percentage << "% (" 
             << entry.second << ")\n";
    }

    file.close();
    std::cout << "Pie Chart gerado com sucesso em: " << fileName << std::endl;
}
