#pragma once

#include <string>

class Ticket {
private:
    unsigned long ID;

    std::string passengerName;
    std::string flightNumber;
    std::string date;

    int row;
    int seat;

    bool isBooked;

public:
    Ticket(const std::string& passengerName, const std::string& flightNumber, const std::string& date, int row, int seat);

    int getRow() const;
    int getSeat() const;
    unsigned long getID() const;

    std::string getDate() const;
    bool getBookingStatus() const;
    std::string getFlightNumber() const;
    std::string getPassengerName() const;

    void setBookingStatus(bool status);
};