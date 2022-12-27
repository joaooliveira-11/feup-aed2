#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <iostream>
#include <stack>
#include <unordered_set>
#include "Airport.h"
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Graph {
    struct Edge {
        string dest;
        list<string> company;
    };

    struct Node {
        string src;
        list<Edge> adj;
        bool visited;   // As the node been visited on a search?

    };
    struct AirportHash {
        std::size_t operator()(const Airport& airport) const {
            /*
            std::size_t h = 0;
            h = 37 * h + std::hash<std::string>()(airport.getAirportcode());
    */
            int v = 0;
            vector<char> chars;

            for(auto c : airport.getAirportcode()){
                chars.push_back(c);
            }
            char first = chars[0];
            char second = chars[1];
            char third = chars[2];
            v = first + second*'A' + third*'A'*'A';
            return v;
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

    int n;
    bool hasDir;        // false: undirected; true: directed

public:
    vector<Node> nodes; // The list of nodes being represented

    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, string dest, string company, int pos);

    void verNodes();

    void insertAirport_intotable(Airport airport);

    void insertAirline_intotable(Airline airline);

    void set_airportTable(unordered_set<Airport, AirportHash, AirportEqual> airportTable1);

    void set_airlineTable(std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable1);

    int get_airportTable_size();

    int get_airlineTable_size();

    vector<Node> get_nodes();

    std::unordered_set<Airport, AirportHash, AirportEqual> airportTable;
    std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable;
};

#endif
