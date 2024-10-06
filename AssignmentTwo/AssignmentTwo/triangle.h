#pragma once

#include "figure.h"

class Triangle : public Figure {
    int x, y, height;
public:
    Triangle(int x, int y, int height);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};
