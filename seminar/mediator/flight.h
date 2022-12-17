#pragma once
#include "Header.h"
#include "runway.h"
#include "mediator.h"

class Flight {
private:
    std::string id;
    IMediator* atcMediator;

public:
    Flight(IMediator*& atcMediator, std::string _id);
    void land(std::string id);
    void getReady();
    std::string getID();
};