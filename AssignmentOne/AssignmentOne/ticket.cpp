#include <functional> 
#include <string>       
#include <sstream>

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

std::string Ticket::getID() const {
    std::hash<std::string> hashFunction;

    std::stringstream ss;
    ss << passengerName << flightNumber << row << seat;

    return std::to_string(hashFunction(ss.str()));
}

bool Ticket::getBookingStatus() const {
    return isBooked;
}

void Ticket::setBookingStatus(bool status) {
    isBooked = status;
}