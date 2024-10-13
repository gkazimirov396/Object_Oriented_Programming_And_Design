#pragma once

#include "figure.h"

class Square : public Figure {
public:
    int x, y, width;

    Square(int x, int y, int width, const std::string& color, FillMode fillMode);

    void draw(std::vector<std::vector<char>>& board) const override;
    std::string getInfo() const override;

    void move(int newX, int newY) override;
    void edit(const std::vector<int>& params) override;
    void paint(const std::string& newColor) override;
};
