#include "mediator.h"

void ATCMediator::registerRunway(Runway* runway, bool status)
{
    this->runway.push_back(runway);
    this->land.push_back(status);
}
void ATCMediator::registerFlight(Flight* flight)
{
    this->flight.push_back(flight);
}
bool ATCMediator::isLandingOk(std::string id)
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
void ATCMediator::setLandingStatus(bool status, std::string id)
{
    for (int i = 0; i < this->runway.size(); i++) {
        if (this->runway[i]->getID() == id) {
            land[i] = status;
        }
    }
}