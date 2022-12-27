#include "Airport.h"
using namespace std;

Airport::Airport(string airport_code1, string airport_name1, string city1, string airport_country1, float latitude1, float longitude1, int numCode) : airport_code(airport_code1), airport_name(airport_name1), city(city1), airport_country(airport_country1), latitute(latitude1), longitude(longitude1), numCode(numCode) {}

Airport::Airport(){
    this-> airport_code = "";
    this -> airport_name = "";
    this-> city = "";
    this ->airport_country = "";
    this-> latitute = 0;
    this -> longitude = 0;
}

Airport::Airport(string code) {
    this-> airport_code = code;
    this -> airport_name = "";
    this-> city = "";
    this ->airport_country = "";
    this-> latitute = 0;
    this -> longitude = 0;
}
string Airport::getAirportcode() const {return airport_code;}
string Airport::getAirportname() const {return airport_name;}
string Airport::getAirportcity() const {return city;}
string Airport::getAirportcountry() const {return airport_country;}
float Airport::getAirportlatitude() const {return latitute;}
float Airport::getAirportlongitude() const {return longitude;}
int Airport::getNumCode() const {return numCode;}
bool Airport::operator==(const Airport& other) const{
    return this->airport_code == other.airport_code;
}