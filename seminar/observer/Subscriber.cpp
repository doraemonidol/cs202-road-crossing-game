#include "Subscriber.h"

Subscriber::Subscriber(RoadCrossingGame &subject, int &cnt): subject_(subject){
    this->subject_.Attach(this);
    std::cout << "Hi, I'm the Subsciber \"" << ++cnt << "\".\n";
    this->number_ = cnt;
}

Subscriber::~Subscriber(){
    std::cout << "Goodbye, I was the Subsciber \"" << this->number_ << "\".\n";
}

void Subscriber::Update(const std::string &message_from_subject){
    message_from_subject_ = message_from_subject;
    PrintInfo();
}

void Subscriber::RemoveMeFromTheList(){
    subject_.Detach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
}

void Subscriber::PrintInfo(){
    std::cout << "Subsciber \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
}