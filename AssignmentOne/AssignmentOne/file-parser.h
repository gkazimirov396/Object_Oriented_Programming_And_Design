#pragma once

#include <string>
#include <vector>

#include "airplane.h"

class FileParser {
public:
    static std::vector<Airplane> readFile(const std::string& filePath);
};
