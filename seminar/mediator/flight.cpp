#include "flight.h"

Flight::Flight(IMediator*& atcMediator, std::string _id)
{
    this->atcMediator = atcMediator;
    this->id = _id;
    atcMediator->registerFlight(this);
}
void Flight::land(std::string id)
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

std::string Flight::getID()
{
    return this->id;
}