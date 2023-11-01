#include <iostream>
#include <random>
#include <chrono>

int const SIZE{9};

class JackpotBoard {
    private:
        bool flipped[SIZE]{false};
        char jackpot[SIZE]{'.','J','A','C','K','P','O','T','.'};
        int dice1{0};
        int dice2{0};
        int numToFlip{0};

        // AI multiplayer variables
        int numPlayers{0};
        int playerPosition{0};
        int currentPosition{0};
        bool player = false;

        // random dice values
        std::random_device rd;
        std::default_random_engine generator{rd()};
        std::uniform_int_distribution <int> playerDistribution{1, 6};
        std::uniform_int_distribution <int> AIdistribution{1, 9};
    
    public:
        void setUpGame(std::ostream& output);

        void setupNewTurn();
        void printBoard(std::ostream& output) const;
        void printDiceRolling(std::ostream& output) const;
        void rollDice(std::ostream& output);

        void inputToFlipBoard(std::ostream& output);
        void updateBoard();

        bool isGameOver() const;
        bool wonJackpot() const;
        bool playAgain(std::ostream& output) const;
        void resetBoard();
};
