#pragma once

#include "shape.h"

class Rectangle : public Shape {
    int x, y, width, height;

public:
    Rectangle(int x, int y, int width, int height);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};
