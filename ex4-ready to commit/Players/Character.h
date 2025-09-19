#ifndef MTAM_4_CHARACTER_H
#define MTAM_4_CHARACTER_H

#include "Job.h"


class Character {
public:
    virtual string getDescription() const = 0;
    virtual ~Character() {}

    virtual unique_ptr<Character> clone() const = 0;

    virtual int applyEvent(Job* job) = 0;

    static const int POTION_PRICE = 5;
    static const int POTION_ADDED_HEALTH = 10;
};

class Responsible : public Character {
public:
    unique_ptr<Character> clone() const override {
        return make_unique<Responsible>(*this);
    }

    string getDescription() const override {
        return "Responsible";
    }

    int applyEvent(Job* job) override;
};

class RiskTaking : public Character {
public:
    unique_ptr<Character> clone() const override {
        return make_unique<RiskTaking>(*this);
    }

    string getDescription() const override {
        return "RiskTaking";
    }

    int applyEvent(Job* job) override;
};



#endif //MTAM_4_CHARACTER_H