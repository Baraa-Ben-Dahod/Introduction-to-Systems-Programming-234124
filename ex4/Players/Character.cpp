#include "Character.h"

int Responsible::applyEvent(Job* job){
    int counter = 0;
    while (job->getCoins() >= POTION_PRICE && job->getHealthPoints() < job->getMaxHealth())
    {
        job->setCurrentHealth(job->getHealthPoints() + POTION_ADDED_HEALTH);
        job->setCoins(job->getCoins() - POTION_PRICE);
        counter++;
    }
    if(job->getHealthPoints() > job->getMaxHealth()){
        job->setCurrentHealth(job->getMaxHealth());
    }
    return counter;
}

int RiskTaking::applyEvent(Job* job){
    if(job->getHealthPoints() < 50){
        if(job->getCoins() >= POTION_PRICE){
            job->setCurrentHealth(job->getHealthPoints() + POTION_ADDED_HEALTH);
            job->setCoins(job->getCoins() - POTION_PRICE);
            return 1;
        }
    }
    if(job->getHealthPoints() > job->getMaxHealth()){
        job->setCurrentHealth(job->getMaxHealth());
    }
    return 0;
}