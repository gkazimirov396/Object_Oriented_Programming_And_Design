#pragma once

#include "figure.h"

class Triangle : public Figure {
public:
    int x, y, height;
    Triangle(int x, int y, int height, const std::string& color, FillMode fillMode);

    void draw(std::vector<std::vector<char>>& board) const override;
    std::string getInfo() const override;

    void move(int newX, int newY) override;
    void edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) override;
    void paint(const std::string& newColor) override;
    bool isPointInsideTriangle(int px, int py);
};