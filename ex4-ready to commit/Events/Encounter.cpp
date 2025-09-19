#include "Encounter.h"

#include <utility>

Encounter::Encounter(const string& enemyType, int combatPower, int loot, int damage):
Event(enemyType), combatPower(combatPower), loot(loot), damage(damage){}

string Encounter::getDescription() const{
    string returnedString = this->eventType + " (power " + to_string(this->combatPower) + ", loot " +
    to_string(this->loot) + ", damage " + to_string(this->damage) + ")";
    return returnedString;
}

int Encounter::getCombatPower() const{
    return this->combatPower;
}

int Encounter::getDamage() const{
    return this->damage;
}

int Encounter::getLoot() const{
    return this->loot;
}

string Encounter::getEnemyType() const{
    return this->eventType;
}

void Encounter::setCombatPower(const int newCombatPower){
    this->combatPower = newCombatPower;
}

Snail::Snail():Encounter("Snail", snailCombatPower, snailLoot, snailDamage){}

Slime::Slime():Encounter("Slime", slimeCombatPower, slimeLoot, slimeDamage){}

Balrog::Balrog():Encounter("Balrog", balrogCombatPower, balrogLoot, balrogDamage){}

int Encounter::playEvent(Player* currentPlayer) {
    int pCombatPower = 0;
    int flag = 0;

    // Calculate player combat power
    if (currentPlayer->getJobTitle() == "Warrior") {
        pCombatPower = (2 * currentPlayer->getForce()) + currentPlayer->getLevel();
    } else {
        pCombatPower = currentPlayer->getForce() + currentPlayer->getLevel();
    }

    // Case: player loses or draws
    if (this->getCombatPower() >= pCombatPower) {
        int newHP = currentPlayer->getHealthPoints() - this->getDamage();
        if (newHP <= 0) {
            currentPlayer->setCurrentHealth(0);
            currentPlayer->setPlayerOut();
            flag = 2; // fainted
        } else {
            currentPlayer->setCurrentHealth(newHP);
            flag = 1; // damaged but alive
        }
    }
    // Case: player wins
    else {
        currentPlayer->setCoins(currentPlayer->getCoins() + this->getLoot());
        currentPlayer->setLevel(currentPlayer->getLevel() + 1);
    }

    if (currentPlayer->getJobTitle() == "Warrior" && currentPlayer->getIsInGame() && flag == 0) {
        int newHP = currentPlayer->getHealthPoints() - 10;
        if (newHP <= 0) {
            currentPlayer->setCurrentHealth(0);
            currentPlayer->setPlayerOut();
        } else {
            currentPlayer->setCurrentHealth(newHP);
        }
    }

    if (this->eventType == "Pack") {
        this->updatePack();
    }

    return flag;
}
