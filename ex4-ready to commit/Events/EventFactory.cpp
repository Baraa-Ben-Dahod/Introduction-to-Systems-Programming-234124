#include "EventFactory.h"
#include <exception>
#include <stdexcept>

unique_ptr<Event> EventFactory::createEvent(const string& type) {
    if (type == "Snail") return make_unique<Snail>();
    if (type == "Slime") return make_unique<Slime>();
    if (type == "Balrog") return make_unique<Balrog>();
    if (type == "PotionsMerchant") return make_unique<PotionsMerchant>();
    if (type == "SolarEclipse") return make_unique<SolarEclipse>();
    throw std::invalid_argument("Invalid Events File");
}

unique_ptr<Pack> EventFactory::createPack(queue<string>& types, queue<int>& counts){
    vector<unique_ptr<Encounter>> newEncounterPack;
    if (counts.empty()) {
        throw std::invalid_argument("Invalid Events File");
    }
    int counter = 0;
    int topCount = counts.front();
    int damage = 0, loot = 0, combatPower = 0;
    for (int i = 0; i < topCount; i++)
    {
        if(types.front() == "Pack"){
            types.pop();
            counts.pop();
            try
            {
                newEncounterPack.push_back(createPack(types, counts));
            }
            catch(const exception& e)
            {
                newEncounterPack.clear();
                throw std::invalid_argument("Invalid Events File");
            }
            counter++;
        }
        else{
            unique_ptr<Encounter> encounter;
            try{
                auto event = createEvent(types.front());
                auto encounter = dynamic_cast<Encounter*>(event.get());
                if (!encounter) {
                    throw std::invalid_argument("Invalid Events File");
                }
                encounter = static_cast<Encounter*>(event.release());

                damage += encounter->getDamage();
                combatPower += encounter->getCombatPower();
                loot += encounter->getLoot();
                newEncounterPack.push_back(std::unique_ptr<Encounter>(encounter));
            }
            catch(const exception& e){
                newEncounterPack.clear();
                throw std::invalid_argument("Invalid Events File");
            }
            types.pop();
        }
    }
    return make_unique<Pack>(std::move(newEncounterPack), topCount, combatPower, loot, damage);
}