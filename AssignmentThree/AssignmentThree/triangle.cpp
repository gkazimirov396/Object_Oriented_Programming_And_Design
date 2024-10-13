#include <string>
#include <sstream>

#include "utils.cpp"

#include "triangle.h"
#include <iostream>

Triangle::Triangle(int x, int y, int height, const std::string& color, FillMode fillMode) 
    : x(x), y(y), height(height) {
    this->color = color;
    this->fillMode = fillMode;
    this->ID = generateID(x + y, color, height);
}

void Triangle::draw(std::vector<std::vector<char>>& board) const {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    if (x + height < 0 || x - height >= BOARD_WIDTH || y + height < 0 || y >= BOARD_HEIGHT || height <= 0) {
        return;
    }

    char drawChar = color[0];

    for (int i = 0; i < height; ++i) {
        int leftMost = x - i;
        int rightMost = x + i;
        int posY = y + i;

        if (posY >= BOARD_HEIGHT) break;

        if (leftMost >= 0 && leftMost < BOARD_WIDTH)
            board[posY][leftMost] = drawChar;
        if (rightMost >= 0 && rightMost < BOARD_WIDTH && leftMost != rightMost)
            board[posY][rightMost] = drawChar;

        if (fillMode == FillMode::Fill) {
            for (int j = leftMost + 1; j < rightMost; ++j) {
                if (j >= 0 && j < BOARD_WIDTH) {
                    board[posY][j] = drawChar;
                }
            }
        }
    }

    for (int j = 0; j < 2 * height - 1; ++j) {
        int baseX = x - height + 1 + j;
        int baseY = y + height - 1;

        if (baseX >= 0 && baseX < BOARD_WIDTH && baseY < BOARD_HEIGHT) {
            board[baseY][baseX] = drawChar;
        }
    }
}

void Triangle::edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) {
    if (params.size() != 1) {
        std::cout << "Error: Invalid argument count.\n";
        return;
    }

    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    int leftEdge = x - height + 1;
    int rightEdge = x + height - 1;
    int bottomEdge = y + height - 1;

    int newHeight = params[0];

    if (leftEdge >= BOARD_WIDTH || rightEdge < 0 ||  y < 0 || bottomEdge >= BOARD_HEIGHT) {
        std::cout << "Error: New width or height will cause the square to go out of the board boundaries.\n";

        return;
    }

    height = newHeight;
    std::cout << "Triangle height updated to " << newHeight << ".\n";
}

void Triangle::paint(const std::string& newColor) {
    color = newColor;
}

void Triangle::move(int newX, int newY) {
    x = newX;
    y = newY;
}

std::string Triangle::getInfo() const {
    std::ostringstream info;
    info << getID() << " Triangle " << x << " " << y << " " 
        << height << " " << color << " " << (fillMode == FillMode::Fill ? "Fill" : "Frame");

    return info.str();
}

bool Triangle::isPointInsideTriangle(int px, int py,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3) {
    int denominator = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);

    float alpha = ((y2 - y3) * (px - x3) + (x3 - x2) * (py - y3)) / (float)denominator;
    float beta = ((y3 - y1) * (px - x3) + (x1 - x3) * (py - y3)) / (float)denominator;
    float gamma = 1.0f - alpha - beta;

    return (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f);
}