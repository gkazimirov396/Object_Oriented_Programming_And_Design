#pragma once

#include <vector>
#include <string>

class Figure {
public:
    virtual void draw(std::vector<std::vector<char>>& board) = 0;
    virtual std::string getInfo() const = 0; 
};
