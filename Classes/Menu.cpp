#include <iostream>
#include "Reading.h"
#include "Graph.h"
#include "Flight.h"
#include "Menu.h"
using namespace std;

Graph voos = Reading::readAllFiles();

void Menu::rede_nrVoos() {
    int count = 0;
    for (auto &node: voos.nodes) {
        for (const auto &el: node.adj) {
            count += el.company.size();
        }
    }
    cout << "Esta rede tem um total de " << count << " voos. \n";
}

void Menu::rede_nrAeroportos() {
    cout << "Esta rede tem um total de " << voos.airportTable.size() << " aeroportos.\n";
}

void Menu::rede_nrCompanhias() {
    cout << "Esta rede tem um total de " << voos.airlineTable.size() << " companhias. \n";
}

void Menu::rede_diametro() {
    int max = 0;
    voos.nodes[0].visited = true;
    for (int v = 0; v < voos.nodes.size(); v++) {
        int d = voos.bfs_max_distance(v);
        if (d > max) max = d;
    }
    cout << "Esta rede tem um diametro igual a " << max << ". \n";
}

void Menu::pais_nrAeroportos(const string &pais) {
    int count = 0;
    for (const auto &itr: voos.airportTable) {
        if (itr.getAirportcountry() == pais) count++;
    }
    if (count == 0) cout << "Este pais nao tem nenhum aeroporto ou nao existe na nossa base dados. \n";
    else cout << "Este pais tem um total de " << count << " aeroportos. \n";
}

void Menu::pais_nrVoos(const string &country) {
    int count = 0;
    for (const auto &airport: voos.airportTable) {
        if (airport.getAirportcountry() == country) {
            for (const auto &el: voos.nodes[airport.getNumCode() - 1].adj) {
                count += el.company.size();
            }
        }
    }
    if (count == 0) cout << "Este pais nao tem nenhum voo ou nao existe na nossa base dados. \n";
    else cout << "Este pais tem um total de " << count << " voos. \n";
}

void Menu::pais_nrCompanhias(const string &country) {
    int count = 0;
    for (const auto &airline: voos.airlineTable) {
        if (airline.getAirlinecountry() == country) count++;
    }
    if (count == 0) cout << "Este pais nao tem nenhuma companhia ou nao existe na nossa base dados. \n \n";
    else cout << "Este pais tem um total de " << count << " companhias. \n \n";
}

void Menu::companhia_nrVoos(const string &airline1) {
    int count = 0;
    for (auto &node: voos.nodes) {
        for (const auto &el: node.adj) {
            for (const auto &airline: el.company) if (airline == airline1) count++;
        }
    }
    if (count == 0) cout << "Esta companhia nao tem nenhum voo ou nao existe na nossa base dados. \n";
    else cout << "Esta companhia tem um total de " << count << " voos. \n";
}

void Menu::companhia_nrAeroportos(const string &airline1) {
    set<string> air_ports;
    for (auto &node: voos.nodes) {
        for (const auto &el: node.adj) {
            for (const auto &airline: el.company) {
                if (airline == airline1) {
                    air_ports.insert(el.dest);
                    air_ports.insert(node.src);
                }
            }
        }
    }
    if (air_ports.empty())
        cout << "Esta companhia nao faz ligacao entre nenhum aeroporto ou nao existe na nossa base dados. \n \n";
    else cout << "Esta companhia faz ligacao entre " << air_ports.size() << " aeroportos. \n \n";
}

void Menu::aeroporto_nrVoos(const Airport &airport1) {
    auto itr = voos.airportTable.find(airport1);
    int number_voos = 0;
    for (const auto &el: voos.nodes[itr->getNumCode() - 1].adj) {
        number_voos += el.company.size();
    }
    cout << "Existe um total de " << number_voos << " voos a partir deste aeroporto. \n \n";
}

void Menu::nrCompanhias_voos_Airport(const Airport &airport1) {
    auto itr = voos.airportTable.find(airport1);
    set<string> airlines_names;
    for (const auto &el: voos.nodes[itr->getNumCode() - 1].adj) {
        for (const string &airline_code: el.company) {
            airlines_names.insert(airline_code);
        }
    }
    cout << "Existe um total de " << airlines_names.size()
         << " companhias aereas diferentes envolvidas nos voos que partem deste aeroporto. \n";
    cout << "As companhias envolvidas sao as seguintes: \n";
    for (const string &airline_code: airlines_names)
        cout << airline_code << endl;
    cout << endl;
}

void Menu::nr_destinos_aeroporto(const Airport &airport1) {
    auto itr = voos.airportTable.find(airport1);
    int numero_destinos = 0;
    for (auto el: voos.nodes[itr->getNumCode() - 1].adj) numero_destinos++;
    cout << "Existe um total de " << numero_destinos
         << " aeroportos/destinos diferentes possiveis de atingir partindo deste aeroporto. \n \n";
}

void Menu::nr_paises_aeroporto(const Airport &airport1) {
    set<string> numero_paises;
    auto itr = voos.airportTable.find(airport1);
    string country = itr->getAirportcountry();
    for (const auto &el: voos.nodes[itr->getNumCode() - 1].adj) {
        Airport aux = Airport(el.dest);
        itr = voos.airportTable.find(aux);
        string country_aux = itr->getAirportcountry();
        if (country != country_aux) numero_paises.insert(country_aux);
    }
    cout << "Existe um total de " << numero_paises.size()
         << " paises diferentes possiveis de atingir partindo deste aeroporto. \n \n";
}

void Menu::nr_aeroportos_Maxvoos(const Airport &airport, int number) {
    string code = airport.getAirportcode();
    cout << voos.countReachableAirports(code, number) << " aeroportos sao atingiveis com um maximo de " << number
         << " voos. \n \n";
}

void Menu::nr_cidades_Maxvoos(const Airport &airport, int number) {
    string code = airport.getAirportcode();
    cout << voos.countReachableCities(code, number) << " cidades sao atingiveis com um maximo de " << number
         << " voos. \n \n";
}

void Menu::nr_paises_Maxvoos(const Airport &airport, int number) {
    string code = airport.getAirportcode();
    cout << voos.countReachableCountries(code, number) << " paises sao atingiveis com um maximo de " << number
         << " voos. \n \n";
}

struct Compare_Pair {
    bool operator()(const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    }
};

void Menu::rede_top_k_aeroportos_voos(int k) {
    set<pair<string, int>, Compare_Pair> topk;
    for (auto & node : voos.nodes) {
        int number_voos = 0;
        for (const auto &el: node.adj) {
            number_voos += el.company.size();
        }
        pair<string, int> pair = make_pair(node.src, number_voos);
        topk.insert(pair);
    }
    cout << "Os " << k << " aeroportos com mais voos sao os seguintes:\n";
    int count = 0;
    for (const auto & itr : topk) {
        if (count != k) {
            cout << itr.first << " com " << itr.second << " voos.\n";
            count++;
        } else break;
    }
}

void Menu::rede_top_k_aeroportos_companhias(int k) {
    set<pair<string, int>, Compare_Pair> topk;
    for (auto & node : voos.nodes) {
        set<string> airlines_names;
        for (const auto &el: node.adj) {
            for (const string &airline_code: el.company) {
                airlines_names.insert(airline_code);
            }
        }
        pair<string, int> pair = make_pair(node.src, airlines_names.size());
        topk.insert(pair);
    }
    cout << "Os " << k << " aeroportos com mais companhias sao os seguintes:\n";
    int count = 0;
    for (const auto & itr : topk) {
        if (count != k) {
            cout << itr.first << " com " << itr.second << " companhias.\n";
            count++;
        } else break;
    }
    cout << endl;
}

void Menu::Articulated_points(){
    list<string> list;
    for (auto &node : voos.nodes) {
        node.visited = false;
        node.low = 0;
        node.num = 0;
    }
    int order = 1;
    for (int v = 0; v < voos.nodes.size(); v++)
        if (!voos.nodes[v].visited) voos.dfs_articulation_points(v, order, list);
    list.sort();
    //Para ver os articulated points
    //for(auto el : list) cout << el << endl;
    cout << "Existe um total de " << list.size() << " pontos de articulacao. \n";
}


void Menu::readmenu() {
    bool flag = true;
    string answer, airport_code, departure_airport, arrival_airport;
    char tecla;
    int top_k;

    while (flag) {
        cout << "Insira uma tecla de acordo com o que pretende fazer:\n"
                "1 : Saber qual a melhor maneira de voar de um local para o outro. (Local = aeroporto) \n"
                "2 : Saber qual a melhor maneira de voar de um local para o outro com restricao de companhia. (Local = aeroporto). \n"
                "3 : Saber qual a melhor maneira de voar de um local para o outro. (Local = cidade) \n"
                "4 : Saber qual a melhor maneira de voar de um local para o outro. (Local = conjunto de coordenadas) \n"
                "5 : Obter informaoes acerca de um aeroporto. \n"
                "6 : Ver as estatisticas globais. \n"
                "q : Quit. \n";
        cin >> tecla;
        switch (tecla) {
            case '1': {
                cout << "\nInsira o codigo IATA do aeroporto de partida. (ex.: CDG)\n";
                cin >> departure_airport;
                Airport airport = Airport(departure_airport);
                while (voos.airportTable.find(airport) == voos.airportTable.end()) {
                    cout << "Este aeroporto nao existe na nossa base de dados, insira um codigo valido. (ex.: CDG) \n";
                    cin >> departure_airport;
                    airport = Airport(departure_airport);
                }
                cout << "\nInsira o codigo IATA do aeroporto de chegada. (ex.: CDG)\n";
                cin >> arrival_airport;
                Airport airport2 = Airport(arrival_airport);
                while (voos.airportTable.find(airport2) == voos.airportTable.end()) {
                    cout << "Este aeroporto nao existe na nossa base de dados, insira um codigo valido. (ex.: CDG) \n";
                    cin >> arrival_airport;
                    airport2 = Airport(arrival_airport);
                }
                cout << voos.distTwoAirports(departure_airport, arrival_airport) << " voo(s) necessario(s).\n \n";
                break;
            }
            case '2': {
                list<string> airlines;
                string answer;
                cout << "\nInsira o codigo IATA do aeroporto de partida. (ex.: CDG)\n";
                cin >> departure_airport;
                Airport airport = Airport(departure_airport);
                while (voos.airportTable.find(airport) == voos.airportTable.end()) {
                    cout << "Este aeroporto nao existe na nossa base de dados, insira um codigo valido. (ex.: CDG) \n";
                    cin >> departure_airport;
                    airport = Airport(departure_airport);
                }
                cout << "\nInsira o codigo IATA do aeroporto de chegada. (ex.: CDG)\n";
                cin >> arrival_airport;
                Airport airport2 = Airport(arrival_airport);
                while (voos.airportTable.find(airport2) == voos.airportTable.end()) {
                    cout << "Este aeroporto nao existe na nossa base de dados, insira um codigo valido. (ex.: CDG) \n";
                    cin >> arrival_airport;
                    airport2 = Airport(arrival_airport);
                }
                cout << "Insira o código da primeira (ou única) companhia que pretende usar.(ex.: CDG) \n";
                cin >> answer;
                airlines.push_back(answer);
                while(answer != "q") {
                    cout << "Insira mais um código se pretender usar mais alguma companhia.(ex.: CDG) \n"
                            "Se não pretender usar mais companhias aéreas, insira q. \n";
                    cin >> answer;
                    airlines.push_back(answer);
                }
                voos.distTwoAirportsAirlineRest(departure_airport, arrival_airport, airlines);
                break;
            }
            case '3':{
                string departure_city, departure_country;
                string arrival_city, arrival_country;

                cout << "\nInsira o nome da cidade de partida. (ex.: Porto)\n";
                getline(cin >> ws,departure_city);
                cout << "\nInsira o nome do pais da cidade de partida. (ex.: Portugal)\n";
                getline(cin >> ws,departure_country);

                cout << "\nInsira o codigo da cidade de chegada. (ex.: Lisboa)\n";
                getline(cin >> ws,arrival_city);
                cout << "\nInsira o nome do pais da cidade de chegada. (ex.: Portugal)\n";
                getline(cin >> ws,arrival_country);

                pair<string, string> pair1 = make_pair(departure_city, departure_country);
                pair<string, string> pair2 = make_pair(arrival_city, arrival_country);
                voos.distTwoCities_bfs(pair1, pair2);
                break;
            }
            case '4':{
                float latitude1, longitude1;
                float latitude2, longitude2;
                float distMax;
                cout << "\nInsira a latitude do local de partida. (ex.: 48.725278)\n";
                cin >> latitude1;
                cout << "\nInsira a longitude do local de partida. (ex.: 2.359444)\n";
                cin >> longitude1;
                cout << "\nInsira a latitude do local de chegada. (ex.: 48.725278)\n";
                cin >> latitude2;
                cout << "\nInsira a longitude do local de chegada. (ex.: 2.359444)\n";
                cin >> longitude2;
                cout << "\nInsira a distancia maxima entre as coordenadas e os aeroportos. (ex.: 30.0 (km) )\n";
                cin >> distMax;

                pair<float, float> pair1 = make_pair(latitude1, longitude1);
                pair<float, float> pair2 = make_pair(latitude2, longitude2);

                voos.distTwoCoordinates_bfs(pair1, pair2, distMax);
                break;
            }
            case '5': {
                cout << "Insira o codigo IATA do aeroporto. (ex.: CDG)\n";
                cin >> airport_code;
                Airport airport = Airport(airport_code);
                while (voos.airportTable.find(airport) == voos.airportTable.end()) {
                    cout << "Este aeroporto nao existe na nossa base de dados, insira um codigo valido. (ex.: CDG) \n";
                    cin >> airport_code;
                    airport = Airport(airport_code);
                }
                cout << "Insira uma tecla de acordo com o que pretende fazer:\n"
                        "1 : Saber quantos voos existem a partir deste aeroporto. \n"
                        "2 : Saber quantas companhias aereas diferentes estao envolvidas nos voos que partem deste aeroporto. \n"
                        "3 : Saber para quantos aeroportos diferentes pode ir partindo deste aeroporto. \n"
                        "4 : Saber para quantos paises diferentes pode ir partindo deste aeroporto. \n"
                        "5 : Saber o maior numero de aeroportos atingiveis usando um maximo de Y voos. \n"
                        "6 : Saber o maior numero de cidades atingiveis usando um maximo de Y voos. \n"
                        "7 : Saber o maior numero de paises atingiveis usando um maximo de Y voos. \n"
                        "q : Quit \n";
                cin >> tecla;
                switch (tecla) {
                    case '1': {
                        aeroporto_nrVoos(airport);
                        break;
                    }
                    case '2': {
                        nrCompanhias_voos_Airport(airport);
                        break;
                    }
                    case '3': {
                        nr_destinos_aeroporto(airport);
                        break;
                    }
                    case '4': {
                        nr_paises_aeroporto(airport);
                        break;
                    }
                    case '5': {
                        int number;
                        cout << "\nInsira o numero maximo de voos. \n";
                        cin >> number;
                        nr_aeroportos_Maxvoos(airport, number);
                        break;
                    }
                    case '6': {
                        int number1;
                        cout << "\nInsira o numero maximo de voos. \n";
                        cin >> number1;
                        nr_cidades_Maxvoos(airport, number1);
                        break;
                    }
                    case '7': {
                        int number2;
                        cout << "\nInsira o numero maximo de voos. \n";
                        cin >> number2;
                        nr_paises_Maxvoos(airport, number2);
                        break;
                    }
                    case 'q':
                        break;
                    default:
                        cout << "\nInsira uma tecla valida. \n \n";
                        break;
                }
                break;
            }
            case '6': {
                cout << "Insira uma tecla de acordo com o que pretende fazer:\n"
                        "1 : Saber estatisticas globais da rede. \n"
                        "2 : Saber estatisticas globais de um pais. \n"
                        "3 : Saber estatisticas globais de uma companhia. \n"
                        "q : Quit \n";
                cin >> tecla;
                switch (tecla) {
                    case '1':
                        cout << "Insira o valor de k para o top-k de aeroportos com mais voos e/ou companhias. \n";
                        cin >> top_k;
                        rede_nrAeroportos();
                        rede_nrVoos();
                        rede_nrCompanhias();
                        rede_diametro();
                        Articulated_points();
                        rede_top_k_aeroportos_voos(top_k);
                        rede_top_k_aeroportos_companhias(top_k);
                        break;
                    case '2': {
                        string country;
                        cout << "Escreva o nome do pais. (ex.: Spain) \n";
                        cin >> country;
                        pais_nrAeroportos(country);
                        pais_nrVoos(country);
                        pais_nrCompanhias(country);
                        break;
                    }
                    case '3': {
                        string airline;
                        cout << "Insira o codigo ICAO da companhia aerea. (ex.: AAL) \n";
                        cin >> airline;
                        companhia_nrVoos(airline);
                        companhia_nrAeroportos(airline);
                        break;
                    }
                    case 'q':
                        break;
                    default:
                        cout << "\nInsira uma tecla valida. \n";
                        break;
                }
                break;
            }
            case 'q': {
                flag = false;
                break;
            }
            default: {
                cout << "\nInsira uma tecla valida. \n \n";
                break;
            }
        }
    }

}
