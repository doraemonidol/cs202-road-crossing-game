#pragma once
#include <string>
using namespace std;

class Observer{
public:
	virtual ~Observer(){};
	virtual void Update(const string &message_from_subject) = 0;
};

