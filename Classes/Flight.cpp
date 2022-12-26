
#include "Flight.h"
using namespace std;

Flight::Flight(string source1 , string target1, string airline1) : source(source1), target(target1), airline(airline1) {}

string Flight::getFlightsource() {return source;}
string Flight::getFlighttarget() {return target;}
string Flight::getFlightairline(){return airline;}