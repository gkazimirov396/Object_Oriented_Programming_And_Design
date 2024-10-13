#include <iostream>
#include <sstream>
#include <algorithm>

#include "square.h"
#include "utils.cpp"

Square::Square(int x, int y, int width, const std::string& color, FillMode fillMode)
    : x(x), y(y), width(width) {
    this->color = color;
    this->fillMode = fillMode;
    this->ID = generateID(x + y, color, width);
}

void Square::draw(std::vector<std::vector<char>>& board) const {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    char drawChar = color[0];

    if (x + width < 0 || x >= BOARD_WIDTH || y + width < 0 || y >= BOARD_HEIGHT) {
        return;
    }

    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < width; ++j) {
            bool isOnEdge = (i == 0 || i == width - 1 || j == 0 || j == width - 1);

            if (fillMode == FillMode::Fill || isOnEdge) {
                int row = y + i;
                int col = x + j;

                if (row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH) {
                    board[row][col] = drawChar;
                }
            }
        }
    }
}


std::string Square::getInfo() const {
    std::ostringstream info;
    info << getID() << " Square " << x << " " << y << " " << width << " " << color
        << " " << (fillMode == FillMode::Fill ? "Fill" : "Frame");

    return info.str();
}

void Square::move(int newX, int newY) {
    x = newX;
    y = newY;
}

void Square::edit(const std::vector<int>& params, std::vector<std::vector<char>>& board) {
    if (params.size() != 1) {
        std::cout << "Error: Invalid argument count.\n";
        return;
    }

    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    int newWidth = params[0];

    if (x + newWidth > BOARD_WIDTH || y + newWidth > BOARD_HEIGHT) {
        std::cout << "Error: New width (" << newWidth << ") will cause the square "
            << "to go out of the board boundaries.\n";
        return;
    }

    width = newWidth;
    std::cout << "Square width updated to " << newWidth << ".\n";
}

void Square::paint(const std::string& newColor) {
    color = newColor;
}
