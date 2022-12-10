#pragma once
#include "flight.h"
#include "runway.h"
#include "Header.h"
#include "IMediator.h"

class Flight;
class Runway;
class Command;
class IATCMediator;

class AirportMediator : public IATCMediator {
private:
    std::vector<Flight*> flight;
    std::vector<Runway*> runway;
    std::vector<bool> land;

public:
    void registerRunway(Runway* runway, bool status);
    void registerFlight(Flight* flight);
    bool isLandingOk(std::string id);
    void setLandingStatus(bool status, std::string id);
};