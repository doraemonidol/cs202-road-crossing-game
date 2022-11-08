#include "Header.h"
using namespace std;
 
void ATCMediator::registerRunway(Runway* runway, bool status)
{
    this->runway.push_back(runway);
    this->land.push_back(status);
}
void ATCMediator::registerFlight(Flight* flight)
{
    this->flight.push_back(flight);
}
bool ATCMediator::isLandingOk(string id)
{
    for (int i = 0; i < this->runway.size(); i++) {
        if (this->runway[i]->getID() == id) {
            if (land[i]) {
                land[i] = false;
                return true;
            } else {
                return false;
            }
        }
    }
    std::cout << "Cannot find Runway with ID " << id << "\n";
    return false;
}
void ATCMediator::setLandingStatus(bool status, string id)
{
    for (int i = 0; i < this->runway.size(); i++) {
        if (this->runway[i]->getID() == id) {
            land[i] = status;
        }
    }
}

Flight::Flight(IATCMediator*& atcMediator, string _id)
{
    this->atcMediator = atcMediator;
    this->id = _id;
    atcMediator->registerFlight(this);
}
void Flight::land(string id)
{
    if (atcMediator->isLandingOk(id)) {
        std::cout << "Successfully Landed." << std::endl;
        atcMediator->setLandingStatus(true, id);
    } else {
        std::cout << "Waiting for landing." << std::endl;
    }
}
void Flight::getReady()
{
    std::cout << "Ready for landing." << std::endl;
}

string Flight::getID() {
    return this->id;
}

Runway::Runway(IATCMediator*& atcMediator, string _id)
{
    this->atcMediator = atcMediator;
    this->id = _id;
    atcMediator->registerRunway(this, true);
}
void Runway::land(string id)
{
    std::cout << "Landing permission granted." << std::endl;
    atcMediator->setLandingStatus(true, this->id);
}

string Runway::getID()
{
    return this->id;
}