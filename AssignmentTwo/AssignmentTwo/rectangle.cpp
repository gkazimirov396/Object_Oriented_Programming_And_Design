#include <sstream>
#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

void Rectangle::draw(std::vector<std::vector<char>>& board) {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    int rightEdge = x + width - 1;
    int bottomEdge = y + height - 1;

    if (x >= BOARD_WIDTH || y >= BOARD_HEIGHT || rightEdge < 0 || bottomEdge < 0) {
        return;
    }

    for (int i = 0; i < width; ++i) {
        int currentX = x + i;

        if (y >= 0 && y < BOARD_HEIGHT && currentX >= 0 && currentX < BOARD_WIDTH) {
            board[y][currentX] = '*';
        }

        if (bottomEdge >= 0 && bottomEdge < BOARD_HEIGHT && currentX >= 0 && currentX < BOARD_WIDTH) {
            board[bottomEdge][currentX] = '*';
        }
    }

    for (int j = 0; j < height; ++j) {
        int currentY = y + j;

        if (x >= 0 && x < BOARD_WIDTH && currentY >= 0 && currentY < BOARD_HEIGHT) {
            board[currentY][x] = '*';
        }

        if (rightEdge >= 0 && rightEdge < BOARD_WIDTH && currentY >= 0 && currentY < BOARD_HEIGHT) {
            board[currentY][rightEdge] = '*';
        }
    }
}

std::string Rectangle::getInfo() const {
    std::ostringstream info;
    info << "Rectangle " << x << " " << y << " " << width << " " << height;

    return info.str();
}
