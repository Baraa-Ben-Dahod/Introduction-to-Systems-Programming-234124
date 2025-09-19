#pragma once
#include "Encounter.h"
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Pack: public Encounter
{
public:
    Pack(vector<unique_ptr<Encounter>> encounterPack, int numberOfEncounters, int combatPower, int damage, int loot);

    string getDescription() const override;
    int getCombatPower() const override;
    int getLoot() const override;
    int getDamage() const override;
    int getPackSize() const;

    void updatePack() override;

private:
    vector<unique_ptr<Encounter>> encounterPack;
    int numberOfEncounters;
};
