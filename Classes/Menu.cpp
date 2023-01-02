#include <iostream>
#include "Reading.h"
#include "Graph.h"
#include "Flight.h"
#include "Menu.h"

void rede_nrVoos(){
    Reading reading;
    Graph voos = reading.readAllFiles();
    int count = 0;
    for(auto itr = voos.nodes.begin(); itr != voos.nodes.end(); itr++){
        for(auto el : itr->adj){
            count += el.company.size();
        }
    }
    cout << "Este rede apresenta um total de " << count << " voos" << endl;
}

void rede_nrAeroportos(){
    Reading reading;
    Graph voos = reading.readAllFiles();
    cout << "Esta rede apresenta um total de " << voos.airportTable.size() << " aeroportos" << endl;
}

void rede_nrCompanhias(){
    Reading reading;
    Graph voos = reading.readAllFiles();
    cout << "Esta rede apresenta um total de " << voos.airlineTable.size() << " companhias" << endl;
}
void rede_diametro(){
    Reading reading;
    Graph voos = reading.readAllFiles();

    int max = 0;
    voos.nodes[0].visited = true;
    for (int v = 0; v < voos.nodes.size(); v++) {
        int d = voos.bfs_max_distance(v);
        if (d > max) max = d;
    }
    cout << "Esta rede apresenta um diametro igual a " << max << endl;
}
void pais_nrAeroportos(string pais){
    Reading reading;
    Graph voos = reading.readAllFiles();
    int count = 0;
    for(auto itr = voos.airportTable.begin(); itr != voos.airportTable.end(); itr++){
        if(itr->getAirportcountry() == pais) count++;
    }
    if(count == 0) cout << "Este pais nao apresenta nenhum aeroporto ou nao existe na nossa base dados" << endl;
    else cout << "Esta pais apresenta um total de " << count << " aeroportos" << endl;
}

void pais_nrVoos(string country){
    Reading reading;
    Graph voos = reading.readAllFiles();
    int count = 0;

    for(auto airport : voos.airportTable){
        if(airport.getAirportcountry() == country){
            for (auto el: voos.nodes[airport.getNumCode() - 1].adj) {
                count += el.company.size();
            }
        }
    }
    if(count == 0) cout << "Este pais nao apresenta nenhum voo ou nao existe na nossa base dados" << endl;
    else cout << "Este pais apresenta um total de " << count << " voos" << endl;
}

void pais_nrCompanhias(string country){
    Reading reading;
    Graph voos = reading.readAllFiles();
    int count = 0;

    for(auto airline : voos.airlineTable){
       if(airline.getAirlinecountry() == country) count++;
    }
    if(count == 0) cout << "Este pais nao apresenta nenhuma companhia ou nao existe na nossa base dados" << endl;
    else cout << "Este pais apresenta um total de " << count << " companhias" << endl;
}

void companhia_nrVoos(string airline1){
    Reading reading;
    Graph voos = reading.readAllFiles();
    int count = 0;

    for(auto itr = voos.nodes.begin(); itr != voos.nodes.end(); itr++){
        for(auto el : itr->adj){
            for(auto airline : el.company) if(airline == airline1) count++;
        }
    }
    if(count == 0) cout << "Este companhia nao apresenta nenhum voo ou nao existe na nossa base dados" << endl;
    else cout << "Este companhia apresenta um total de " << count << " voos" << endl;
}

void companhia_nrAeroportos(string airline1){
    Reading reading;
    Graph voos = reading.readAllFiles();
    set<string>air_ports;

    for(auto itr = voos.nodes.begin(); itr != voos.nodes.end(); itr++){
        for(auto el : itr->adj){
            for(auto airline : el.company){
                if(airline == airline1){
                    air_ports.insert(el.dest);
                    air_ports.insert(itr->src);
                }
            }
        }
    }
    if(air_ports.size() == 0) cout << "Este companhia nao faz ligacao entre nenhum aeroporto ou nao existe na nossa base dados" << endl;
    else cout << "Este companhia faz ligacaos entre " << air_ports.size() << " aeroportos" << endl;
}

void aeroporto_nrVoos(Airport airport1){
    Reading reading;
    Graph voos = reading.readAllFiles();

    auto itr = voos.airportTable.find(airport1);


    int number_voos = 0;
    for (auto el: voos.nodes[itr->getNumCode() - 1].adj) {
        number_voos += el.company.size();
    }
    cout << "Existe um total de" << " " << number_voos << " voos a partir deste aeroporto" << endl;
}

void nrCompanhias_voos_Airport(Airport airport1){
    Reading reading;
    Graph voos = reading.readAllFiles();

    auto itr = voos.airportTable.find(airport1);
    set<string> airlines_names;
    for (auto el: voos.nodes[itr->getNumCode() - 1].adj) {
        for (string airline_code: el.company) {
            airlines_names.insert(airline_code);
        }
    }
    cout << "Existe um total de" << " " << airlines_names.size()
         << " companhias aereas diferentes envolvidas nos voos que partem deste aeroporto. \n";

    cout << "As companhias envolvidas sao as seguintes: \n";
    for (string airline_code: airlines_names)
        cout << airline_code << endl;
}

void nr_destinos_aeroporto(Airport airport1){
    Reading reading;
    Graph voos = reading.readAllFiles();

    auto itr = voos.airportTable.find(airport1);

    int numero_destinos = 0;
    for (auto el: voos.nodes[itr->getNumCode() - 1].adj) numero_destinos++;
    cout << "Existe um total de" << " " << numero_destinos
         << " aeroportos/destinos diferentes possiveis de alcancar atraves deste aeroporto. \n";
}

void nr_paises_aeroporto(Airport airport1){
    Reading reading;
    Graph voos = reading.readAllFiles();

    set<string> numero_paises;
    auto itr = voos.airportTable.find(airport1);
    string country = itr->getAirportcountry();
    for (auto el: voos.nodes[itr->getNumCode() - 1].adj) {
        Airport aux = Airport(el.dest);
        auto itr = voos.airportTable.find(aux);
        string country_aux = itr->getAirportcountry();
        if (country != country_aux) numero_paises.insert(country_aux);
    }
    cout << "Existe um total de" << " " << numero_paises.size()
         << " paises diferentes possiveis de alcancar atraves deste aeroporto. \n";
}

void nr_aeroportos_Maxvoos(Airport airport, int number){
    Reading reading;
    Graph voos = reading.readAllFiles();
    string code = airport.getAirportcode();
    cout << "E possivel atingir " << voos.countReachableAirports(code, number) << " aeroportos com um maximo de " << number << " voos. \n";

}

void nr_cidades_Maxvoos(Airport airport, int number){
    Reading reading;
    Graph voos = reading.readAllFiles();
    string code = airport.getAirportcode();
    cout << "E possivel atingir " << voos.countReachableCities(code, number) << " cidades com um maximo de " << number << " voos. \n";

}

void nr_paises_Maxvoos(Airport airport, int number){
    Reading reading;
    Graph voos = reading.readAllFiles();
    string code = airport.getAirportcode();
    cout << "E possivel atingir " << voos.countReachableCountries(code, number) << " paises com um maximo de " << number << " voos. \n";

}
void Menu::readmenu() {

    Reading reading;
    Graph voos = reading.readAllFiles();

    bool flag = true, flag2 = true, flag3 = true, flag4 = true;
    string answer;
    string airport_code, departure_airport, arrival_airport;
    char tecla;
    int top_k;


    while(flag){
        cout << "Press a key according to what you want to do: \n"
                "1 : Ver a melhor maneira de voar de um local para o outro. (Local = aeroporto) \n"
                "2 : Ver todas as informaoes de um aeroporto. \n"
                "3 : Saber as estatisticas globais de uma rede. \n"
                "q : Quit. \n";

        cin >> tecla;
        switch(tecla){
            case '1':
                cout << "Insert the departure Airports code. \n";
                cin >> departure_airport;
                while(flag3){
                    Airport airport = Airport(departure_airport);
                    auto itr = voos.airportTable.find(airport);
                    if(itr == voos.airportTable.end()){
                        cout << "This airport doesnt exist in this database, insert a valid code." << endl;
                        cin >> departure_airport;
                    }
                    else break;
                }

                cout << "Insert the arrival Airports code. \n";
                cin >> arrival_airport;
                while (flag3){
                    Airport airport = Airport(arrival_airport);
                    auto itr = voos.airportTable.find(airport);
                    if(itr == voos.airportTable.end()){
                        cout << "This airport doesnt exist in this database, insert a valid code." << endl;
                        cin >> arrival_airport;
                    }
                    else break;
                }
                cout << voos.distTwoAirports(departure_airport, arrival_airport) << endl;
                break;
            case '2': {
                cout << "Insert the Airport's code. \n";
                cin >> airport_code;
                while (flag2) {
                    Airport airport = Airport(airport_code);
                    auto itr = voos.airportTable.find(airport);
                    if (itr == voos.airportTable.end()) {
                        cout << "This airport doesnt exist in this database, insert a valid code." << endl;
                        cin >> airport_code;
                    } else {
                        cout << "Press a key according to what you want to do: \n"
                                "1 : Saber quantos voos existem a partir deste aeroporto. \n"
                                "2 : Saber o numero de companhias aereas diferentes envolvidas nos voos que partem deste aeroporto. \n"
                                "3 : Saber o numero de destinos diferentes que este aeroporto alcanca. \n"
                                "4 : Saber o numero de paises diferentes que este aeroporto alcanca. \n"
                                "5 : Saber o numero maximo de aeroportos alcancaveis com um numero maximo de n voos. \n"
                                "6 : Saber o numero maximo de cidades alcancaveis com um numero maximo de n voos. \n"
                                "7 : Saber o numero maximo de paises alcancaveis com um numero maximo de n voos. \n";
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
                            case '5':
                                int number;
                                cout << "Inser a number. \n";
                                cin >> number;
                                nr_aeroportos_Maxvoos(airport, number);
                                break;
                            case '6':
                                int number1;
                                cout << "Inser a number. \n";
                                cin >> number1;
                                nr_cidades_Maxvoos(airport, number1);
                                break;
                            case '7':
                                int number2;
                                cout << "Inser a number. \n";
                                cin >> number2;
                                nr_paises_Maxvoos(airport, number2);
                                break;
                            case 'q':
                                break;
                        }
                    }
                    break;
                }
            }
            case '3':
                cout << "Press a key according to what you want to do: \n"
                        "1 : Saber estatisticas globais da rede. \n"
                        "2 : Saber estatisticas globais de um pais. \n"
                        "3 : Saber estatisticas globais de uma companhia. \n";
                cin >> tecla;
                switch(tecla){
                    case '1':
                        cout << "Insert the number you want to see for the feature top-k de aeroportos com mais voos / companhias. \n";
                        cin >> top_k;  // falta adicionar flag caso seja maior que o numro de aeroportos
                        rede_nrAeroportos();
                        rede_nrVoos();
                        rede_nrCompanhias();
                        rede_diametro();  // colocar a opcao de quer saber o diametro? porque demora muito tempo uma pesquisa em largura com 69k dados
                        // falta top k
                        break;
                    case '2': {
                        string country;
                        cout << "Insert the country. \n";
                        cin >> country;
                        cout << "Insert the number you want to see for the feature top-k de aeroportos deste pais com mais voos / companhias. \n";
                        cin >> top_k;
                        pais_nrAeroportos(country);
                        pais_nrVoos(country);
                        pais_nrVoos(country);
                        pais_nrCompanhias(country);  // perguntar ao prof se é o numero de companhias areas envolvidas em voos
                                                     // que saem de areportos portugueses
                                                     // ou de fundação portuguesa no ficheiro airlines (exemplo portugal)
                        // falta top k
                        break;
                    }
                    case '3':
                        string airline;
                        cout << "Insert the airlines code. \n";
                        cin >> airline;
                        cout << "Insert the number you want to see for the feature top-k de aeroportos com mais voos desta companhia. \n";
                        cin >> top_k;
                        companhia_nrVoos(airline);
                        companhia_nrAeroportos(airline);
                        // falta top k
                        break;
                }

            case 'q':
                break;

            default:
                cout << "Not a valid key! \n";
                break;
        }
    }
}
