#include "Event.h"

#include <utility>

Event::Event(const string& eventType) : eventType(eventType){}

SolarEclipse::SolarEclipse():Event("SolarEclipse"){}

PotionsMerchant::PotionsMerchant():Event("PotionsMerchant"){}

string SolarEclipse::getDescription() const{
    return this->eventType;
}

string PotionsMerchant::getDescription() const{
    return this->eventType;
}

int SolarEclipse::playEvent(Player* currentPlayer){
    return currentPlayer->getJob()->applyEvent(currentPlayer->getJob());
}

int PotionsMerchant::playEvent(Player* currentPlayer){
    return currentPlayer->getCharacter()->applyEvent(currentPlayer->getJob());
}