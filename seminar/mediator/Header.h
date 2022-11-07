#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class Flight;
class Runway;

class Mediator {
private:
    vector<Flight*> flights;
    vector<Runway*> runways;

public:
    virtual void addRunway(Runway* runway);
    virtual void addFlight(Flight* flight);
    virtual bool isLandingOk(Runway* runway);
    virtual void setLandingStatus(Runway* runway, bool status);
};

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */
class BaseComponent {
protected:
    Mediator* mediator_;

public:
    BaseComponent(Mediator* mediator = nullptr)
        : mediator_(mediator)
    {
    }
    void set_mediator(Mediator* mediator)
    {
        this->mediator_ = mediator;
    }
};

/**
 * Concrete Components implement various functionality. They don't depend on
 * other components. They also don't depend on any concrete mediator classes.
 */
class Flight : public BaseComponent {
public:
    void land()
    {
        cout << "Succesfully Landed.\n";
        this->mediator_->Notify(this, "flight_land");
    }
    void getReady()
    {
        cout << "Ready for landing\n";
        this->mediator_->Notify(this, "flight_ready");
    }
    void wait()
    {
        cout << "Waiting for landing.\n";
    }
};

class Runway : public BaseComponent {
private:
    bool land;

public:
    bool isLandingOk() {
        return land;
    }
    void setLandingStatus(bool status)
    {
        land = status;
        if (status) {
            cout << "Runway freed.\n";
        } else {
            cout << "Runway occupied.\n";
            this->mediator_->Notify(this, "D");
        }
    }
};

/**
 * Concrete Mediators implement cooperative behavior by coordinating several
 * components.
 */
class ConcreteMediator : public Mediator {
private:
    Component1* component1_;
    Component2* component2_;

public:
    ConcreteMediator(Component1* c1, Component2* c2)
        : component1_(c1)
        , component2_(c2)
    {
        this->component1_->set_mediator(this);
        this->component2_->set_mediator(this);
    }
    void Notify(BaseComponent* sender, string event) const override
    {
        if (event == "A") {
            cout << "Mediator reacts on A and triggers following operations:\n";
            this->component2_->DoC();
        }
        if (event == "D") {
            cout << "Mediator reacts on D and triggers following operations:\n";
            this->component1_->DoB();
            this->component2_->DoC();
        }
    }
};

/**
 * The client code.
 */

void ClientCode()
{
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A.\n";
    c1->DoA();
    cout << "\n";
    cout << "Client triggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}