#pragma once

#include <vector>
#include <string>

class Shape {
public:
    virtual void draw(std::vector<std::vector<char>>& board) = 0;
    virtual std::string getInfo() const = 0; 
    virtual ~Shape() {}
};
