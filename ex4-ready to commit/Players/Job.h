#ifndef MTAM_4_JOB_H
#define MTAM_4_JOB_H
#include "string"
using std::string;
#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

class Job {
private:
    string m_jobType;

protected:
    int m_force;
    int m_level;
    int m_currentHP;
    int m_maxHP;
    int m_coins;

public:
    Job(const string& type, int force = 5, int level = 1, int maxHP = 100, int coins = 10) : m_jobType(type),
    m_force(force), m_level(level), m_currentHP(maxHP), m_maxHP(maxHP), m_coins(coins) {}

    virtual unique_ptr<Job> clone() const = 0;

    virtual string getDescription() const = 0;
    virtual ~Job() = default;
    virtual int getCombatPower() const {
        return m_force + m_level;
    };

    //Getters
    int getForce() const;
    int getLevel() const;
    int getHealthPoints() const;
    int getCoins() const;
    string getJobTitle() const;
    int getMaxHealth() const;
    //Setters
    void setMaxHealth(const int MaxHealth);
    void setJobTitle(const string& newJobType);
    void setLevel(const int newLevel);
    virtual void setForce(const int newForce);
    void setCurrentHealth(const int CurrentHealth);
    void setCoins(const int newCoins);

    virtual int applyEvent(Job* job) = 0;

};

class Warrior : public Job {
public:
    Warrior(const string& type) : Job(type) {
        this->m_maxHP = 150;
        this->m_currentHP = 150;
    }

    unique_ptr<Job> clone() const override {
        return make_unique<Warrior>(*this);
    }

    string getDescription() const override {
        return "Warrior";
    }

    int getCombatPower() const override {
        return m_force*2 + m_level;
    }

    int applyEvent(Job* job) override;

};



class Archer : public Job {
public:
    Archer(const string& type) : Job(type) {
        this->m_coins = 20;
    }

    unique_ptr<Job> clone() const override {
        return make_unique<Archer>(*this);
    }

    string getDescription() const override {
        return "Archer";
    }

    int applyEvent(Job* job) override;
};

class Magician : public Job {
public:
    Magician(const string& type):Job(type){}
    
    unique_ptr<Job> clone() const override {
        return make_unique<Magician>(*this);
    }

    string getDescription() const override {
        return "Magician";
    }

    int applyEvent(Job* job) override;
};




#endif //MTAM_4_JOB_H
