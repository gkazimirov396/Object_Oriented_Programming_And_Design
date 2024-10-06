#include <string>
#include <sstream>

#include "triangle.h"

Triangle::Triangle(int x, int y, int height) : x(x), y(y), height(height) {}

void Triangle::draw(std::vector<std::vector<char>>& board) {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

    if (x + height < 0 || x - height >= BOARD_WIDTH || y + height < 0 || y >= BOARD_HEIGHT || height <= 0) {
        return;
    }

    for (int i = 0; i < height; ++i) {
        int leftMost = x - i;
        int rightMost = x + i; 
        int posY = y + i; 

        if (posY >= BOARD_HEIGHT) break;

        if (posY < BOARD_HEIGHT) {
            if (leftMost >= 0 && leftMost < BOARD_WIDTH)
                board[posY][leftMost] = '*';
            if (rightMost >= 0 && rightMost < BOARD_WIDTH && leftMost != rightMost) 
                board[posY][rightMost] = '*';
            
        }
    }

    for (int j = 0; j < 2 * height - 1; ++j) {
        int baseX = x - height + 1 + j;
        int baseY = y + height - 1;

        if (baseX >= 0 && baseX < BOARD_WIDTH && baseY < BOARD_HEIGHT)
            board[baseY][baseX] = '*';
    }
}


std::string Triangle::getInfo() const {
    std::ostringstream info;
    info << "Triangle " << x << " " << y << " " << height;

    return info.str();
}