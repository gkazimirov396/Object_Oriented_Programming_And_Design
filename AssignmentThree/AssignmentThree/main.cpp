#include <iostream>
#include <memory>
#include <string>

#include "board.h"
#include "square.h"

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
        }
        else if (command == "select") {
            std::string option;
            std::cin >> option;

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

            if (selectedShape) {
                board.moveShape(selectedShape, x, y);
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