#ifndef JSONREADER_H
#define JSONREADER_H

#include <iostream>
#include <vector>
#include "Human.h"

class JsonReader
{
public:
    static std::vector<Human> parseHumans(const std::string &filePath);
};

#endif
