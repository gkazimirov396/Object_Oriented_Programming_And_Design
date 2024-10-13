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

    std::shared_ptr<Figure> selectShapeById(std::string& id);
    std::shared_ptr<Figure> selectShapeByCoordinates(int x, int y);

    void removeShape(std::shared_ptr<Figure> shape);
    void paintShape(std::shared_ptr<Figure> shape, const std::string& color);
    bool editShape(std::shared_ptr<Figure> shape, const std::vector<int>& params);
    void moveShape(std::shared_ptr<Figure> shape, int x, int y);

    void addShape(std::shared_ptr<Figure> shape);
    void printBoard();
    void listShapes() const;
    void clearBoard();
    void printAvailableShapes() const;
    void removeLastShape();
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};