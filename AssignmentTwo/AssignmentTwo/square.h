#pragma once

#include "figure.h"

class Square : public Figure {
    int x, y, width;
public:
    Square(int x, int y, int width);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};

