#include "runway.h"

Runway::Runway(IMediator*& atcMediator, std::string _id)
{
    this->atcMediator = atcMediator;
    this->id = _id;
    atcMediator->registerRunway(this, true);
}
void Runway::land(std::string id)
{
    std::cout << "Landing permission granted." << std::endl;
    atcMediator->setLandingStatus(true, this->id);
}

std::string Runway::getID()
{
    return this->id;
}