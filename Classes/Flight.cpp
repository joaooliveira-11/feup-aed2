
#include "Flight.h"
using namespace std;

Flight::Flight(string source1 , string target1, string airline1) : source(source1), target(target1), airline(airline1) {}

string Flight::getFlightsource() const {return source;}
string Flight::getFlighttarget() const {return target;}
string Flight::getFlightairline() const {return airline;}