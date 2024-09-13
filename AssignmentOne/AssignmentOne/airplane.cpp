#include <iostream>

#include "airplane.h"

Airplane::Airplane(const std::string& flightNumber, const std::string& date, int seatsPerRow, const std::vector<std::pair<std::string, std::string>>& pricing)
    : flightNumber(flightNumber), date(date), seatsPerRow(seatsPerRow), pricing(pricing) {

    for (const auto& range : pricing) {
        std::string rowRange = range.first;
        size_t dashPos = rowRange.find('-');

        if (dashPos != std::string::npos) {
            int endRow = std::stoi(rowRange.substr(dashPos + 1));
            rows = std::max(rows, endRow);
        }
    }

    seatAvailability = std::vector<std::vector<bool>>(rows, std::vector<bool>(seatsPerRow, false));
}

std::string Airplane::getPriceForRow(int row) const {
    for (const auto& range : pricing) {
        std::string rowRange = range.first;
        size_t dashPos = rowRange.find('-');

        if (dashPos != std::string::npos) {
            int startRow = std::stoi(rowRange.substr(0, dashPos));
            int endRow = std::stoi(rowRange.substr(dashPos + 1));

            if (row >= startRow && row <= endRow) {
                return range.second;
            }
        }
    }
    return "Unknown";
}

bool Airplane::isSeatAvailable(int row, int seat) const {
    row -= 1; 
    seat -= 1;

    if (row < 0 || row >= rows || seat < 0 || seat >= seatsPerRow) {
        std::cerr << "Error: Invalid seat number!" << std::endl;
        return false;
    }

    return !seatAvailability[row][seat];
}

bool Airplane::bookSeat(int row, int seat, const std::string& passengerName) {
    row -= 1; 
    seat -= 1;

    if (isSeatAvailable(row + 1, seat + 1)) {
        seatAvailability[row][seat] = true;

        Ticket newTicket(passengerName, flightNumber, date, row + 1, seat + 1);
        bookedTickets.push_back(newTicket);

        std::cout << "Booking confirmed for " << passengerName << " with Ticket ID: " << newTicket.getID() << std::endl;
        return true;
    }

    std::cerr << "Seat not available!" << std::endl;
    return false;
}

bool Airplane::returnSeat(int row, int seat) {
    row -= 1; 
    seat -= 1;

    if (row >= 0 && row < rows && seat >= 0 && seat < seatsPerRow && seatAvailability[row][seat]) {
        seatAvailability[row][seat] = false;

        for (auto& ticket : bookedTickets) {
            if (ticket.getRow() == row + 1 && ticket.getSeat() == seat + 1 && ticket.getBookingStatus()) {
                ticket.setBookingStatus(false);
                std::cout << "Ticket returned successfully!" << std::endl;

                return true;
            }
        }

        return true;
    }

    std::cerr << "Seat not found or not booked!" << std::endl;

    return false;
}

void Airplane::displayAvailableSeats() const {
    std::cout << "Available seats for flight " << flightNumber << " on " << date << ":" << std::endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < seatsPerRow; ++j) {
            std::string seatDisplay = seatAvailability[i][j] ? "X" : "O";
            std::cout << seatDisplay << " ";
        }

        std::cout << "(Price: " << getPriceForRow(i + 1) << ")" << std::endl;
    }
}

void Airplane::viewTickets() const {
    std::cout << "Booked tickets for flight " << flightNumber << " on " << date << ":" << std::endl;

    for (const auto& ticket : bookedTickets) {
        if (ticket.getBookingStatus()) {
            std::cout << "Passenger: " << ticket.getPassengerName()
                << ", Seat: Row " << ticket.getRow() << ", Seat " << ticket.getSeat()
                << ", Ticket ID: " << ticket.getID() << std::endl;
        }
    }
}

std::string Airplane::getFlightNumber() const {
    return flightNumber;
}

std::string Airplane::getDate() const {
    return date;
}
