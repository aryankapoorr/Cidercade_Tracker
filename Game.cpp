/******************************************************************************

Aryan Kapoor

*******************************************************************************/
// Class imports below
#include "Game.h"
#include <iomanip>

/*
* Default constructor, sets the base values for all of the class attributes
*/
Game::Game() {
    name = "";
    highScore = 0;
    initials = "";
    plays = 0;
    revenue = 0;
}

/*
* Overloaded constructor, passing in values for all of the class attributes
*/
Game::Game(std::string n, long s, std::string i, int p) {
    name = n;
    highScore = s;
    initials = i;
    plays = p;
    revenue = plays * 0.25;
}

/*
* Overloaded less than operator, based off of the highScore attribute
*/
bool Game::operator<(Game& g) {
    if (name < g.name)
        return true;
    else
        return false;
}

/*
* Overloaded greater than operator, based off of the highScore attribute
*/
bool Game::operator>(Game& g) {
    if (name > g.name)
        return true;
    else
        return false;
}

/*
* Overloaded equals operator, based on if two highScores are equivalent
*/
bool Game::operator==(Game& g) {
    if (name == g.name)
        return true;
    else
        return false;
}

/*
* Overloaded insertion operator, prints out the content of the game, displaying
* the name and content of different attirbutes
*/
std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << g.name << ", " << g.highScore << ", " << g.initials << ", ";
    os << g.plays << ", $" << std::fixed << std::setprecision(2);
    os << g.revenue << std::endl;

    return os;
}