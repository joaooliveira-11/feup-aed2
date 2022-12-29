#include <iostream>
#include "Reading.h"
#include "Graph.h"
#include "Flight.h"
#include "Menu.h"


void Menu::readmenu() {

    Reading reading;
    Graph voos = reading.readAllFiles();

    bool flag = true, flag2 = true;
    string answer;
    string airport_code;
    char tecla;
    cout << voos.distTwoAirports("OPO","PXO") ;

    //voos.bfs(17);
/*
    while(flag){
        cout << "Press a key according to what you want to do: \n"
                "1 : Ver todas as informaoes de um aeroporto. \n"
                "q : Quit. \n";

        cin >> tecla;
        switch(tecla){
            case '1':
                cout << "Insert the Airport's code. \n";
                cin >> airport_code;
                while(flag2){
                    Airport airport = Airport(airport_code);
                    auto itr = voos.airportTable.find(airport);
                    if(itr == voos.airportTable.end()){
                        cout << "This airport doesn´t exist in this database, insert a valid code." << endl;
                        cin >> airport_code;
                    }
                    else{
                        cout << "Press a key according to what you want to do: \n"
                                "1 : Saber quantos voos existem a partir deste aeroporto. \n"
                                "2 : Saber o numero de companhias aereas diferentes envolvidas nos voos que partem deste aeroporto. \n"
                                "3 : Saber o numero de destinos diferentes que este aeroporto alcanca. \n"
                                "4 : Saber o numero de paises diferentes que este aeroporto alcanca. \n";
                        cin >> tecla;
                        switch(tecla){
                            case '1': {
                                int number_voos = 0;
                                for (auto el: voos.nodes[itr->getNumCode() - 1].adj) {
                                    number_voos += el.company.size();
                                }
                                cout << "Existe um total de" << " " << number_voos << " voos a partir deste aeroporto"
                                     << endl;
                                break;
                            }
                            case '2': {
                                set<string> airlines_names;
                                for (auto el: voos.nodes[itr->getNumCode() - 1].adj) {
                                    for (string airline_code: el.company) {
                                        airlines_names.insert(airline_code);
                                    }
                                }
                                cout << "Existe um total de" << " " << airlines_names.size()
                                     << " companhias aereas diferentes envolvidas nos voos que partem deste aeroporto. \n";

                                cout << "Deseja saber quais sao as companhias aereas envolvidas? \n";
                                cin >> answer;
                                if(answer == "yes") for (string airline_code: airlines_names) cout << airline_code << endl;
                                break;
                            }
                            case '3':{
                                int numero_destinos = 0;
                                for (auto el: voos.nodes[itr->getNumCode() - 1].adj) numero_destinos++;
                                cout << "Existe um total de" << " " << numero_destinos
                                     << " aeroportos/destinos diferentes possiveis de alcancar atraves deste aeroporto. \n";
                                break;
                            }
                            case '4':{
                                set<string> numero_paises;
                                auto itr = voos.airportTable.find(airport);
                                string country = itr->getAirportcountry();
                                for (auto el: voos.nodes[itr->getNumCode() - 1].adj){
                                    Airport aux = Airport(el.dest);
                                    auto itr = voos.airportTable.find(aux);
                                    string country_aux = itr->getAirportcountry();
                                    if(country != country_aux) numero_paises.insert(country_aux);
                                }
                                cout << "Existe um total de" << " " << numero_paises.size()
                                     << " paises diferentes possiveis de alcancar atraves deste aeroporto. \n";
                                break;
                            }
                            case 'q':
                                break;
                        }
                    }
                }

            case 'q':
                break;

            default:
                cout << "Not a valid key! \n";
                break;
        }
    }
*/
}
