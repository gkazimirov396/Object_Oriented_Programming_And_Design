#include <iostream>

#include "board.h"

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
