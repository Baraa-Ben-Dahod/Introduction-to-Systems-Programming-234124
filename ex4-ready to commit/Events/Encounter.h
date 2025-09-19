#pragma once
#include "Event.h"

class Encounter:public Event
{
public:
    Encounter(const string& enemyType, int combatPower, int loot, int damage);
    ~Encounter() override = default;

    string getDescription() const override;
    virtual int getCombatPower() const;
    virtual int getLoot() const;
    virtual int getDamage() const;
    virtual string getEnemyType() const;

    virtual void setCombatPower(int newCombatPower);
    virtual void updatePack(){}

    int playEvent(Player* currentPlayer) override;

protected:
    int combatPower;
    int loot;
    int damage;
};


class Snail:public Encounter
{
public:
    static const int snailCombatPower = 5;
    static const int snailLoot = 2;
    static const int snailDamage = 10;

    Snail();
    ~Snail() override = default;
};


class Slime:public Encounter
{
public:
    static const int slimeCombatPower = 12;
    static const int slimeLoot = 5;
    static const int slimeDamage = 25;
    
    Slime();
    ~Slime() override = default;
};


class Balrog:public Encounter
{
public:
    static const int balrogCombatPower = 15;
    static const int balrogLoot = 100;
    static const int balrogDamage = 9001;
    
    Balrog();
    ~Balrog() override = default;
};