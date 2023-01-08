

#ifndef AED_2_AIRPORT_H
#define AED_2_AIRPORT_H

#include <string>
using namespace std;

class Airport {
private:
    ///@brief The Airport´s code, name, city and country
    string airport_code, airport_name, city, airport_country;

    ///@brief The Airports´s latitude and longitude
    float latitute, longitude;

    ///@brief The Airport´s numCode (The position of each airport in the vector of the graph is numCode -1)
    int numCode;

public:
    ///@brief Constructor of new Airport given it´s Airport code, name, city, country, latitude and longitude
    ///@param airport_code1
    ///@param airport_name1
    ///@param city
    ///@param airport_country1
    ///@param latitude1
    ///@param longitude1
    Airport(string airport_code1, string airport_name1, string city, string airport_country1, float latitude1, float longitude1, int numCode);

    ///@brief Empty Airport constructor.
    Airport();

    ///@brief Constructor of new Airport given it´s Airport code
    explicit Airport(string code);

    ///@brief Getter for the Airport´s code.
    ///@returns A Airports´s code.
    string getAirportcode() const;

    ///@brief Getter for the Airport´s name.
    ///@returns A Airport´s name.
    string getAirportname() const;

    ///@brief Getter for the Airport´s city.
    ///@returns A Airport´s city.
    string getAirportcity() const;

    ///@brief Getter for the Airport´s country.
    ///@returns A Airport´s country.
    string getAirportcountry() const;

    ///@brief Getter for the Airports´s latitude.
    ///@returns A Airports´s latitude.
    float getAirportlatitude() const;

    ///@brief Getter for the Airport´s longitude.
    ///@returns A Airline´s longitude.
    float getAirportlongitude() const;

    ///@brief Getter for the Airport´s numCode.
    ///@returns A Airport´s numCode.
    int getNumCode() const;

    ///@brief Operator= overload.
    ///@returns True if our Airport´s code is equal to the Airport received as parameter.
    ///@param other
    bool operator==(const Airport& other) const;
};

#endif //AED_2_AIRPORT_H
