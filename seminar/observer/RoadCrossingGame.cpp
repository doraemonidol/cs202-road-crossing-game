#include "RoadCrossingGame.h"

RoadCrossingGame::~RoadCrossingGame() {
    cout << "Goodbye, I was RoadCrossingGame, the Subject.\n";
}

void RoadCrossingGame::Attach(Observer *observer){
    list_observer_.push_back(observer);
}

void RoadCrossingGame::Detach(Observer *observer){
    list_observer_.remove(observer);
}

void RoadCrossingGame::Notify(){
    std::list<Observer *>::iterator iterator = list_observer_.begin();
    HowManyObserver();
    while(iterator != list_observer_.end()) {
        (*iterator)->Update(message_);
        ++iterator;
    }
}

void RoadCrossingGame::CreateMessage(string message = "Empty"){
    this->message_ = message;
    Notify();
}
void RoadCrossingGame::HowManyObserver(){
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
}

void RoadCrossingGame::SomeBusinessLogic(){
    this->message_ = "change message message";
    Notify();
    std::cout << "I'm about to do some thing important\n";
}