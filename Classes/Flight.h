#ifndef AED_2_FLIGHT_H
#define AED_2_FLIGHT_H
#include <string>
using namespace std;

class Flight {
private:
    ///@brief The Flight´s source, target, airline
    string source, target, airline;
public:
    ///@brief Constructor of new Flight given it´s Flight source, target and airline
    Flight(string source1 , string target1, string airline1);

    ///@brief Getter for the Flight´s source Airport.
    ///@returns A Flight´s source.
    string getFlightsource() ;

    ///@brief Getter for the Flight´s target Airport.
    ///@returns A Flight´s target.
    string getFlighttarget() ;

    ///@brief Getter for the Flight´s airline.
    ///@returns A Flight´s airline.
    string getFlightairline();
};


#endif //AED_2_FLIGHT_H
