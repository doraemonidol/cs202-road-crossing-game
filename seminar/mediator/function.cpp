#include "Header.h"
using namespace std;
 
void ATCMediator::registerRunway(Runway*& runway)
{
    this->runway = runway;
}
void ATCMediator::registerFlight(Flight*& flight)
{
    this->flight = flight;
}
bool ATCMediator::isLandingOk()
{
    return land;
}
void ATCMediator::setLandingStatus(bool status)
{
    land = status;
}

Flight::Flight(IATCMediator*& atcMediator)
{
    this->atcMediator = atcMediator;
}
void Flight::land()
{
    if (atcMediator->isLandingOk()) {
        std::cout << "Successfully Landed." << std::endl;
        atcMediator->setLandingStatus(true);
    } else {
        std::cout << "Waiting for landing." << std::endl;
    }
}
void Flight::getReady()
{
    std::cout << "Ready for landing." << std::endl;
}


Runway::Runway(IATCMediator*& atcMediator)
{
    this->atcMediator = atcMediator;
    atcMediator->setLandingStatus(true);
}
void Runway::land()
{
    std::cout << "Landing permission granted." << std::endl;
    atcMediator->setLandingStatus(true);
}
