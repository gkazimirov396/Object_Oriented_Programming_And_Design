#include <iostream>

#include "board.h"

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

Board::Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

void Board::clearBoard() {
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			grid[i][j] = ' ';
		}
	}

	shapes.clear();
}

void Board::printBoard() {
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
	for (size_t i = 0; i < shapes.size(); ++i) {
		std::cout << i + 1 << ": " << shapes[i]->getInfo() << std::endl;
	}
}

void Board::addShape(std::shared_ptr<Shape> shape) {
	shapes.push_back(shape);
}