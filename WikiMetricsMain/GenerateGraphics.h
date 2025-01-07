#ifndef GENERATEGRAPHICS_H
#define GENERATEGRAPHICS_H

#include <iostream>
#include <unordered_map>

class GenerateGraphics
{
public:
    static void generateBarChart(const std::unordered_map<std::string, int> &data, const std::string &fileName);
    static void generatePieChart(const std::unordered_map<std::string, int> &data, const std::string &fileName);
};

#endif