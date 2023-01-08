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
#include "Graph.h"

class Reading {
    public:
        ///@brief Reads airlines.csv, airports.csv, flights.csv
        ///@note Store Airports, Airlines in an unordered_set and build a graph with nodes representing airports and edges the flights.
        ///@note Instead of having for example 5 edges between node A - B (5 edges represent 5 airlines in this case) we have just 1 edge
        ///@note and each edge has a list with all the airlines that link those nodes
        ///@returns A graph with the nodes being airports and the edges flights
        ///@note Time complexity: O(n)
        static Graph readAllFiles();
};

#endif
