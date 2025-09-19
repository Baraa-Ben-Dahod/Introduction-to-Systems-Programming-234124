#include "Pack.h"

Pack::Pack(vector<unique_ptr<Encounter>> encounterPack, int numberOfEncounters, int combatPower, int damage, int loot):
Encounter("Pack", combatPower, loot, damage),
encounterPack(std::move(encounterPack)), numberOfEncounters(numberOfEncounters){}


int Pack::getDamage() const{
    int sum = 0;
    for (int i = 0; i < this->numberOfEncounters; i++)
    {
        sum += this->encounterPack[i]->getDamage();
    }
    return sum;
}

int Pack::getLoot() const{
    int sum = 0;
    for (int i = 0; i < this->numberOfEncounters; i++)
    {
        sum += this->encounterPack[i]->getLoot();
    }
    return sum;
}

int Pack::getCombatPower() const{
    int sum = 0;
    for (int i = 0; i < this->numberOfEncounters; i++)
    {
        sum += this->encounterPack[i]->getCombatPower();
    }
    return sum;
}

int Pack::getPackSize() const {
    return numberOfEncounters;
}

string Pack::getDescription() const{
    string str = "Pack of " + to_string(this->getPackSize());
    str += " members (power " + to_string(this->getCombatPower());
    str += ", loot " + to_string(this->getLoot());
    str += ", damage " + to_string(this->getDamage());
    str += ")";
    return str;
}

void Pack::updatePack() {
    for (const auto & i : encounterPack) {
        if (i->getEnemyType() == "Balrog") {
            auto* balrog = dynamic_cast<Balrog*>(i.get());
            if (balrog) {
                balrog->setCombatPower(balrog->getCombatPower() + 2);
            }
        } else if (i->getEnemyType() == "Pack") {
            Pack* pack = dynamic_cast<Pack*>(i.get());
            if (pack) {
                pack->updatePack();
            }
        }
    }
}
