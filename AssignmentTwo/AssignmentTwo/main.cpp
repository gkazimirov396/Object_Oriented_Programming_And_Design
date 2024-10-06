#include <iostream>
#include <memory>
#include <string>

#include "board.h"
#include "square.h"
#include "triangle.h"
#include "rectangle.h"
#include "line.h"

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

            if (shapeType == "rectangle") {
                int x, y, width, height;
                std::cin >> x >> y >> width >> height;

                if (width > 0 && height > 0) {
                    board.addShape(std::make_shared<Rectangle>(x, y, width, height));
                }
                else {
                    std::cout << "Radius must be positive." << std::endl;
                }
            }
            else if (shapeType == "square") {
                int x, y, width;
                std::cin >> x >> y >> width;
                
                if (width > 0) {
                    board.addShape(std::make_shared<Square>(x, y, width));
                }
                else {
                    std::cout << "Width must be positive." << std::endl;
                }
            }
            else if (shapeType == "triangle") {
                int x, y, height;
                std::cin >> x >> y >> height;

                if (height > 0) {
                    board.addShape(std::make_shared<Triangle>(x, y, height));
                }
                else {
                    std::cout << "Height must be positive." << std::endl;
                }
            }
            else if (shapeType == "line") {
                int x1, y1, x2, y2;
                std::cin >> x1 >> y1 >> x2 >> y2;

                board.addShape(std::make_shared<Line>(x1, y1, x2, y2));
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
