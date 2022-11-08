#pragma once
#include "flight.h"
#include "runway.h"
#include "mediator.h"
#include "Header.h"


class Flight;
class Runway;

class IATCMediator {
public:
    virtual void registerRunway(Runway* runway, bool status) = 0;
    virtual void registerFlight(Flight* flight) = 0;
    virtual bool isLandingOk(std::string id) = 0;
    virtual void setLandingStatus(bool status, std::string id) = 0;
};