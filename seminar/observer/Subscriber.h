#pragma once
#include "Observer.h"
#include "RoadCrossingGame.h"

class Subscriber: public Observer{
private:
    string message_from_subject_;
    RoadCrossingGame &subject_;
    int number_;
public:
    Subscriber(RoadCrossingGame &subject, int &cnt);
    ~Subscriber();

    void Update(const string &message_from_subject);
    void RemoveMeFromTheList();
    void PrintInfo();
};

