#pragma once

#include "figure.h"

class Line : public Figure {
public:
    int x1, y1, x2, y2;
    Line(int x1, int y1, int x2, int y2, const std::string& color, FillMode fillMode = FillMode::Fill);

    void draw(std::vector<std::vector<char>>& board) const override;
    std::string getInfo() const override;

    void move(int newX, int newY) override;
    void edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) override;
    void paint(const std::string& newColor) override;
};
