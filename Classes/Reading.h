#ifndef AED_2_READING_H
#define AED_2_READING_H
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"

#include <vector>

class Reading {
    public:
    static vector<Airport> readAirports();
    static vector<Airline> readAirLines();
    static vector<Flight> readFlights();

};


#endif //AED_2_READING_H
