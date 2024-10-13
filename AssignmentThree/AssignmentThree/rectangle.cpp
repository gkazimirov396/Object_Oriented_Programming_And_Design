#include <iostream>
#include <sstream>

#include "utils.cpp"

#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height, const std::string& color, FillMode fillMode)
    : x(x), y(y), width(width), height(height) {
    this->color = color;
    this->fillMode = fillMode;
    this->ID = generateID(x + y, color, width + height);
}

void Rectangle::draw(std::vector<std::vector<char>>& board) const {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    int rightEdge = x + width - 1;
    int bottomEdge = y + height - 1;

    if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT || rightEdge < 0 || bottomEdge < 0) {
        return;
    }

    char drawChar = color[0];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int currentX = x + j;
            int currentY = y + i;

            if (currentX >= 0 && currentX < BOARD_WIDTH &&
                currentY >= 0 && currentY < BOARD_HEIGHT) {

                bool isOnEdge = (i == 0 || i == height - 1 || j == 0 || j == width - 1);

                if (fillMode == FillMode::Fill || isOnEdge) {
                    board[currentY][currentX] = drawChar;
                }
            }
        }
    }
}

void Rectangle::edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) {
    if (params.size() != 2) {
        std::cout << "Error: Invalid argument count.\n";
        return;
    }

    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    int newWidth = params[0];
    int newHeight = params[1];

    if (x + width > BOARD_WIDTH || y + height > BOARD_HEIGHT) {
        std::cout << "Error: New width or height will cause the square to go out of the board boundaries.\n";
        return;
    }

    width = newWidth;
    height = newHeight;
    std::cout << "Rectangle (width, height) updated to (" << newWidth << ", " << newHeight << ").\n";
}

void Rectangle::paint(const std::string& newColor) {
    color = newColor;
}

void Rectangle::move(int newX, int newY) {
    x = newX;
    y = newY;
}

std::string Rectangle::getInfo() const {
    std::ostringstream info;
    info << getID() << " Rectangle " << x << " " << y << " " << width << " " << height
        << " " << color << " " << (fillMode == FillMode::Fill ? "Fill" : "Frame");

    return info.str();
}