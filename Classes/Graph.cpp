

#include <stack>
#include "Graph.h"


Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

void Graph::insertAirport_intotable(Airport airport){
    this->airportTable.insert(airport);
}

void Graph::insertAirline_intotable(Airline airline){
    this->airlineTable.insert(airline);
}
void Graph::set_airportTable(unordered_set<Airport, AirportHash, AirportEqual> airportTable1){
    this->airportTable = airportTable1;
}

void Graph::set_airlineTable(std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable1){
    this->airlineTable = airlineTable1;
}

int Graph::get_airportTable_size(){
    return this->airportTable.size();
}

int Graph::get_airlineTable_size(){
    this->airlineTable.size();
}

void Graph::addEdge(string src, string dest, string company, int pos){
    nodes[pos].src=src;
    bool flag = true;
    for(auto &edge : nodes[pos].adj){
        if(edge.dest==dest){
            edge.company.push_back(company);
            flag=false;
            break;
        }
    }
   if(flag){
       list<string> auxList;
       auxList.push_back(company);
       nodes[pos].adj.push_back({dest,auxList});
   }
}

void Graph::verNodes(){
    int count = 1;
    for (int i=0;i<nodes.size();i++){
        for(auto x : nodes[i].adj){
            for(auto y:x.company){
                cout << nodes[i].src << " | "
                     << y << " | "
                     << x.dest << " | "
                     << count <<endl;
                count++;
            }
        }
    }
}