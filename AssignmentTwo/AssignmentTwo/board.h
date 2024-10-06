#pragma once

#include <vector>
#include <memory>
#include <string>

#include "figure.h"

class Board {
    std::vector<std::shared_ptr<Figure>> shapes;
    std::vector<std::vector<char>> grid;

public:
    Board();

    void addShape(std::shared_ptr<Figure> shape);
    void printBoard();
    void listShapes() const;
    void clearBoard();
    void printAvailableShapes() const;
    void removeLastShape();
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};
