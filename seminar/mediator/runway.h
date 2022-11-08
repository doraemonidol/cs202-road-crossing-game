#pragma once
#include "Header.h"
#include "flight.h"
#include "mediator.h"
#include "BaseComponent.h"

class Flight;
class Runway;
class Command;
class IATCMediator;

class Runway : public Command {
private:
    std::string id;
    IATCMediator* atcMediator;

public:
    Runway(IATCMediator*& atcMediator, std::string _id);
    void land(std::string id = "");
    std::string getID();
};