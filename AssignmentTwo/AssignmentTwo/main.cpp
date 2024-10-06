#include <iostream>
#include <memory>
#include <string>

#include "board.h"
#include "square.h"
#include "triangle.h"

int main() {
    Board board;
    std::string command;

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
            std::string shapeType;
            std::cin >> shapeType;

            if (shapeType == "circle") {
                int x, y, radius;
                std::cin >> x >> y >> radius;

                // TODO
            }
            else if (shapeType == "square") {
                int x, y, width;
                std::cin >> x >> y >> width;
                
                board.addShape(std::make_shared<Square>(x, y, width));
            }
            else if (shapeType == "triangle") {
                int x, y, height;
                std::cin >> x >> y >> height;

                board.addShape(std::make_shared<Triangle>(x, y, height));
            }
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
