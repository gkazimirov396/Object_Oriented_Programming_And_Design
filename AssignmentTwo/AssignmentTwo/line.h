#pragma once

#include "shape.h"

class Line : public Shape {
    int x1, y1, x2, y2;

public:
    Line(int x1, int y1, int x2, int y2);

    void draw(std::vector<std::vector<char>>& board) override;
    std::string getInfo() const override;
};

