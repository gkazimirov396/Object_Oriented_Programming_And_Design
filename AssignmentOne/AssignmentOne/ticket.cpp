#include <functional>

#include "ticket.h"

Ticket::Ticket(const std::string& passengerName, const std::string& flightNumber, const std::string& date, int row, int seat)
    : passengerName(passengerName), flightNumber(flightNumber), date(date), row(row), seat(seat), isBooked(true), ID(getID()) {}

std::string Ticket::getPassengerName() const {
    return passengerName;
}

std::string Ticket::getFlightNumber() const {
    return flightNumber;
}

std::string Ticket::getDate() const {
    return date;
}

int Ticket::getRow() const {
    return row;
}

int Ticket::getSeat() const {
    return seat;
}

unsigned long Ticket::getID() const {
    return std::hash<std::string>{}(passengerName + date + flightNumber + std::to_string(row) + std::to_string(seat));
}

bool Ticket::getBookingStatus() const {
    return isBooked;
}

void Ticket::setBookingStatus(bool status) {
    isBooked = status;
}