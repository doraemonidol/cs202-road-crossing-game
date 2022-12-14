#pragma once
#include "Header.h"
#include "runway.h"
#include "mediator.h"
#include "BaseComponent.h"

class Flight : public Command {
private:
    std::string id;
    IMediator* atcMediator;

public:
    Flight(IMediator*& atcMediator, std::string _id);
    void land(std::string id);
    void getReady();
    std::string getID();
};