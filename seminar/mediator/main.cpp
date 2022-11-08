#include "Header.h"
#include "flight.h"
#include "runway.h"
#include "mediator.h"
using namespace std;

int main()
{
    IATCMediator* atcMediator = new ATCMediator();
    Flight* sparrow101 = new Flight(atcMediator, "Sparrow101");
    Runway* mainRunway = new Runway(atcMediator, "TanSonNhatAirport");
    sparrow101->getReady();
    mainRunway->land();
    sparrow101->land("TanSonNhatAirport");
    return 0;
};