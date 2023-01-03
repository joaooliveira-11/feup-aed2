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
        int dist;

    };
    struct AirportHash {
        std::size_t operator()(const Airport& airport) const {
            vector<char> chars;
            for(auto c : airport.getAirportcode()){
                chars.push_back(c);
            }
            char first = chars[0], second = chars[1], third = chars[2];
            return first + second*'A' + third*'A'*'A';
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
    vector<Node> nodes; // The list of nodes being representedq

    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void addEdge(string src, const string& dest, const string& company, int pos);

    void verNodes();

    void insertAirport_intotable(const Airport& airport);

    void insertAirline_intotable(const Airline& airline);

    void set_airportTable(unordered_set<Airport, AirportHash, AirportEqual> airportTable1);

    void set_airlineTable(std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable1);

    int get_airportTable_size() const;

    int get_airlineTable_size() const;

    void setFalse();

    void resetDist();

    void bfs(int v);

    list<list<string>> distTwoAiports_bfs(const string& v, const string& d);

    int bfs_max_distance(int a);

    int distTwoAirports(const string& airpA,const string& airpB);

    int distTwoAirportsAirlineRest(const string& airpA,const string& airpB, const list<string>& airlines );

    list<list<string>> distTwoAiportsWithRest_bfs(const string& v, const string& d, const list<string>& airlines);

    int countReachableAirports(string startAirport, int maxFlights);

    int countReachableCities(string startAirport, int maxFlights);

    int countReachableCountries(string startAirport, int maxFlights);

    vector<Node> get_nodes() const;

    std::unordered_set<Airport, AirportHash, AirportEqual> airportTable;
    std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable;
};

#endif
