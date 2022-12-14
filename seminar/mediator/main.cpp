#include "Header.h"
#include "flight.h"
#include "runway.h"
#include "mediator.h"
using namespace std;

int main()
{
    IMediator* atcMediator = new AirportMediator();
    Flight* sparrow101 = new Flight(atcMediator, "Group8");
    Runway* mainRunway = new Runway(atcMediator, "TanSonNhatAirport");
    sparrow101->getReady();
    mainRunway->land();
    sparrow101->land("TanSonNhatAirport");
    return 0;
};