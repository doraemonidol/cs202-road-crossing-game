#pragma once
#include "Subject.h"
#include "Observer.h"
#include <iostream>
#include <list>
using namespace std;

class RoadCrossingGame: public Subject{
private:
    list<Observer *> list_observer_;
    string message_;
public:
    ~RoadCrossingGame();
    /* The subscription management methods. */
    void Attach(Observer *observer);
    void Detach(Observer *observer);
    void Notify();
    void CreateMessage(string message);
    void HowManyObserver();
    void SomeBusinessLogic();
};

