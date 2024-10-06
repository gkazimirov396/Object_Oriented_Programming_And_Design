#pragma once

#include <vector>
#include <memory>
#include <string>

#include "shape.h"

class Board {
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::vector<char>> grid;

public:
    Board();

    void addShape(std::shared_ptr<Shape> shape);
    void printBoard();
    void listShapes() const;
    void clearBoard();
    void printAvailableShapes() const;
    void removeLastShape();
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};
