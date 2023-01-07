#ifndef AED_2_MENU_H
#define AED_2_MENU_H


class Menu {
public:
    ///@brief Runs the interactive user menu.
    static void readmenu();
    static void rede_nrVoos();
    static void rede_nrAeroportos();
    static void rede_nrCompanhias();
    static void rede_diametro();
    static void pais_nrAeroportos(const string &pais);
    static void pais_nrVoos(const string &country);
    static void pais_nrCompanhias(const string &country);
    static void companhia_nrVoos(const string &airline1);
    static void companhia_nrAeroportos(const string &airline1);
    static void aeroporto_nrVoos(const Airport &airport1);
    static void nrCompanhias_voos_Airport(const Airport &airport1);
    static void nr_destinos_aeroporto(const Airport &airport1);
    static void nr_paises_aeroporto(const Airport &airport1);
    static void nr_aeroportos_Maxvoos(const Airport &airport, int number);
    static void nr_cidades_Maxvoos(const Airport &airport, int number);
    static void nr_paises_Maxvoos(const Airport &airport, int number);
    static void rede_top_k_aeroportos_voos(int k);
    static void rede_top_k_aeroportos_companhias(int k);
    static void Articulated_points();
};


#endif
