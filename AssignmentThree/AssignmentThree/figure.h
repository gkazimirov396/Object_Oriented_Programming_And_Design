#pragma once

#include <vector>
#include <string>

enum class FillMode {
    Frame, 
    Fill   
};

class Figure {
public:
    virtual ~Figure() = default;

    virtual void draw(std::vector<std::vector<char>>& board) const = 0;
    virtual std::string getInfo() const = 0;

    virtual void move(int x, int y) = 0;
    virtual void edit(const std::vector<int>& params) = 0;
    virtual void paint(const std::string& color) = 0;

    std::string getID() const { return ID; }
protected:
    std::string ID;
    std::string color;
    FillMode fillMode;
};
