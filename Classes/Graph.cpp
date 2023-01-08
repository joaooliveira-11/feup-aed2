#include <queue>
#include <set>
#include "Graph.h"
#include <cmath>
#include <iostream>
using namespace std;

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {}

void Graph::insertAirport_intotable(const Airport& airport){
    this->airportTable.insert(airport);
}

void Graph::insertAirline_intotable(const Airline& airline){
    this->airlineTable.insert(airline);
}
void Graph::set_airportTable(unordered_set<Airport, AirportHash, AirportEqual> airportTable1){
    this->airportTable = airportTable1;
}

void Graph::set_airlineTable(std::unordered_set<Airline, AirlineHash, AirlineEqual> airlineTable1){
    this->airlineTable =airlineTable1;
}

int Graph::get_airportTable_size() const{
    return this->airportTable.size();
}


void Graph::addEdge(string src, const string& dest, const string& company, int pos){
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
int Graph::bfs_max_distance(int a) {
    if (!nodes[a].visited) return -1;
    for (int i=1; i<=n; i++) {
        nodes[i].visited = false;
        nodes[i].dist = -1;
    }
    queue<int> q;
    q.push(a);
    nodes[a].visited = true;
    nodes[a].dist = 0;
    int max_dist = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e : nodes[u].adj) {
            Airport aux = Airport(e.dest);
            std::unordered_set<Airport>::const_iterator itr_aux = this->airportTable.find(aux);
            int w = itr_aux->getNumCode()-1;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
                nodes[w].dist = nodes[u].dist + 1;
                if (nodes[w].dist > max_dist) max_dist = nodes[w].dist;
            }
        }
    }
    return max_dist;
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



list<list<string>> Graph::distTwoAiportsWithRest_bfs(const string& v,
const string& d,
const list<string>& airlines_) {
    list<list<string>> res;
    this->setFalse();
    queue<list<string>> q; // queue of unvisited nodes
    list<string> aux;
    aux.push_back(v);
    q.push(aux);
    Airport aux1 = Airport(v);
    std::unordered_set<Airport>::const_iterator itr_airpA =this->airportTable.find(aux1);
    int pos = itr_airpA->getNumCode()-1;
    nodes[pos].dist = 0;
    nodes[pos].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        list<string> f_list = q.front();
        q.pop();
        string u = f_list.back();
        aux1 = Airport(u);
        auto itr_aux = this->airportTable.find(aux1);
        int pos_aux = itr_aux->getNumCode()-1;
        if (u == d) res.push_back(f_list);
        else {
            for (auto &e: nodes[pos_aux].adj) {
                for(const auto& x : airlines_){
                    for(const auto& y: e.company){
                        if(x==y){
                            Airport aux = Airport(e.dest);
                            itr_aux = this->airportTable.find(aux);
                            int w = itr_aux->getNumCode() - 1;
                            if(itr_aux->getAirportcode()==d and nodes[w].visited==true){
                                list<string> aux2 = f_list;
                                aux2.push_back(e.dest);
                                q.push(aux2);
                            }
                            else if (!nodes[w].visited) {
                                nodes[w].dist = nodes[pos_aux].dist + 1;
                                nodes[w].visited = true;
                                list<string> aux2 = f_list;
                                aux2.push_back(e.dest);
                                q.push(aux2);
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

//pair<city,country>
void Graph::distTwoCities_bfs(const pair<string,string> city1, const pair<string,string> city2) {
    this->setFalse();
    list<string> airpCity1;
    list<string> airpCity2;
    for (auto x: airportTable) {
        if (x.getAirportcity() == city1.first and x.getAirportcountry() == city1.second) {
            airpCity1.push_back(x.getAirportcode());
        }
        if (x.getAirportcity() == city2.first and x.getAirportcountry() == city2.second) {
            airpCity2.push_back(x.getAirportcode());
        }
    }
    int melhor = 100;
    list<list<string>> res;
    queue<list<string>> q; // queue of unvisited nodes
    for (string airp1: airpCity1) {
        for (string airp2: airpCity2) {
            this->setFalse();
            list<string> aux;
            aux.push_back(airp1);
            q.push(aux);
            Airport aux1 = Airport(airp1);
            std::unordered_set<Airport>::const_iterator itr_airpA = this->airportTable.find(aux1);
            int pos = itr_airpA->getNumCode() - 1;
            nodes[pos].dist = 0;
            nodes[pos].visited = true;
            while (!q.empty()) {
                list<string> f_list = q.front();
                q.pop();
                string u = f_list.back();
                aux1 = Airport(u);
                auto itr_aux = this->airportTable.find(aux1);
                int pos_aux = itr_aux->getNumCode() - 1;
                if (u == airp2) {
                    res.push_back(f_list);
                } else {
                    for (auto &e: nodes[pos_aux].adj) {
                        Airport aux = Airport(e.dest);
                        itr_aux = this->airportTable.find(aux);
                        int w = itr_aux->getNumCode() - 1;
                        if (itr_aux->getAirportcode() == airp2 and nodes[w].visited == true) {
                            list<string> aux2 = f_list;
                            aux2.push_back(e.dest);
                            q.push(aux2);
                            if(nodes[w].dist<melhor){
                                melhor = nodes[w].dist;
                            }
                        } else if (!nodes[w].visited) {
                            nodes[w].dist = nodes[pos_aux].dist + 1;
                            nodes[w].visited = true;
                            list<string> aux2 = f_list;
                            aux2.push_back(e.dest);
                            q.push(aux2);
                        }
                    }
                }
            }
        }
    }
    for ( const auto& a : res){
        if(a.size()==melhor+1){
            int flag_aux = 0;
            for(const auto& x : a ){
                Airport aux = Airport(x);
                std::unordered_set<Airport>::const_iterator itr_aux  =this->airportTable.find(aux);
                string nome_to_print = itr_aux->getAirportname();
                nome_to_print += ", ";
                nome_to_print += itr_aux->getAirportcountry();
                if(itr_aux->getAirportcity()== city2.first and itr_aux->getAirportcountry()==city2.second){
                    cout << nome_to_print <<endl;
                    continue;
                }
                if(flag_aux==0) {
                    cout << nome_to_print << " --> ";
                }
                else{
                    cout << nome_to_print << endl;
                    cout << nome_to_print << " --> ";
                }
                flag_aux++;
            }
            cout<<"________________________________________" <<endl;
        }
    }
}


//pedir longitude e latitude e criar pares para chamar funções
void Graph::distTwoCoordinates_bfs(const pair<float,float> coord1, const pair<float,float> coord2, float distMax) {
    this->setFalse();
    list<string> airpCity1;
    list<string> airpCity2;
    for (auto x: airportTable) {
        if ( distance_longANDlat(x.getAirportcode(), coord1.first, coord1.second) < distMax) {
            airpCity1.push_back(x.getAirportcode());
        }
        if (distance_longANDlat(x.getAirportcode(), coord2.first, coord2.second) < distMax) {
            airpCity2.push_back(x.getAirportcode());
        }
    }
    int melhor = 100;
    list<list<string>> res;
    queue<list<string>> q; // queue of unvisited nodes
    for (string airp1: airpCity1) {
        for (string airp2: airpCity2) {
            this->setFalse();
            list<string> aux;
            aux.push_back(airp1);
            q.push(aux);
            Airport aux1 = Airport(airp1);
            std::unordered_set<Airport>::const_iterator itr_airpA = this->airportTable.find(aux1);
            int pos = itr_airpA->getNumCode() - 1;
            nodes[pos].dist = 0;
            nodes[pos].visited = true;
            while (!q.empty()) {
                list<string> f_list = q.front();
                q.pop();
                string u = f_list.back();
                aux1 = Airport(u);
                auto itr_aux = this->airportTable.find(aux1);
                int pos_aux = itr_aux->getNumCode() - 1;
                if (u == airp2) {
                    res.push_back(f_list);
                } else {
                    for (auto &e: nodes[pos_aux].adj) {
                        Airport aux = Airport(e.dest);
                        itr_aux = this->airportTable.find(aux);
                        int w = itr_aux->getNumCode() - 1;
                        if (itr_aux->getAirportcode() == airp2 and nodes[w].visited == true) {
                            list<string> aux2 = f_list;
                            aux2.push_back(e.dest);
                            q.push(aux2);
                            if(nodes[w].dist<melhor){
                                melhor = nodes[w].dist;
                            }
                        } else if (!nodes[w].visited) {
                            nodes[w].dist = nodes[pos_aux].dist + 1;
                            nodes[w].visited = true;
                            list<string> aux2 = f_list;
                            aux2.push_back(e.dest);
                            q.push(aux2);
                        }
                    }
                }
            }
        }
    }
    for ( const auto& a : res){
        if(a.size()==melhor+1){
            int flag_aux = 0;
            for(const auto& x : a ){
                Airport aux = Airport(x);
                std::unordered_set<Airport>::const_iterator itr_aux  =this->airportTable.find(aux);
                string nome_to_print = itr_aux->getAirportname();
                nome_to_print += ", ";
                nome_to_print += itr_aux->getAirportcountry();
                if(distance_longANDlat(itr_aux->getAirportcode(),coord2.first, coord2.second)< distMax){
                    cout << nome_to_print <<endl;
                    continue;
                }
                if(flag_aux==0) {
                    cout << nome_to_print << " --> ";
                }
                else{
                    cout << nome_to_print << endl;
                    cout << nome_to_print << " --> ";
                }
                flag_aux++;
            }
            cout<<"________________________________________" <<endl;
        }
    }
}



list<list<string>> Graph::distTwoAiports_bfs(const string& v, const string& d) {
    list<list<string>> res;
    this->setFalse();
    queue<list<string>> q; // queue of unvisited nodes
    list<string> aux;
    aux.push_back(v);
    q.push(aux);
    Airport aux1 = Airport(v);
    std::unordered_set<Airport>::const_iterator itr_airpA =this->airportTable.find(aux1);
    int pos = itr_airpA->getNumCode()-1;
    nodes[pos].dist = 0;
    nodes[pos].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        list<string> f_list = q.front();
        q.pop();
        string u = f_list.back();
        aux1 = Airport(u);
        auto itr_aux =this->airportTable.find(aux1);
        int pos_aux = itr_aux->getNumCode()-1;
        if (u == d) {
            res.push_back(f_list);
        } else {
            for (auto &e: nodes[pos_aux].adj) {
                Airport aux = Airport(e.dest);
                itr_aux = this->airportTable.find(aux);
                int w = itr_aux->getNumCode() - 1;
                if(itr_aux->getAirportcode()==d and nodes[w].visited==true){
                    list<string> aux2 = f_list;
                    aux2.push_back(e.dest);
                    q.push(aux2);
                }
                else if (!nodes[w].visited) {
                    nodes[w].dist = nodes[pos_aux].dist + 1;
                    nodes[w].visited = true;
                    list<string> aux2 = f_list;
                    aux2.push_back(e.dest);
                    q.push(aux2);
                }
            }
        }
    }
    return res;
}
/*
ret > 0 -> "distancia" entre os aeroportos
ret = 0 -> mesmo aeroporto
ret =-1 -> não é possível chegar ao aeroporto
ret =-2 -> um dos aeroportos não existe
 */
int Graph::distTwoAirports(const string& airpA,const string& airpB){
    if (airpA==airpB){
        cout << "Escreveu o mesmo codigo para os aeroportos de partida e chegada. \n"
                "Para ver as melhores rotas tente dois codigos distintos. \n";
        return 0;
    }
    Airport aux1 = Airport(airpA);
    std::unordered_set<Airport>::const_iterator itr_airpA =this->airportTable.find(aux1);
    Airport aux2 = Airport(airpB);
    std::unordered_set<Airport>::const_iterator itr_airpB  =this->airportTable.find(aux2);
    if(itr_airpA==this->airportTable.end() or itr_airpB==this->airportTable.end()){
        return -2;
    }
    int airpA_numCode = itr_airpA->getNumCode();
    int airpB_numCode = itr_airpB->getNumCode();
    this->bfs(airpA_numCode);
    list<list<string>> aux = this->distTwoAiports_bfs(airpA, airpB);
    int tamanho = this->nodes[airpB_numCode-1].dist;
    for ( const auto& a : aux){
        if(a.size()==tamanho+1){
            int flag_aux = 0;
            for(const auto& x : a ){
                Airport aux = Airport(x);
                std::unordered_set<Airport>::const_iterator itr_aux  =this->airportTable.find(aux);
                string nome_to_print = itr_aux->getAirportname();
                nome_to_print += ", ";
                nome_to_print += itr_aux->getAirportcountry();
                if(x==airpB){
                    cout << nome_to_print <<endl;
                    continue;
                }
                if(flag_aux==0) {
                    cout << nome_to_print << " --> ";
                }
                else{
                    cout << nome_to_print << endl;
                    cout << nome_to_print << " --> ";
                }
                flag_aux++;
            }
            cout<<"________________________________________" <<endl;
        }
    }
    if(this->nodes[airpB_numCode-1].dist==-1){
        cout << "Nao existe forma de chegar de um aeroporto ao outro.\n";
    }
    return (this->nodes[airpB_numCode-1].dist);
}

//dá para 1 airline ou várias porque é usada uma lista como imput
int Graph::distTwoAirportsAirlineRest(const string& airpA,const string& airpB, const list<string>& airlines){
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
    this->bfs(airpA_numCode);
    list<list<string>> aux = this-> distTwoAiportsWithRest_bfs(airpA, airpB, airlines);
    int tamanho = this->nodes[airpB_numCode-1].dist;
    for ( auto a : aux){
        if(a.size()==tamanho+1){
            int flag_aux = 0;
            for(auto x : a ){
                Airport aux = Airport(x);
                std::unordered_set<Airport>::const_iterator itr_aux  =this->airportTable.find(aux);
                string nome_to_print = itr_aux->getAirportname();
                nome_to_print += ", ";
                nome_to_print += itr_aux->getAirportcountry();

                if(x==airpB){
                    cout << nome_to_print <<endl;
                    continue;
                }
                if(flag_aux==0) {
                    cout << nome_to_print << " --> ";
                }
                else{
                    cout << nome_to_print <<endl;
                    cout << nome_to_print << " --> ";
                }
                flag_aux++;
            }
        }
    }
    return (this->nodes[airpB_numCode-1].dist);
}

int Graph::countReachableAirports(string startAirport, int maxFlights) {
    int count = 0;
    Airport aux = Airport(startAirport);
    auto itr = airportTable.find(aux);
    int pos = itr->getNumCode() - 1;
    bfs(pos);
    for(auto & node : nodes){
        if(node.dist <= maxFlights && node.dist >= 1){
            count++;
        }
    }
    return count;
}

int Graph::countReachableCities(string startAirport, int maxFlights){
    set<string> count_cities;
    Airport aux = Airport(startAirport);
    auto itr = airportTable.find(aux);
    int pos = itr->getNumCode() - 1;
    bfs(pos);
    for(int i = 0; i < nodes.size(); i++){
        if(nodes[i].dist <= maxFlights && nodes[i].dist >= 1){
            Airport airport = Airport(nodes[i].src);
            auto itr = airportTable.find(airport);
            if(itr != airportTable.end())count_cities.insert(itr->getAirportcity());
        }
    }
    return count_cities.size();
}

int Graph::countReachableCountries(string startAirport, int maxFlights){
    set<string> count_countries;
    Airport aux = Airport(startAirport);
    auto itr = airportTable.find(aux);
    int pos = itr->getNumCode() - 1;
    bfs(pos);
    for(auto & node : nodes){
        if(node.dist <= maxFlights && node.dist >= 1){
            Airport airport = Airport(node.src);
            auto itr = airportTable.find(airport);
            if(itr != airportTable.end())count_countries.insert(itr->getAirportcountry());
        }
    }
    return count_countries.size();
}

void Graph::dfs_articulation_points(int v, int &order, list<string>& points) {
    nodes[v].visited = true;
    nodes[v].num = nodes[v].low = order++;

    int children = 0;
    bool articulation = false;

    for (auto e : nodes[v].adj) {
        Airport aux = Airport(e.dest);
        auto itr_aux = this->airportTable.find(aux);
        int w;
        if(itr_aux != airportTable.end()) w = itr_aux->getNumCode()-1;
        if (!nodes[w].visited) {
            children++;
            dfs_articulation_points(w, order, points);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
            if (nodes[w].low >= nodes[v].num) articulation = true;
        }
        else
            nodes[v].low = min(nodes[v].low, nodes[w].num);
    }

    if ((nodes[v].num == 1 && children > 1) || (nodes[v].num > 1 && articulation)) {
        Airport airport = Airport(nodes[v].src);
        auto itr = airportTable.find(airport);
        if(itr != airportTable.end()) points.push_front(itr->getAirportcode());
    }
}

float Graph::distance_longANDlat(string airport1, float latitude2, float longitude2){
    float latitude1;
    float longitude1;
    Airport airport = Airport(airport1);
    auto itr = airportTable.find(airport);
    if(itr != airportTable.end()){
        latitude1 = itr->getAirportlatitude();
        longitude1 = itr->getAirportlongitude();
    }
    float dLat = (latitude2 - latitude1) * M_PI / 180.0;
    float dLon = (longitude2 - longitude1) * M_PI / 180.0;

    latitude1 = (latitude1) * M_PI / 180.0;
    latitude2 = (latitude2) * M_PI / 180.0;

    float a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(latitude1) * cos(latitude2);
    float rad = 6371;
    float c = 2 * asin(sqrt(a));
    return rad * c;
}







