#pragma once

#include <string>
#include <vector>

#include "airplane.h"

class FileReader {
public:
    static std::vector<Airplane> readConfigFile(const std::string& filePath);
};
