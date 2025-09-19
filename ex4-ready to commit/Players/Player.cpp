#include <stdexcept>
#include <utility>
#include "Player.h"
using std::make_unique;
using std::move;

int Player::counter = 1;



Player::Player(const string& name, const string& jobTitle, const string& characterType):
 name(name), stillInGame(true) , m_rank(counter){

    counter++;
    if(jobTitle == "Warrior"){
        this->job = make_unique<Warrior>("Warrior");
    }
    else{
        if(jobTitle == "Archer"){
            this->job = make_unique<Archer>("Archer");
        }
        else{

            if(jobTitle == "Magician"){
                this->job = make_unique<Magician>("Magician");
            }
            else{
                throw std::invalid_argument("Invalid Players File");
            }
        }
    }   

    if(characterType == "RiskTaking"){
        this->character = make_unique<RiskTaking>();
    }
    else{
        if(characterType == "Responsible"){
            this->character = make_unique<Responsible>();
        }
        else{
            throw std::invalid_argument("Invalid Players File");
        }
    }
}

Player::Player(const Player& other)
        : character(other.character ? other.character->clone() : nullptr),
          job(other.job ? other.job->clone() : nullptr),
          name(other.name),
          stillInGame(other.stillInGame),
          m_rank(other.m_rank) {}

string Player::getDescription() const{
    string returnedString;
    returnedString = this->name + ", " + this->job->getJobTitle() + " with "
    + this->character->getDescription() + " character (level " + std::to_string(this->job->getLevel())
    + ", force " + std::to_string(this->job->getForce()) + ")";
    return returnedString;
}

string Player::getName() const{
    return this->name;
}

string Player::getJobTitle() const{
    return this->job->getJobTitle();
}

int Player::getLevel() const{
    return this->job->getLevel();
}

int Player::getForce() const{
    return this->job->getForce();
}

int Player::getHealthPoints() const{
    return this->job->getHealthPoints();
}

int Player::getMaxHealth() const{
    return this->job->getMaxHealth();
}

unsigned int Player::getCoins() const{
    return this->job->getCoins();
}

int Player::getRank()const{
    return this->m_rank;
}

void Player::setRank(int rank)
{
    this->m_rank = rank;
}

bool Player::getIsInGame() const{
    return this->stillInGame;
}

Job* Player::getJob(){
    return this->job.get();
}

Character* Player::getCharacter(){
    return this->character.get();
}
void Player::setForce(const int newForce){
    this->job->setForce(newForce);
}

void Player::setLevel(const int newLevel){
    this->job->setLevel(newLevel);
}

void Player::setCurrentHealth(const unsigned int newHealth){
    this->job->setCurrentHealth(newHealth);
}

void Player::setCoins(const unsigned int newCoins){
    this->job->setCoins(newCoins);
}

void Player::setPlayerOut(){
    this->stillInGame = false;
}

bool Player::operator<(const Player& other) const {
    if (this->getLevel() != other.getLevel()) {
        return this->getLevel() > other.getLevel();
    }

    if (this->getCoins() != other.getCoins()) {
        return this->getCoins() > other.getCoins();
    }

    return this->getName() < other.getName();
}

bool Player::operator>(const Player& other) const {
    if (this->getLevel() != other.getLevel()) {
        return this->getLevel() < other.getLevel();
    }

    if (this->getCoins() != other.getCoins()) {
        return this->getCoins() < other.getCoins();
    }

    return this->getName() < other.getName();
}
