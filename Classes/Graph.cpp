

#include <stack>
#include <queue>
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

vector<Graph::Node> Graph::get_nodes(){
    return this->nodes;
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

void Graph::setFalse() {
    for(Node &node : this->nodes){
        node.visited = false;
    }
}
void Graph::resetDist() {
    for(Node &node : this->nodes){
        node.dist = -1;
    }
}

void Graph::bfs(int v) {
    this->setFalse();
    this->resetDist();
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].dist = 0;
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front();
        q.pop();
        for (auto &e : nodes[u].adj) {
            Airport aux = Airport(e.dest);
            std::unordered_set<Airport>::const_iterator itr_aux = this->airportTable.find(aux);
            int w = itr_aux->getNumCode()-1;
            if (!nodes[w].visited) {
                nodes[w].dist = nodes[u].dist +1;
                nodes[w].visited = true;
                q.push(w);

            }
        }
    }
}

/*
ret > 0 -> "distancia" entre os aeroportos
ret = 0 -> mesmo aeroporto
ret =-1 -> não é possível chegar ao aeroporto
ret =-2 -> um dos aeroportos não existe
 */
int Graph::distTwoAirports(string airpA,string airpB ){
    if ( airpA==airpB){
        return 0;
    }
    Airport aux1 = Airport(airpA);
    std::unordered_set<Airport>::const_iterator itr_airpA =this->airportTable.find(aux1);
    Airport aux2 = Airport(airpB);
    std::unordered_set<Airport>::const_iterator itr_airpB  =this->airportTable.find(aux2);
    if( itr_airpA==this->airportTable.end() or itr_airpB==this->airportTable.end() ){
        return -2;
    }
    int airpA_numCode = itr_airpA->getNumCode();
    int airpB_numCode = itr_airpB->getNumCode();
    this->bfs(airpA_numCode-1);
    return (this->nodes[airpB_numCode-1].dist);
}
