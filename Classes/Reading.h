#ifndef AED_2_READING_H
#define AED_2_READING_H
#include "Airline.h"
#include "Airport.h"
#include "Flight.h"
#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include "HashTable.h"

struct AirportHash {
    std::size_t operator()(const Airport& airport) const {
        std::size_t h = 0;
        h = 37 * h + std::hash<std::string>()(airport.getAirportcode());
        h = 37 * h + std::hash<std::string>()(airport.getAirportname());
        h = 37 * h + std::hash<std::string>()(airport.getAirportcity());
        h = 37 * h + std::hash<std::string>()(airport.getAirportcountry());
        h = 37 * h + std::hash<float>()(airport.getAirportlatitude());
        h = 37 * h + std::hash<float>()(airport.getAirportlongitude());
        return h;
    }
};

struct AirlineHash{
    std::size_t operator()(const Airline& airline) const {
        std::size_t h = 0;
        h = 37 * h + std::hash<std::string>()(airline.getAirlinename());
        h = 37 * h + std::hash<std::string>()(airline.getAirlinecode());
        h = 37 * h + std::hash<std::string>()(airline.getAirlinecountry());
        h = 37 * h + std::hash<std::string>()(airline.getAirlinecallsign());
        return h;
    }
};

struct AirportEqual {
    bool operator()(const Airport& airport1, const Airport& airport2) const {
        return airport1 == airport2;
    }
};

struct AirlineEqual{
    bool operator()(const Airline& airline1, const Airline& airline2) const {
        return airline1 == airline2;
    }
};

class Reading {
private:

public:
    void printAIRPORTtablesize(){
        cout << "AIRPORTtable size: " << airportTable.size() << endl;
    }

    void printAIRLINEtablesize(){
        cout << "AIRLINEtable size: " << airlineTable.size() << endl;
    }
    std::unordered_set<Airport, AirportHash, AirportEqual> airportTable;
    std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable;
    void readAirports();
    void readAirlines();
};

#endif
