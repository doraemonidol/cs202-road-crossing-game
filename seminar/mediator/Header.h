#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Flight;
class Runway;

class IATCMediator {
public:
    virtual void registerRunway(Runway*& runway) = 0;
    virtual void registerFlight(Flight*& flight) = 0;
    virtual bool isLandingOk() = 0;
    virtual void setLandingStatus(bool status) = 0;
};

class Command {
public:
    virtual void land() = 0;
};

class ATCMediator : public IATCMediator {
private:
    Flight* flight;
    Runway* runway;

public:
    bool land;
    void registerRunway(Runway*& runway);
    void registerFlight(Flight*& flight);
    bool isLandingOk();
    void setLandingStatus(bool status);
};

class Flight : public Command {
private:
    IATCMediator* atcMediator;

public:
    Flight(IATCMediator*& atcMediator);
    void land();
    void getReady();
};

class Runway : public Command {
private:
    IATCMediator* atcMediator;

public:
    Runway(IATCMediator*& atcMediator);
    void land();
};