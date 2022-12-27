#include <iostream>
#include "Classes/Reading.h"
#include "Classes/Graph.h"
#include "Classes/Flight.h"

int main() {
    Reading reading;

    Graph voos = reading.readAllFiles();
    voos.verNodes();
    return 0;
}
