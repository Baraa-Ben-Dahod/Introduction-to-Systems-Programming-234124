#include "Job.h"

int Job::getLevel() const{
    return this->m_level;
}
int Job::getForce() const{
    return this->m_force;
}
int Job::getHealthPoints() const{
    return this->m_currentHP;
}
int Job::getCoins() const{
    return this->m_coins;
}
string Job::getJobTitle() const{
    return this->m_jobType;
}
int Job::getMaxHealth() const{
    return this->m_maxHP;
}
void Job::setMaxHealth(const int newMaxHealth){
    this->m_maxHP = newMaxHealth;
}
void Job::setJobTitle(const string& newJobType){
    this->m_jobType = newJobType;
}
void Job::setLevel(int newLevel){
    this->m_level = newLevel;
}
void Job::setForce(int newForce){
    this->m_force = newForce;
}
void Job::setCurrentHealth(int newCurrentHealth){
    this->m_currentHP = newCurrentHealth;
}
void Job::setCoins(int newCoins){
    this->m_coins = newCoins;
}

int Warrior::applyEvent(Job* job){
    if(job->getForce() != 0){
        job->setForce(job->getForce() - 1);
        return -1;
    }
    return 0;
}

int Archer::applyEvent(Job* job){
    if(job->getForce() != 0){
        job->setForce(job->getForce() - 1);
        return -1;
    }
    return 0;
}

int Magician::applyEvent(Job* job){
    job->setForce(job->getForce() + 1);
    return 1;
}