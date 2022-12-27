#include <iostream>
#include "Classes/Reading.h"
#include "Classes/Graph.h"
#include "Classes/Flight.h"

int main() {
    Reading reading;
    reading.readAirports();
    reading.readAirlines();

    reading.printAIRPORTtablesize();
    reading.printAIRLINEtablesize();

    Graph voos = reading.readFlights();
    voos.verNodes();


    return 0;
}
