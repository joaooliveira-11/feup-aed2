#ifndef AED_2_MENU_H
#define AED_2_MENU_H
#include "string"
#include "Airport.h"

class Menu {
public:
    ///@brief Runs the interactive user menu.
    static void readmenu();

    ///@brief Prints the total number of flights
    ///@note Time complexity: O(n)
    static void rede_nrVoos();

    ///@ Prints the total number of airports
    ///@note Time complexity: O(1)
    static void rede_nrAeroportos();

    ///@brief Prints the total number of companhias
    ///@note Time complexity: O(1)
    static void rede_nrCompanhias();

    ///@brief Prints graph´s diameter
    ///@note Time complexity: O(|V|(|V| + |E|))
    static void rede_diametro();

    ///@brief Prints the number of airports in a country
    ///@param pais
    ///@note Time complexity: O(n)
    static void pais_nrAeroportos(const string &pais);

    ///@brief Prints the number of flights departing from a country
    ///@param country
    ///@note Time complexity: O(n)
    static void pais_nrVoos(const string &country);

    ///@brief Prints the number of airlines that do the flights
    ///@param country
    ///@note Time complexity: O(n)
    static void pais_nrCompanhias(const string &country);

    ///@brief Prints the number of flights of a certain airline
    ///@param airline1
    ///@note Time complexity: O(n)
    static void companhia_nrVoos(const string &airline1);

    ///@brief Prints the number of aiports that an airline link
    ///@param airline1
    ///@note Time complexity: O(n)
    static void companhia_nrAeroportos(const string &airline1);

    ///@brief Prints the number of flights departing from an aiport
    ///@param airport1
    ///@note Time complexity: O(n)
    static void aeroporto_nrVoos(const Airport &airport1);

    ///@brief Prints the number of airlines that participate in the flights that depart from an airport
    ///@param airport1
    ///@note Time complexity: O(n)
    static void nrCompanhias_voos_Airport(const Airport &airport1);

    ///@brief Prints the number of different airports reachable from an airport
    ///@param airport1
    ///@note Time complexity: O(n)
    static void nr_destinos_aeroporto(const Airport &airport1);

    ///@brief Prints the number of different countries reachable from an airport
    ///@param airport1
    ///@note Time complexity: O(n)
    static void nr_paises_aeroporto(const Airport &airport1);

    ///@brief Prints the number of different airports reachable with a certain max number of flights
    ///@param airport
    ///@param number
    ///@note Time complexity: O(|V| + |E|)
    static void nr_aeroportos_Maxvoos(const Airport &airport, int number);

    ///@brief Prints the number of different cities reachable with a certain max number of flights
    ///@param airport
    ///@param num
    ///@note Time complexity: O(|V|(|V| + |E|))
    static void nr_cidades_Maxvoos(const Airport &airport, int number);

    ///@brief Prints the number of different countries reachable with a certain max number of flights
    ///@param airport
    ///@param number
    ///@note Time complexity: O(|V|(|V| + |E|))
    static void nr_paises_Maxvoos(const Airport &airport, int number);

    ///@brief Prints the k airports with more flights departing from it
    ///@param k
    ///@note Time complexity: O(n)
    static void rede_top_k_aeroportos_voos(int k);

    ///@brief Prints the k airports with more airlines participating in the flights departing from it
    ///@param k
    ///@note Time complexity: O(n)
    static void rede_top_k_aeroportos_companhias(int k);

    ///@brief Prints graph´s number of articulated points
    ///@note Time complexity: O(|V|(|V| + |E|))
    static void Articulated_points();
};

#endif
