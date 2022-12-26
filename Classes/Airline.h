#ifndef AED_2_AIRLINE_H
#define AED_2_AIRLINE_H
#include <string>
using namespace std;

class Airline {
private:
    string airline_code;
    string airline_name;
    string callsign;
    string airline_country;
public:
    Airline(string airline_code1, string airline_name1, string callsign1, string airline_country1);
    string getAirlinecode() const;
    string getAirlinename() const;
    string getAirlinecallsign() const;
    string getAirlinecountry() const;
    bool operator==(const Airline& other) const;

};


#endif //AED_2_AIRLINE_H
