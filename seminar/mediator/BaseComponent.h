#pragma once
#include "flight.h"
#include "runway.h"
#include "mediator.h"
#include "Header.h"

class Command {
public:
    virtual void land(std::string id) = 0;
};
