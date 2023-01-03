#include "Airport.h"
#include "Flight.h"
#include "Reading.h"
#include "Airline.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Graph.h"

Graph Reading::readAllFiles(){
    Graph aux(0,true);

    int verify1 = 0;
    vector<Airline> airlines;
    string AIRLINE_CODE, AIRLINE_NAME, CALLSIGN, AIRLINE_COUNTRY;

    ifstream in("../airlines.csv");
    if (!in.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in, line);) {
        istringstream iss(line);
        if (verify1 == 0) {
            verify1++;
            continue;
        }
        getline(iss, AIRLINE_CODE, ',');
        getline(iss,AIRLINE_NAME, ',');
        getline(iss, CALLSIGN, ',');
        getline(iss, AIRLINE_COUNTRY, ',');

        Airline airline1 = Airline(AIRLINE_CODE, AIRLINE_NAME, CALLSIGN, AIRLINE_COUNTRY);
        aux.insertAirline_intotable(airline1);
    }

    int verify2 = 0, count = 1;
    string AIRPORT_CODE, AIRPORT_NAME, CITY, AIRPORT_COUNTRY;
    float LATITUDE, LONGITUDE;
    char c;
    ifstream in2("../airports.csv");
    if (!in2.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in2, line);) {
        istringstream iss(line);
        if (verify2 == 0) {
            verify2++;
            continue;
        }
        getline(iss, AIRPORT_CODE, ',');
        getline(iss,AIRPORT_NAME, ',');
        getline(iss, CITY, ',');
        getline(iss, AIRPORT_COUNTRY, ',');
        iss >> LATITUDE >> c;
        iss >> LONGITUDE >> c;

        Airport airport1 = Airport(AIRPORT_CODE, AIRPORT_NAME, CITY, AIRPORT_COUNTRY,LATITUDE, LONGITUDE, count);
        aux.insertAirport_intotable(airport1);
        count++;
    }

    int verify3 = 0;
    vector<Flight> flights;
    string SOURCE, TARGET,AIRLINE;
    ifstream in3("../flights.csv");
    if (!in3.is_open()) exit(EXIT_FAILURE);

    for (string line; getline(in3, line);) {
        istringstream iss(line);
        if (verify3 == 0) {
            verify3++;
            continue;
        }
        getline(iss, SOURCE, ',');
        getline(iss,TARGET, ',');
        getline(iss, AIRLINE, ',');

        Flight flight1 = Flight(SOURCE, TARGET, AIRLINE );
        flights.push_back(flight1);
    }

    int size_aux = aux.get_airportTable_size();
    Graph voos((int)size_aux-1,true);
    voos.set_airportTable(aux.airportTable);
    voos.set_airlineTable(aux.airlineTable);

    for(auto flight: flights){
        Airport aux1 = Airport(flight.getFlightsource());
        std::unordered_set<Airport>::const_iterator itr = voos.airportTable.find(aux1);
        int pos =  itr->getNumCode();
        voos.addEdge(flight.getFlightsource(),flight.getFlighttarget(),flight.getFlightairline(), pos-1);
    }
    return voos;
}
