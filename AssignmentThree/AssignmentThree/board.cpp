#include <iostream>
#include <fstream>

#include "board.h"
#include "square.h"
#include "line.h"
#include "rectangle.h"

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

Board::Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

std::shared_ptr<Figure> Board::selectShapeByCoordinates(int x, int y) {
    for (const auto& shape : shapes) {
        if (auto square = std::dynamic_pointer_cast<Square>(shape)) {
            if ((x >= square->x && x < square->x + square->width && y >= square->y && y < square->y + square->width)) {
                std::cout << "Selected: " << square->getInfo() << std::endl;

                return square;
            }
        }
        else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(shape)) {
            if ((x >= rectangle->x && x < rectangle->x + rectangle->width &&
                y >= rectangle->y && y < rectangle->y + rectangle->height)) {
                std::cout << "Selected: " << rectangle->getInfo() << std::endl;

                return rectangle;
            }
        }
    }

    std::cout << "Error: No shape found at coordinates (" << x << ", " << y << ").\n";

    return nullptr;
}

std::shared_ptr<Figure> Board::selectShapeById(std::string& id) {
    auto it = std::find_if(shapes.begin(), shapes.end(),
        [&id](const std::shared_ptr<Figure>& shape) {
            return shape->getID() == id;
        });

    if (it != shapes.end()) {
        std::shared_ptr<Figure> selected = *it;
        std::cout << "Selected: " << selected->getInfo() << std::endl;

        return selected;
    }

    std::cout << "Error: No shape found with ID " << id << ".\n";

    return nullptr;
}

void Board::clearBoard() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), ' ');
    }

    shapes.clear();
}

void Board::printBoard() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), ' ');
    }

    for (const auto& shape : shapes) {
        shape->draw(grid);
    }

    for (auto& row : grid) {
        for (char c : row) {
            std::cout << c;
        }

        std::cout << "\n";
    }
}

void Board::listShapes() const {
    if (shapes.empty()) {
        std::cout << "No shapes on the board.\n";
        return;
    }

    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << i + 1 << ": " << shapes[i]->getInfo() << std::endl;
    }
}

void Board::addShape(std::shared_ptr<Figure> shape) {
    shapes.push_back(shape);
}

void Board::removeLastShape() {
    if (!shapes.empty()) {
        shapes.pop_back();
    }
}

void Board::removeShape(std::shared_ptr<Figure> shape) {
    shapes.erase(std::remove(shapes.begin(), shapes.end(), shape), shapes.end());
}

bool Board::editShape(std::shared_ptr<Figure> shape, const std::vector<int>& params) {
    if (auto square = std::dynamic_pointer_cast<Square>(shape)) {
        if (params.size() == 1) {
            square->edit(params, grid);

            return true;
        }
    }
    else if (auto rectangle = std::dynamic_pointer_cast<Rectangle>(shape)) {
        if (params.size() == 2) {
            rectangle->edit(params, grid);

            return true;
        }
    }

    std::cout << "Error: Invalid parameters for this shape.\n";

    return false;
}

void Board::paintShape(std::shared_ptr<Figure> shape, const std::string& color) {
    shape->paint(color);
}

void Board::moveShape(std::shared_ptr<Figure> shape, int x, int y) {
    shape->move(x, y);
}

void Board::printAvailableShapes() const {
    std::cout << "Available shapes and their parameters:\n";
    std::cout << "1. square: x y width\n";
    std::cout << "   - x: X coordinate of the top-left corner\n";
    std::cout << "   - y: Y coordinate of the top-left corner\n";
    std::cout << "   - width: The width of the square\n\n";

    std::cout << "2. triangle: x y height\n";
    std::cout << "   - x: X coordinate of the apex\n";
    std::cout << "   - y: Y coordinate of the apex\n";
    std::cout << "   - height: The height of the triangle\n\n";

    std::cout << "3. rectangle: x y width height\n";
    std::cout << "   - x: X coordinate of the top-left corner\n";
    std::cout << "   - y: Y coordinate of the top-left corner\n";
    std::cout << "   - width: The width of the rectangle\n";
    std::cout << "   - height: The height of the rectangle\n";

    std::cout << "4. line: x1 y1 x2 y2\n";
    std::cout << "   - x1: X coordinate of the starting point\n";
    std::cout << "   - y1: Y coordinate of the starting point\n";
    std::cout << "   - x2: X coordinate of the ending point\n";
    std::cout << "   - y2: Y coordinate of the ending point\n";
}

bool Board::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Could not open file for writing: " << filename << std::endl;

        return false;
    }

    outFile << BOARD_WIDTH << " " << BOARD_HEIGHT << "\n";

    for (const auto& shape : shapes) {
        std::string info = shape->getInfo();
        outFile << info << "\n";
    }

    outFile.close();
    std::cout << "Board saved to " << filename << std::endl;

    return true;
}

bool Board::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file for reading: " << filename << std::endl;

        return false;
    }

    clearBoard();

    int width, height;
    inFile >> width >> height;

    if (width != BOARD_WIDTH || height != BOARD_HEIGHT) {
        std::cerr << "Invalid board dimensions in file: " << filename << std::endl;

        return false;
    }

    std::string shapeType, ID;

    while (inFile >> ID >> shapeType) {
        if (shapeType == "Square") {
            int x, y, width;
            std::string color, fillModeStr;

            inFile >> x >> y >> width >> color >> fillModeStr;
            FillMode fillMode = (fillModeStr == "Fill" ? FillMode::Fill : FillMode::Frame);

            if (inFile.fail() || width <= 0) {
                std::cerr << "Invalid shape data for square." << std::endl;

                return false;
            }

            addShape(std::make_shared<Square>(x, y, width, color, fillMode));
        }
        else if (shapeType == "Line") {
            int x1, y1, x2, y2;
            std::string color;

            inFile >> x1 >> y1 >> x2 >> y2 >> color;

            if (inFile.fail()) {
                std::cerr << "Invalid shape data for line." << std::endl;

                return false;
            }

            addShape(std::make_shared<Line>(x1, y1, x2, y2, color));
        }
        else if (shapeType == "Rectangle") {
            int x, y, width, height;
            std::string color, fillModeStr;

            inFile >> x >> y >> width >> height >> color >> fillModeStr;
            FillMode fillMode = (fillModeStr == "Fill" ? FillMode::Fill : FillMode::Frame);

            if (inFile.fail() || width <= 0 || height <= 0) {
                std::cerr << "Invalid shape data for rectangle." << std::endl;

                return false;
            }

            addShape(std::make_shared<Rectangle>(x, y, width, height, color, fillMode));
        }
        else {
            std::cerr << "Unknown shape type in file: " << shapeType << std::endl;

            return false;
        }
    }

    inFile.close();
    std::cout << "Board loaded from " << filename << std::endl;

    return true;
}