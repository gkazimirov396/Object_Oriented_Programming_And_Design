#include <iostream>
#include <memory>
#include <string>

#include "board.h"

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
                
                // TODO
            }
            else if (shapeType == "triangle") {
                int x, y, height;
                std::cin >> x >> y >> height;

                // TODO
            }
        }
        else if (command == "undo") {
            // TODO
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
