#include <iostream>
#include "Classes/Reading.h"
#include "Classes/Graph.h"
#include "Classes/Flight.h"

int main() {
    Reading reading = Reading();

    vector<Flight> flights; // Source,Target,Airline
    flights = reading.readFlights();
    /*
    for(Flight flight : flights){
        cout << flight.getFlightsource() << endl;
        cout << flight.getFlighttarget() << endl;
        cout << flight.getFlightairline() << endl;
    }
     */
//    ta a dar
    Graph voos(flights.size()-1,true);
    int pos = 0;
    for(auto flight: flights){
        voos.addEdge(flight.getFlightsource(),flight.getFlighttarget(),flight.getFlightairline(), pos);
        pos++;
    }
    cout<<"deve ter dado" << endl;
    voos.verNodes();
        /*
    airports = reading.readAirports();
    vector<Airport> airports; // Code,Name,City,Country,Latitude,Longitude
    for(Airport airport : airports){
        cout << airport.getAirportcode() << endl;
        cout << airport.getAirportname() << endl;
        cout << airport.getAirportcity() << endl;
        cout << airport.getAirportcountry() << endl;
        cout << airport.getAirportlatitude() << endl;
        cout << airport.getAirportlongitude() << endl;
    }
     está a dar mas o float está a cortar casas decimais e a arredondar
    */
    /*
    airlines = reading.readAirLines();
    vector<Airline> airlines; // Code,Name,Callsign,Country
    for(Airline airline : airlines){
        cout << airline.getAirlinecode() << endl;
        cout << airline.getAirlinename() << endl;
        cout << airline.getAirlinecallsign() << endl;
        cout << airline.getAirlinecountry() << endl;
    }
     ta a dar
     */


    return 0;
}
