
#pragma once

#include "../Players/Player.h"

class Event {
public:
    explicit Event(const string& eventType);
    virtual ~Event() = default;
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;
    virtual int playEvent(Player* currentPlayer) = 0;

protected:
    string eventType;
};


class SolarEclipse:public Event
{
public:
    SolarEclipse();
    ~SolarEclipse() override = default;

    string getDescription() const override;
    int playEvent(Player* currentPlayer) override;
};


class PotionsMerchant:public Event
{
public:
    PotionsMerchant();
    ~PotionsMerchant() override = default;

    string getDescription() const override;
    int playEvent(Player* currentPlayer) override;
};