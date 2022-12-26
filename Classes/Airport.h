

#ifndef AED_2_AIRPORT_H
#define AED_2_AIRPORT_H

#include <string>
using namespace std;

class Airport {
private:
    string airport_code;
    string airport_name;
    string city;
    string airport_country;
    float latitute;
    float longitude;
public:
    Airport(string airport_code1, string airport_name1, string city, string airport_country1, float latitude1, float longitude1);
    string getAirportcode() const;
    string getAirportname() const;
    string getAirportcity() const;
    string getAirportcountry() const;
    float getAirportlatitude() const;
    float getAirportlongitude() const;
    bool operator==(const Airport& other) const;
};


#endif //AED_2_AIRPORT_H
