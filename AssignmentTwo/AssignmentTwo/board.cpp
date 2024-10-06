#include <iostream>
#include <fstream>

#include "board.h"
#include "square.h"
#include "triangle.h"
#include "rectangle.h"

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

Board::Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

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

void Board::addShape(std::shared_ptr<Shape> shape) {
	shapes.push_back(shape);
}

void Board::removeLastShape() {
	if (!shapes.empty()) {
		shapes.pop_back();
	}
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

    std::string shapeType;

    while (inFile >> shapeType) {
        if (shapeType == "Square") {
            int x, y, width;
            inFile >> x >> y >> width;

            if (inFile.fail() || width <= 0) {
                std::cerr << "Invalid shape data for square." << std::endl;

                return false;
            }

            addShape(std::make_shared<Square>(x, y, width));
        }
        else if (shapeType == "Triangle") {
            int x, y, height;
            inFile >> x >> y >> height;

            if (inFile.fail() || height <= 0) {
                std::cerr << "Invalid shape data for triangle." << std::endl;

                return false;
            }

            addShape(std::make_shared<Triangle>(x, y, height));
        }
        else if (shapeType == "Rectangle") {
            int x, y, width, height;
            inFile >> x >> y >> width >> height;

            if (inFile.fail() || width <= 0 || height <= 0) {
                std::cerr << "Invalid shape data for rectangle." << std::endl;

                return false;
            }

            addShape(std::make_shared<Rectangle>(x, y, width, height));
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