#pragma once

#include "shape.h"

class Triangle : public Shape {
    int x, y, height;
public:
    Triangle(int x, int y, int height);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};
