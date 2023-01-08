#ifndef AED_2_AIRLINE_H
#define AED_2_AIRLINE_H
#include <string>
using namespace std;

class Airline {
private:
    ///@brief The Airline´s code, name, callsign and country
    string airline_code, airline_name, callsign, airline_country;
public:
    ///@brief Constructor of new Airline given it´s airline code, name, callsign and country
    ///@param airline_code1
    ///@param airline_name1
    ///@param callsign1
    ///@param airline_country1
    Airline(string airline_code1, string airline_name1, string callsign1, string airline_country1);

    ///@brief Getter for the Airline´s code.
    ///@returns A Airline´s code.
    string getAirlinecode() const;

    ///@brief Getter for the Airline´s name.
    ///@returns A Airline´s name
    string getAirlinename() const;

    ///@brief Getter for the Airline´s callsign.
    ///@returns A Airline´s callsign.
    string getAirlinecallsign() const;

    ///@brief Getter for the Airline´s country.
    ///@returns A Airline´s country.
    string getAirlinecountry() const;

    ///@brief Operator= overload.
    ///@returns True if all of our Airline´s atributes are equal to all atributes from the Airline received as parameter.
    ///@param other
    bool operator==(const Airline& other) const;

};

#endif //AED_2_AIRLINE_H
