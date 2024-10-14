#include <sstream>
#include <iostream>
#include <cmath>

#include "utils.cpp"

#include "line.h"

Line::Line(int x1, int y1, int x2, int y2, const std::string& color, FillMode fillMode)
    : x1(x1), y1(y1), x2(x2), y2(y2) {
    this->color = color;
    this->ID = generateID(x1 + y1, color, x2 + y2);
}

void Line::draw(std::vector<std::vector<char>>& board) const {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    char drawChar = color[0];

    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = dx / static_cast<float>(steps);
    float yIncrement = dy / static_cast<float>(steps);

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; ++i) {
        int roundedX = static_cast<int>(round(x));
        int roundedY = static_cast<int>(round(y));

        if (roundedX >= 0 && roundedX < BOARD_WIDTH && roundedY >= 0 && roundedY < BOARD_HEIGHT) {
            board[roundedY][roundedX] = drawChar;
        }

        x += xIncrement;
        y += yIncrement;
    }
}

void Line::move(int newX, int newY) {
    return;
}

void Line::moveLine(int newX1, int newX2, int newY1, int newY2) {
    x1 = newX1;
    x2 = newX2;

    y1 = newY1;
    y2 = newY2;
}

bool Line::isPointOnLine(int x, int y) const {
    int dx = x2 - x1;
    int dy = y2 - y1;

    return (dy * (x - x1) == dx * (y - y1));
}

std::string Line::getInfo() const {
    std::ostringstream info;
    info << getID() << " Line " << x1 << " " << y1 << " " << x2 << " " 
        << y2 << " " << color << " " << "Fill";

    return info.str();
}

void Line::edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) {
    std::cout << "Cannot edit a line, since it has no dimensional attributes.\n";
    return;
}

void Line::paint(const std::string& newColor) {
    color = newColor;
}