#include <sstream>

#include "square.h"

Square::Square(int x, int y, int width) : x(x), y(y), width(width) {}

void Square::draw(std::vector<std::vector<char>>& board) {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    if (x + width < 0 || x >= BOARD_WIDTH || y + width < 0 || y >= BOARD_HEIGHT) {
        return;
    }

    for (int i = 0; i < width; ++i) {
        if (y >= 0 && y < BOARD_HEIGHT && (x + i) >= 0 && (x + i) < BOARD_WIDTH) {
            board[y][x + i] = '*';
        }
        if ((y + width - 1) >= 0 && (y + width - 1) < BOARD_HEIGHT && (x + i) >= 0 && (x + i) < BOARD_WIDTH) {
            board[y + width - 1][x + i] = '*';
        }

        if (x >= 0 && x < BOARD_WIDTH && (y + i) >= 0 && (y + i) < BOARD_HEIGHT) {
            board[y + i][x] = '*';
        }
        if ((x + width - 1) >= 0 && (x + width - 1) < BOARD_WIDTH && (y + i) >= 0 && (y + i) < BOARD_HEIGHT) {
            board[y + i][x + width - 1] = '*';
        }
    }
}

std::string Square::getInfo() const {
    std::ostringstream info;
    info << "Square " << x << " " << y << " " << width;

    return info.str();
}