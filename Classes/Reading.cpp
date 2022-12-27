#include "Airport.h"
#include "Flight.h"
#include "Reading.h"
#include "Airline.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "Graph.h"

void Reading::readAirlines() {
    int verify = 0;
    vector<Airline> airlines;
    string AIRLINE_CODE, AIRLINE_NAME, CALLSIGN, AIRLINE_COUNTRY;

    ifstream in("../airlines.csv");
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss, AIRLINE_CODE, ',');
        getline(iss,AIRLINE_NAME, ',');
        getline(iss, CALLSIGN, ',');
        getline(iss, AIRLINE_COUNTRY, ',');

        Airline airline1 = Airline(AIRLINE_CODE, AIRLINE_NAME, CALLSIGN, AIRLINE_COUNTRY);
        airlineTable.insert(airline1);
    }
}

void Reading::readAirports(){
        int verify = 0;
        int count = 1;
        string AIRPORT_CODE, AIRPORT_NAME, CITY, AIRPORT_COUNTRY;
        float LATITUDE, LONGITUDE;
        char c;
        ifstream in("../airports.csv");
        if (!in.is_open()) exit(EXIT_FAILURE);

        for (string line; getline(in, line);) {
            istringstream iss(line);
            if (verify == 0) {
                verify++;
                continue;
            }
            getline(iss, AIRPORT_CODE, ',');
            getline(iss,AIRPORT_NAME, ',');
            getline(iss, CITY, ',');
            getline(iss, AIRPORT_COUNTRY, ',');
            iss >> LATITUDE >> c;
            iss >> LONGITUDE >> c;

            Airport airport1 = Airport(AIRPORT_CODE, AIRPORT_NAME, CITY, AIRPORT_COUNTRY,LATITUDE, LONGITUDE, count);
            airportTable.insert(airport1);
            count++;
        }

}


Graph Reading::readFlights(){
    int verify = 0;
    vector<Flight> flights;
    string SOURCE, TARGET,AIRLINE;
    ifstream in("../flights.csv");
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify == 0) {
            verify++;
            continue;
        }
        getline(iss, SOURCE, ',');
        getline(iss,TARGET, ',');
        getline(iss, AIRLINE, ',');

        Flight flight1 = Flight(SOURCE, TARGET, AIRLINE );
        flights.push_back(flight1);
    }
    Graph voos((int)airportTable.size(),true);
    for(auto flight: flights){
        Airport aux = Airport(flight.getFlightsource());
        std::unordered_set<Airport>::const_iterator itr = this->airportTable.find(aux);
        int pos =  itr->getNumCode();
        voos.addEdge(flight.getFlightsource(),flight.getFlighttarget(),flight.getFlightairline(), pos-1);

    }

    return voos;
}
