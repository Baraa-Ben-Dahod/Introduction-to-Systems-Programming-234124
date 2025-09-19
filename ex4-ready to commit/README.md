# Exercise 4 – MatamStory (Game Simulation)

This assignment implements **MatamStory**, a simplified role-playing game inspired by MapleStory, written in C++.  
It combines **object-oriented programming**, **design patterns**, and **modular system design**.

---

---

## Game Rules

- **Players**: 2–6 players, each with a chosen **Job** (Warrior, Archer, Magician) and **Character type** (Responsible, RiskTaking).  
- **Stats**:
  - Level (≥1, starts at 1)
  - Force (≥0, depends on job & events)
  - Health Points (HP: current & max)
  - Coins (gold currency)

- **Events**:
  - **Encounter (Monster/Pack)**: Player fights based on combat power.
  - **Solar Eclipse**: Magic users gain force, others lose force.
  - **Potion Merchant**: Players may buy healing potions based on their character type.

- **Combat**:
  - Warriors use `CombatPower = Force * 2 + Level`.
  - Others use `CombatPower = Force + Level`.
  - Winner: gains coins and a level-up.
  - Loser: loses HP. Warriors also take bonus damage when fighting in close range.

- **Game End**:
  - A player reaches level 10 → wins the game.
  - All players faint (0 HP) → no winner.

---

## Core Components

### `MatamStory`
- Loads players & events from input files.
- Controls game flow:
  - `playTurn(Player&)` – plays a single turn for a player.
  - `playRound()` – plays a full round (each player acts once).
  - `isGameOver()` – checks win/lose condition.
  - `play()` – full game loop with start message, rounds, and end.

### `Player`
- Represents a single character with stats.
- Provides `getDescription()`, `getName()`, `getLevel()`, `getForce()`, `getHealthPoints()`, `getCoins()`.

### `Event`
- Abstract class for all game events.
- Provides `getDescription()`.

### `Utilities`
- Printing functions for consistent output:
  - `printStartMessage`, `printStartPlayerEntry`, `printBarrier`
  - `printTurnDetails`, `printTurnOutcome`
  - `printRoundStart`, `printRoundEnd`
  - `printLeaderBoardMessage`, `printLeaderBoardEntry`
  - `printGameOver`, `printWinner`, `printNoWinners`

---

## Running & Testing

Compile all code:
```bash
g++ --std=c++17 -Wall -pedantic-errors -Werror -DNDEBUG *.cpp Events/*.cpp Players/*.cpp -I. -I./Players -I./Events -o MatamStory
```

Run with event & player files:
```bash
./MatamStory tests/test1.events tests/test1.players > test1.out
```

Compare with expected output:
```bash
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```

---

## Key Skills Practiced

- Advanced OOP design in C++  
- Use of **design patterns** and extensibility (Open–Closed principle)  
- STL containers & smart pointers  
- Exception handling and modular code structure  
