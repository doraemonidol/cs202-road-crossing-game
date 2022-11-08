#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Flight;
class Runway;

class IATCMediator {
public:
    virtual void registerRunway(Runway* runway, bool status) = 0;
    virtual void registerFlight(Flight* flight) = 0;
    virtual bool isLandingOk(string id) = 0;
    virtual void setLandingStatus(bool status, string id) = 0;
};

class Command {
public:
    virtual void land(string id) = 0;
};

class ATCMediator : public IATCMediator {
private:
    vector<Flight*> flight;
    vector<Runway*> runway;
    vector<bool> land;

public:
    void registerRunway(Runway* runway, bool status);
    void registerFlight(Flight* flight);
    bool isLandingOk(string id);
    void setLandingStatus(bool status, string id);
};

class Flight : public Command {
private:
    string id;
    IATCMediator* atcMediator;

public:
    Flight(IATCMediator*& atcMediator, string _id);
    void land(string id);
    void getReady();
    string getID();
};

class Runway : public Command {
private:
    string id;
    IATCMediator* atcMediator;

public:
    Runway(IATCMediator*& atcMediator, string _id);
    void land(string id = "");
    string getID();
};