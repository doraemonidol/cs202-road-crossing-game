#pragma once
#include "Header.h"
#include "runway.h"
#include "mediator.h"
#include "BaseComponent.h"

class Flight : public Command {
private:
    std::string id;
    IATCMediator* atcMediator;

public:
    Flight(IATCMediator*& atcMediator, std::string _id);
    void land(std::string id);
    void getReady();
    std::string getID();
};