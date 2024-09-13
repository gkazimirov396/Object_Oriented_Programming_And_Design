#pragma once

#include <string>
#include <vector>

#include "ticket.h"

class Airplane {
private:
    std::string date;
    std::string flightNumber;
    std::string getPriceForRow(int row) const;

    int rows;
    int seatsPerRow;
    //Ticket nextTicket;

    std::vector<Ticket> bookedTickets;
    std::vector<std::vector<bool>> seatAvailability;
    std::vector<std::pair<std::string, std::string>> pricing;

public:
    Airplane(const std::string& flightNumber, const std::string& date, int seatsPerRow, const std::vector<std::pair<std::string, std::string>>& pricing);

    bool isSeatAvailable(int row, int seat) const;
    bool bookSeat(int row, int seat, const std::string& passengerName);
    bool returnSeat(int row, int seat);

    void displayAvailableSeats() const;
    void viewTickets() const;

    std::string getFlightNumber() const;
    std::string getDate() const;
};