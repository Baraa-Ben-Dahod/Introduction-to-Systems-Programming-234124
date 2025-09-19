
#pragma once

#include <iostream>
#include <queue>
#include <vector>

#include "Players/Player.h"
#include "Events/Event.h"
#include "Events/Pack.h"
#include "Events/EventFactory.h"

using std::queue;
using std::vector;
using std::invalid_argument;

class MatamStory{
private:
    unsigned int m_turnIndex;
    int roundNum;
    queue<unique_ptr<Event>> events;
    vector<shared_ptr<Player>> players;

    static vector<string> split(const string& str, char delimiter);

    static void sortPlayers(vector<shared_ptr<Player>>& allPlayers);

    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player* player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
