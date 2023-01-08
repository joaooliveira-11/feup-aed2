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

    ///@brief dest - Destination node, company - list of airlines
    struct Edge {
        string dest;
        list<string> company;
    };

    struct Node {
        string src;
        list<Edge> adj;
        bool visited;
        int dist;
        int low;
        int num;
    };
    ///@brief AirportHash function for the Airport unordered_set
    struct AirportHash {
        std::size_t operator()(const Airport& airport) const {
            size_t h = 0;
            h = 37 * hash<string>()(airport.getAirportcode());
            return h;
        }
    };
    ///@brief AirlineHash function for the Airline unordered_set
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
    ///@brief AirportEqual function for the Airport unordered_set
    struct AirportEqual {
        bool operator()(const Airport& airport1, const Airport& airport2) const {
            return airport1 == airport2;
        }
    };
    ///@brief AirlineEqual function for the Airline unordered_set
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
    ///@note Time complexity: O(1)
    void addEdge(string src, const string& dest, const string& company, int pos);

    ///@brief Insert a new Airport in the airports unordered_set
    ///@param airport
    ///@note Time complexity: O(1)
    void insertAirport_intotable(const Airport& airport);

    ///@brief Insert a new Airline in the airlines unordered_set
    ///@param airline
    ///@note Time complexity: O(1)
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

    ///@brief Setter to set all nodes to unvisited
    ///@note Time complexity: O(V)
    void setFalse();

    ///@brief Setter to set all node´s dist to -1
    ///@note Time complexity: O(V)
    void resetDist();

    ///@brief Normal Breadth-First Search(BFS)
    ///@param v
    ///@note Time complexity: O(|V| + |E|)
    void bfs(int v);

    ///@brief DFS to calculate the number of articulated points and store them in a list
    ///@param v
    ///@param order
    ///@param points
    ///@note Time complexity: O(|V| + |E|)
    void dfs_articulation_points(int v, int &order, list<string>& points);

    ///@brief Auxiliar function to store all the paths between the 2 airports
    ///@param v
    ///@param d
    ///@returns List with all the paths between the 2 airports
    ///@note Time complexity: O(|V| + |E|)
    list<list<string>> distTwoAiports_bfs(const string& v, const string& d);

    ///@brief BFS used to calculate the diameter
    ///@param a
    ///@returns The max distance between all nodes and node a
    ///@note Time complexity: O(|V| + |E|)
    int bfs_max_distance(int a);

    ///@brief function to calculate the distance between two airports and print it
    ///@param airpA
    ///@param airpB
    ///@returns distance between the aiports
    ///@note Time complexity: O(|V| + |E|)
    int distTwoAirports(const string& airpA,const string& airpB);

    ///@brief function to calculate the distance between two airports using only certain airlines
    ///@param airpA
    ///@param airpB
    ///@param airlines
    ///@returns distance between the aiports with airlines restrictions
    ///@note Time complexity: O(|V| + |E|)
    int distTwoAirportsAirlineRest(const string& airpA,const string& airpB, const list<string>& airlines );

    ///@brief Auxiliar function to store all the paths between the 2 airports using only certain airlines
    ///@param v
    ///@param d
    ///@param airlines
    ///@returns lists with different paths from airport v to airport d with airlines restrictions
    ///@note Time complexity: O(|V| + |E|)
    list<list<string>> distTwoAiportsWithRest_bfs(const string& v, const string& d, const list<string>& airlines);

    ///@brief function do calculate the shortest path between two cities and print it
    ///@param city1 (pair<city,country)
    ///@param city2 (pair<city,country)
    ///@note Time complexity: O(|V| + |E|)
    void distTwoCities_bfs(const pair<string,string>& city1, const pair<string,string> city2);

    ///@brief Count the number of reachable airports with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable airports
    ///@note Time complexity: O(|V| + |E|)
    int countReachableAirports(string startAirport, int maxFlights);

    ///@brief Count the number of reachable cities with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable cities
    ///@note Time complexity: O(|V| + |E|)
    int countReachableCities(string startAirport, int maxFlights);

    ///@brief Count the number of reachable countries with a max number of flights
    ///@param startAirport
    ///@param maxFlights
    ///@returns The number of reachable countries
    ///@note Time complexity: O(|V| + |E|)
    int countReachableCountries(string startAirport, int maxFlights);

    ///@brief Calculates the distance (in kms) between an airport and a Point given its latitude and longitude using Haversine formula
    ///@param airport
    ///@param latitude
    ///@param longitude
    ///@returns the distance (in kms)
    ///@note Time complexity: O(1)
    float distance_longANDlat(string airport, float latitude, float longitude);

    ///@brief Unordered_set with Airport objects
    std::unordered_set<Airport, AirportHash, AirportEqual> airportTable;

    ///@brief Unordered_set with Airline objects
    std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable;

    ///@brief function do calculate the shortest path between all aiports with a lower distance than distMax to coord1 and all aiports with a lower distance than distMax to coord2 and print it
    ///@param coord1
    ///@param coord2
    ///@param distMax
    ///@note Time complexity: O(|V| + |E|)
    void distTwoCoordinates_bfs(const pair<float,float> coord1, const pair<float,float> coord2, float distMax);
};

#endif
