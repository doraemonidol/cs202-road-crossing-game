#pragma once
#include "Observer.h"

class Subject{
public:
	virtual ~Subject(){};
	virtual void Attach(Observer *observer) = 0;
	virtual void Detach(Observer *observer) = 0;
	virtual void Notify() = 0;
};

