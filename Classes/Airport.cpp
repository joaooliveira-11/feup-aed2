#include "Airport.h"
using namespace std;

Airport::Airport(string airport_code1, string airport_name1, string city1, string airport_country1, float latitude1, float longitude1) : airport_code(airport_code1), airport_name(airport_name1), city(city1), airport_country(airport_country1), latitute(latitude1), longitude(longitude1) {}

Airport::Airport(){
    this-> airport_code = "";
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
bool Airport::operator==(const Airport& other) const{
    return this->airport_code == other.airport_code && this->airport_name == other.airport_name && this->city == other.city
    && this->airport_country == other.airport_country && this->latitute == other.latitute && this->longitude == other.longitude;
}