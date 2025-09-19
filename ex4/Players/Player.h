#pragma once

#include <string>
#include "Job.h"
#include "Character.h"
#include <memory>


using std::string;
using std::unique_ptr;
using std::to_string;
class Job;
class Character;

class Player {
public:
    Player(const string& name, const string& job, const string& character);

    ~Player() = default;

    Player(const Player&);

    string getDescription() const;

    string getName() const;

    string getJobTitle() const;

    int getLevel() const;

    int getForce() const;
    
    int getHealthPoints() const;

    int getMaxHealth() const;

    unsigned int getCoins() const;

    int getRank()const;
    
    void setRank(int rank);

    bool getIsInGame() const;

    Job* getJob();

    Character* getCharacter();

    void setForce(int newForce);

    void setLevel(int newLevel);

    void setCurrentHealth(unsigned int newHealth);

    void setCoins(unsigned int newCoins);

    void setPlayerOut();

    Player& operator=(const Player&) = delete;

    bool operator<(const Player& other) const;

    static int counter;

    bool operator>(const Player& other) const;
    

private:
    unique_ptr<Character> character;
    unique_ptr<Job> job;
    string name;
    bool stillInGame;
    int m_rank;
};
