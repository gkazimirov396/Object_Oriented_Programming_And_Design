#include <iostream>
#include <vector>

#include "airplane.h"
#include "file-parser.h"

int main() {
    std::vector<Airplane> airplanes = FileParser::readFile("/Users/User/source/repos/object-oriented-programming-and-design/homework/AssignmentOne/AssignmentOne/config.txt");

    std::string command;

    while (true) {
        std::cout << "> ";
        std::cin >> command;

        if (command == "check") {
            std::string date, flightNumber;
            std::cin >> date >> flightNumber;

            for (const auto& airplane : airplanes) {
                if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                    airplane.displayAvailableSeats();
                }
            }
        }
        else if (command == "book") {
            int row, seat;
            std::string date, flightNumber, passengerName;

            std::cin >> date >> flightNumber >> row >> seat >> passengerName;

            for (auto& airplane : airplanes) {
                if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                    airplane.bookSeat(row, seat, passengerName);
                }
            }
        }
        else if (command == "return") {
            std::string date, flightNumber;
            int row, seat;
            std::cin >> date >> flightNumber >> row >> seat;

            for (auto& airplane : airplanes) {
                if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                    airplane.returnSeat(row, seat);
                }
            }
        }
        else if (command == "view") {
            std::string param;

            std::cin >> param;

            if (param == "username") {
                std::string username;
                std::cin >> username;

                for (const auto& airplane : airplanes) {
                    airplane.viewTicketsByUsername(username);
                }

            }
            else if (param == "flight") {
                std::string flightNumber, date;
                std::cin >> flightNumber >> date;

                for (const auto& airplane : airplanes) {
                    if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                        airplane.viewTickets();
                    }
                }
            }
            else {
                std::cout << "Unknown view option!" << std::endl;
            }

        }
        else if (command == "e") {
            break;
        }
        else {
            std::cout << "Unknown command!" << std::endl;
        }
    }

    return 0;
}