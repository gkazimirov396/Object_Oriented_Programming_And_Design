#pragma once

#include "shape.h"

class Square : public Shape {
    int x, y, width;
public:
    Square(int x, int y, int width);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};

