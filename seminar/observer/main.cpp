#include "RoadCrossingGame.h"
#include "Subscriber.h"

int main(){
	int cnt = 0;
	RoadCrossingGame *subject = new RoadCrossingGame;
	Subscriber *subscriber1 = new Subscriber(*subject, cnt);
	Subscriber *subscriber2 = new Subscriber(*subject, cnt);
	Subscriber *subscriber3 = new Subscriber(*subject, cnt);
	Subscriber *subscriber4;
	Subscriber *subscriber5;

	subject->CreateMessage("Game Release!!!");
	subscriber3->RemoveMeFromTheList();

	subject->CreateMessage("Update v1.1!");
	subscriber4 = new Subscriber(*subject, cnt);

	subscriber2->RemoveMeFromTheList();
	subject->CreateMessage("Update v1.2!");
	subscriber5 = new Subscriber(*subject, cnt);

	subject->CreateMessage("Update v2.0!");
	subject->CreateMessage("Hotfix v2.1!");
	subscriber5->RemoveMeFromTheList();

	subscriber4->RemoveMeFromTheList();
	subscriber1->RemoveMeFromTheList();

	delete subscriber5;
	delete subscriber4;
	delete subscriber3;
	delete subscriber2;
	delete subscriber1;
	delete subject;
	return 0;
}