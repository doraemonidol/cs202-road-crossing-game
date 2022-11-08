#include "Header.h"
using namespace std;

int main()
{
    IATCMediator* atcMediator = new ATCMediator();
    Flight* sparrow101 = new Flight(atcMediator);
    Runway* mainRunway = new Runway(atcMediator);
    atcMediator->registerFlight(sparrow101);
    atcMediator->registerRunway(mainRunway);
    sparrow101->getReady();
    mainRunway->land();
    sparrow101->land();
    return 0;
};