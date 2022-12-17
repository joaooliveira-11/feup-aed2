#ifndef AED_2_FLIGHT_H
#define AED_2_FLIGHT_H
#include <string>
using namespace std;

class Flight {
private:
    string source;
    string target;
    string airline;
public:
    Flight(string source1 , string target1, string airline1);
};


#endif //AED_2_FLIGHT_H
