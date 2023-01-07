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
        int low;
        int num;
    };
    struct AirportHash {
        std::size_t operator()(const Airport& airport) const {
            size_t h = 0;
            /*
            vector<char> chars;
            for(auto c : airport.getAirportcode()){
                chars.push_back(c);
            }
            char first = chars[0], second = chars[1], third = chars[2];
            return first + second*'A' + third*'A'*'A';
             */
            h = 37 * hash<string>()(airport.getAirportcode());
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

    int n;

    bool hasDir;        // false: undirected; true: directed

public:
    ///@brief The vector of nodes being represented.
    vector<Node> nodes;

    ///@brief Constructor: nr nodes and direction (default: undirected)
    ///@param nodes
    ///@param dir
    explicit Graph(int nodes, bool dir = false);

    ///@brief Add edge from source to destination with a certain weight
    ///@param src
    ///@param dest
    ///@param company - list containing all the airlines that execute the link for each edge
    ///@param pos
    void addEdge(string src, const string& dest, const string& company, int pos);

    ///@brief See the all the nodes
    void verNodes();

    ///@brief Insert a new Airport in the airports unordered_set
    ///@param airport
    void insertAirport_intotable(const Airport& airport);

    ///@brief Insert a new Airline in the airlines unordered_set
    ///@param airline
    void insertAirline_intotable(const Airline& airline);

    ///@brief Setter for the airports unordered_set.
    ///@param airportTable1
    void set_airportTable(unordered_set<Airport, AirportHash, AirportEqual> airportTable1);

    ///@brief Setter for the airlines unordered_set.
    ///@param airlineTable1
    void set_airlineTable(std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable1);

    ///@brief Getter for the airports unordered_set size
    ///@returns The size of the airports unordered_set
    int get_airportTable_size() const;

    ///@brief Getter for the airlines unordered_set size
    ///@returns The size of the airlines unordered_set
    int get_airlineTable_size() const;

    ///@brief Setter to set all nodes to unvisited
    void setFalse();

    ///@brief Setter to set all node´s dist to -1
    void resetDist();

    ///@brief Normal Breadth-First Search(BFS)
    ///@param v
    void bfs(int v);

    ///@brief
    ///@param v
    ///@param order
    ///@param points
    void dfs_articulation_points(int v, int &order, list<string>& points);

    ///@brief
    ///@param v
    ///@param d
    ///@returns
    list<list<string>> distTwoAiports_bfs(const string& v, const string& d);

    ///@brief BFS used to calculate the diameter
    ///@param a
    ///@returns
    int bfs_max_distance(int a);

    ///@brief
    ///@param airpA
    ///@param airpB
    ///@returns
    int distTwoAirports(const string& airpA,const string& airpB);

    ///@brief
    ///@param airpA
    ///@param airpB
    ///@param airlines
    ///@returns
    int distTwoAirportsAirlineRest(const string& airpA,const string& airpB, const list<string>& airlines );

    ///@brief
    ///@param v
    ///@param d
    ///@param airlines
    list<list<string>> distTwoAiportsWithRest_bfs(const string& v, const string& d, const list<string>& airlines);

    ///@brief
    ///@param city1
    ///@param city2
    void distTwoCities_bfs(const pair<string,string> city1, const pair<string,string> city2);

    ///@brief Count the number of reachable airports with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable airports
    int countReachableAirports(string startAirport, int maxFlights);

    ///@brief Count the number of reachable cities with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable cities
    int countReachableCities(string startAirport, int maxFlights);

    ///@brief Count the number of reachable countries with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable countries
    int countReachableCountries(string startAirport, int maxFlights);

    float distance_longANDlat(string airport, float latitude, float longitude);

    ///@brief Getter for the graph´s vector of nodes
    ///@returns The graph´s vector of nodes
    vector<Node> get_nodes() const;

    ///@brief Unordered_set with Airport objects
    std::unordered_set<Airport, AirportHash, AirportEqual> airportTable;

    ///@brief Unordered_set with Airline objects
    std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable;
};

#endif
