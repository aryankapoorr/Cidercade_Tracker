/******************************************************************************

Aryan Kapoor
Net ID: AXK200159

*******************************************************************************/
// Class declarations/imports below
#ifndef GAME_H
#define GAME_H
#include <string>
#include <iostream>

class Game {
    // Private class members, instance variables for game attributes
    private:
        std::string name;
        long highScore;
        std::string initials;
        int plays;
        double revenue;

    public:
        // Class constructors
        Game();
        Game(std::string, long, std::string, int);

        // Get methods for each class attribute
        std::string getName() { return name; }
        long getScore() { return highScore; }
        std::string getInitials() { return initials; }
        int getPlays() { return plays; }
        double getRevenue() { return revenue; }

        // Set methods for each class attribute
        // *revenue does not have its own set method as it
        // is solely based off of the plays attribute
        void setName(std::string n) { name = n; }
        void setScore(long s) { highScore = s; }
        void setInitials(std::string i) { initials = i; }
        void setPlays(int p) { plays = p; revenue = plays * 0.25; }

        // Class overloaded relational operators, based off of the highScore attribute
        bool operator<(Game&);
        bool operator>(Game&);
        bool operator==(Game&);
        friend std::ostream& operator<<(std::ostream&, const Game&);

};
#endif