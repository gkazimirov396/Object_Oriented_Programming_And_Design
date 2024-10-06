#pragma once

#include "figure.h"

class Rectangle : public Figure {
    int x, y, width, height;

public:
    Rectangle(int x, int y, int width, int height);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};
