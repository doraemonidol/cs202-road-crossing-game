#pragma once
#include "Header.h"
#include "flight.h"
#include "mediator.h"
#include "BaseComponent.h"

class Flight;
class Runway;
class Command;
class IMediator;

class Runway : public Command {
private:
    std::string id;
    IMediator* atcMediator;

public:
    Runway(IMediator*& atcMediator, std::string _id);
    void land(std::string id = "");
    std::string getID();
};