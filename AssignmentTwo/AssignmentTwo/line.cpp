#include <sstream>
#include <cmath>

#include "line.h"

Line::Line(int x1, int y1, int x2, int y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

void Line::draw(std::vector<std::vector<char>>& board) {
    const int BOARD_HEIGHT = board.size();
    const int BOARD_WIDTH = board[0].size();

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
            board[roundedY][roundedX] = '*';
        }

        x += xIncrement;
        y += yIncrement;
    }
}

std::string Line::getInfo() const {
    std::ostringstream info;
    info << "Line " << x1 << " " << y1 << " " << x2 << " " << y2;

    return info.str();
}
