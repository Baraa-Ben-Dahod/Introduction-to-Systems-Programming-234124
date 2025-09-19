
#include <algorithm>

#include "MatamStory.h"

#include "Utilities.h"

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream)
    : m_turnIndex(1), roundNum(0)
{
    /*===== STEP 1: Read and validate EVENTS file =====*/
    std::string wholeFile;
    std::string line;
    std::vector<std::string> words;

    int counter = 0;
    while (std::getline(eventsStream, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        std::vector<std::string> tokens = split(line, ' ');
        for (const auto& token : tokens) {
            if (token != " ") {
                wholeFile += token + " ";
            }
        }
    }
    words = split(wholeFile, ' ');

    for (int i = 0; i < (int)words.size(); i++) {
        EventFactory eventCreator;
        counter++;
        try {
            if (words[i] == "Pack") {
                std::queue<int> counts;
                std::queue<std::string> types;
                int numOfAdded = 0;

                if ((int)words.size() < i + 1 || std::stoi(words[i + 1]) < 2 ||
                    words[i + 1].find(".") != std::string::npos) {
                    throw std::invalid_argument("Invalid Events File");
                }
                counts.push(std::stoi(words[i + 1]));

                if ((int)words.size() < i + 1 + std::stoi(words[i + 1])) {
                    throw std::invalid_argument("Invalid Events File");
                }
                i += 2;
                int end = i + counts.front();
                for (; i < end; i++) {
                    types.push(words[i]);
                    if (words[i] == "Pack") {
                        if ((int)words.size() < i + 1 || std::stoi(words[i + 1]) < 2 ||
                            words[i + 1].find(".") != std::string::npos) {
                            throw std::invalid_argument("Invalid Events File");
                        }
                        counts.push(std::stoi(words[i + 1]));
                        if ((int)words.size() < i + 1 + std::stoi(words[i + 1])) {
                            throw std::invalid_argument("Invalid Events File");
                        }
                        end += 1 + std::stoi(words[i + 1]);
                        i++;
                    }
                    numOfAdded++;
                }
                std::queue<int> tempCounts = counts;
                int sum = 0;
                while (!tempCounts.empty()) {
                    sum += tempCounts.front();
                    tempCounts.pop();
                }
                if (numOfAdded != sum) {
                    throw std::invalid_argument("Invalid Events File");
                }
                i--;
                try {
                    this->events.push(eventCreator.createPack(types, counts));
                } catch (...) {
                    throw std::invalid_argument("Invalid Events File");
                }
            } else {
                this->events.emplace(eventCreator.createEvent(words[i]));
            }
        } catch (...) {
            throw std::invalid_argument("Invalid Events File");
        }
    }
    if (counter < 2) {
        throw std::invalid_argument("Invalid Events File");
    }

    /*===== STEP 2: Read and validate PLAYERS file =====*/
    wholeFile.clear();
    while (std::getline(playersStream, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        wholeFile += line + " ";
    }
    words = split(wholeFile, ' ');

    if (words.size() % 3 != 0 || words.size() / 3 < 2 || words.size() / 3 > 6) {
        throw std::invalid_argument("Invalid Players File");
    }

    for (int i = 0; i < (int)words.size(); i += 3) {
        if (i + 2 < (int)words.size()) {
            if (words[i].length() > 15 || words[i].length() < 3) {
                throw std::invalid_argument("Invalid Players File");
            }
            for (char c : words[i]) {
                if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z') {
                    throw std::invalid_argument("Invalid Players File");
                }
            }
            this->players.push_back(std::make_shared<Player>(
                words[i], words[i + 1], words[i + 2]));
        } else {
            throw std::invalid_argument("Invalid Players File");
        }
    }
}



vector<string> MatamStory::split(const string& str, char delimiter) {
    vector<string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (start != string::npos) {
        if (end != string::npos) {
            if (end > start) { 
                tokens.push_back(str.substr(start, end - start));
            }
            start = end + 1;
            end = str.find(delimiter, start);
        } else {
            if (start < str.size()) {
                tokens.push_back(str.substr(start));
            }
            break;
        }
    }
    
    return tokens;
}

void MatamStory::playTurn(Player* currentPlayer) {
    printTurnDetails(m_turnIndex, *currentPlayer, *events.front());
    int status = events.front()->playEvent(currentPlayer);

    if(events.front()->getDescription() != "PotionsMerchant" &&
       events.front()->getDescription() != "SolarEclipse"){
        if(status == 2){
            currentPlayer->setPlayerOut();
            currentPlayer->setCurrentHealth(0);
            printTurnOutcome(getEncounterLostMessage(*currentPlayer, dynamic_cast<Encounter*>(events.front().get())->getDamage()));
        }
        else{
            if(status == 0){
                printTurnOutcome(getEncounterWonMessage(*currentPlayer, dynamic_cast<Encounter*>(events.front().get())->getLoot()));
            }
            else{
                printTurnOutcome(getEncounterLostMessage(*currentPlayer, dynamic_cast<Encounter*>(events.front().get())->getDamage()));
            }
        }
        if(dynamic_cast<Encounter*>(events.front().get())->getEnemyType() == "Balrog"){
            dynamic_cast<Encounter*>(events.front().get())->setCombatPower(dynamic_cast<Encounter*>(events.front().get())->getCombatPower() + 2);
        }
    }
    else{
        if(events.front()->getDescription() == "PotionsMerchant"){
            if(currentPlayer->getHealthPoints() > currentPlayer->getMaxHealth()){
                currentPlayer->setCurrentHealth(currentPlayer->getMaxHealth());
            }
            printTurnOutcome(getPotionsPurchaseMessage(*currentPlayer, status));
        }
        else{
            printTurnOutcome(getSolarEclipseMessage(*currentPlayer, status));
        }
    }
    events.push(std::move(events.front()));
    events.pop();

    m_turnIndex = m_turnIndex + 1;
}

void MatamStory::sortPlayers(vector<shared_ptr<Player>>& allPlayers) {
    std::sort(allPlayers.begin(), allPlayers.end(), [](const shared_ptr<Player>& a, const shared_ptr<Player>& b) {
        return *a < *b;
    });
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    for (int i = 0; i < int(players.size()); i++)
    {
        if(players[i]->getIsInGame()){
            playTurn(players[i].get());
        }
    }
    this->roundNum++;

    /*=============================================*/

    printRoundEnd();

    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    vector<shared_ptr<Player>> temp;
    for (const auto& player : players) {
        temp.push_back(make_shared<Player>(*player));
    }

    sortPlayers(temp);

    for (int i = 0; i < int(temp.size()); i++)
    {
        printLeaderBoardEntry(i + 1, *temp[i]);
    }
    

    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    bool allOut = true;
    for (const auto& player : players) {
        if (player->getIsInGame()) {
            allOut = false;
        }
        if (player->getLevel() >= 10) {
            return true; // winner exists
        }
    }
    return allOut; // true if all players fainted
}



void MatamStory::play() {
    printStartMessage();

    for (size_t i = 0; i < players.size(); ++i) {
        printStartPlayerEntry(static_cast<unsigned int>(i + 1), *players[i]);
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    // Sort players (by level, coins, name, rank)
    sortPlayers(players);

    printGameOver();

    // Case 1: winner exists
    if (!players.empty() && players[0]->getLevel() >= 10) {
        printWinner(*players[0]);
        return;
    }

    // Case 2: no winner
    printNoWinners();
}
