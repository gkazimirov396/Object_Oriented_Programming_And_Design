#include <iostream>
#include <sstream>
#include <memory>
#include <string>

#include "board.h"
#include "square.h"
#include "line.h"
#include "rectangle.h"
#include "triangle.h"

int main() {
    Board board;
    std::string command;
    std::shared_ptr<Figure> selectedShape = nullptr;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "draw") {
            board.printBoard();
        }
        else if (command == "list") {
            board.listShapes();
        }
        else if (command == "shapes") {
            board.printAvailableShapes();
        }
        else if (command == "add") {
            std::string fillModeStr, color, shapeType;

            std::cin >> fillModeStr >> color >> shapeType;
            FillMode fillMode = (fillModeStr == "fill") ? FillMode::Fill : FillMode::Frame;

            if (shapeType == "square") {
                int x, y, width;
                std::cin >> x >> y >> width;

                if (width > 0) {
                    board.addShape(std::make_shared<Square>(x, y, width, color, fillMode));
                }
                else {
                    std::cout << "Width must be positive." << std::endl;
                }
            }
            else if (shapeType == "rectangle") {
                int x, y, width, height;
                std::cin >> x >> y >> width >> height;

                if (width > 0 && height > 0) {
                    board.addShape(std::make_shared<Rectangle>(x, y, width, height, color, fillMode));
                }
                else {
                    std::cout << "Width and height must be positive." << std::endl;
                }
            }
            else if (shapeType == "triangle") {
                int x, y, height;
                std::cin >> x >> y >> height;

                if (height > 0) {
                    board.addShape(std::make_shared<Triangle>(x, y, height, color, fillMode));
                }
                else {
                    std::cout << "Height must be positive." << std::endl;
                }
            }
            else if (shapeType == "line") {
                int x1, y1, x2, y2;
                std::cin >> x1 >> y1 >> x2 >> y2;

                board.addShape(std::make_shared<Line>(x1, y1, x2, y2, color));
            }
        }
        else if (command == "select") {
            std::string option;
            std::cin >> option;

            if (selectedShape) {
                std::cout << "Error: Shape already selected.\n";
                continue;
            }

            if (option == "id") {
                std::string id;
                std::cin >> id;

                selectedShape = board.selectShapeById(id);
            }
            else if (option == "coords") {
                int x, y;
                std::cin >> x >> y;

                selectedShape = board.selectShapeByCoordinates(x, y);
            }
            else {
                std::cout << "Unknown option, expected 'id', or 'coords'";
            }
        }
        else if (command == "paint") {
            std::string color;
            std::cin >> color;

            if (selectedShape) {
                board.paintShape(selectedShape, color);
            }
            else {
                std::cout << "Error: No shape selected.\n";
            }
        }
        else if (command == "move") {
            int x, y;
            std::cin >> x >> y;

            if (auto line = std::dynamic_pointer_cast<Line>(selectedShape)) {
                int x2, y2;
                std::cin >> x2 >> y2;

                line->moveLine(x, x2, y, y2);
            }
            else if (selectedShape) {
                board.moveShape(selectedShape, x, y);
            }
            else {
                std::cout << "Error: No shape selected.\n";
            }
        }
        else if (command == "remove") {
            if (selectedShape) {
                board.removeShape(selectedShape);
                selectedShape = nullptr;
            }
            else {
                std::cout << "Error: No shape selected.\n";
            }
        }
        else if (command == "edit") {
            std::string input;

            std::getline(std::cin, input);
            std::istringstream iss(input);

            if (selectedShape) {
                std::vector<int> params;
                int param;

                while (iss >> param) {
                    params.push_back(param);
                }

                if (!board.editShape(selectedShape, params)) {
                    std::cout << "Error: Invalid parameters or shape out of bounds.\n";
                }
            }
            else {
                std::cout << "Error: No shape selected.\n";
            }
        }
        else if (command == "save") {
            std::string filename;
            std::cin >> filename;

            board.saveToFile(filename);
        }
        else if (command == "load") {
            std::string filename;
            std::cin >> filename;

            board.loadFromFile(filename);
        }
        else if (command == "cancel") {
            std::cout << "Unselected: " << selectedShape->getInfo();

            selectedShape = nullptr;
        }
        else if (command == "undo") {
            board.removeLastShape();
        }
        else if (command == "clear") {
            board.clearBoard();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }

    return 0;
}