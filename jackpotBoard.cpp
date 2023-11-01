#include "jackpotBoard.h"

void JackpotBoard::setUpGame (std::ostream& output) {
    output << "Enter how many players are playing between 1-4, enter 1 to play local multiplayer: ";
    std::cin >> numPlayers;
    std::cin.clear();
    std::cin.ignore(128, '\n');

    while (std::cin.fail() || numPlayers < 1 || numPlayers > 4) {
        output << "Enter how many players are playing between 1-4, enter 1 to play local multiplayer: ";
        std::cin >> numPlayers;
        std::cin.clear();
        std::cin.ignore(128, '\n');

        if (std::cin.fail() || numPlayers < 1 || numPlayers > 4) {
            output << "Error: invalid number of players!\n";
        }
    }

    if (numPlayers != 1) {
        output << "Enter the order you will play in based on number of players, if not you will be randomly ordered: \n";
        std::cin >> playerPosition;

        if (std::cin.fail() || playerPosition < 1 || playerPosition > numPlayers) {
            srand(std::time(0));
            playerPosition = rand() % (4 - 1 + 1) + 1;
        }

        std::cin.clear();
        std::cin.ignore(128, '\n');

    } else { playerPosition = 1; };

    currentPosition = 0;
    player = false;
}

void JackpotBoard::setupNewTurn() {
    ++currentPosition;
    if (currentPosition == playerPosition) {
        player = true;
    } else {
        player = false;
    }
}

void JackpotBoard::printBoard(std::ostream& output) const {
    for (int i = 0; i < SIZE; ++i) {
        if (flipped[i] == false) {
            output << i + 1 << ' ';
        } else {
            output << jackpot[i] << ' ';
        }
    }

    output << '\n';
}

void JackpotBoard::printDiceRolling(std::ostream& output) const {
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    srand(std::time(0));
    int intervalElapse_ms{0};

    while (diff_ms.count() < 500) {
        end = std::chrono::steady_clock::now();
        diff_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        if (diff_ms.count() > intervalElapse_ms) {
            intervalElapse_ms += 100; // print every 100 ms or 0.1 sec
            output << "\nRolling...\t";
            output << rand() % (6 - 1 + 1) + 1 << '\t';
            output << rand() % (6 - 1 + 1) + 1 << '\n';
        }
    }
}

void JackpotBoard::rollDice(std::ostream& output) {
    dice1 = playerDistribution(generator);
    dice2 = playerDistribution(generator);

    output << "\nRolled:\t\t" << dice1 << "\t" << dice2 << '\n';
}

void JackpotBoard::inputToFlipBoard(std::ostream& output) {
    if (player) {
        output << "Enter the number you would like to flip: ";
        std::cin >> numToFlip;
        std::cin.clear();
        std::cin.ignore(128, '\n');
    } else {
        numToFlip = AIdistribution(generator);
    }

    if (dice1 == dice2) {
        while (std::cin.fail() || numToFlip < 1 || numToFlip > 9) { 
        // || (flipped[numToFlip - 1] == false) // if double cannot flip any unflipped up
        // needs to account for doubles roll on roll 1, where nothing is flipped
            if (player) {
                output << "Invalid number entered! Enter a new number: ";
                std::cin >> numToFlip;
                std::cin.clear();
                std::cin.ignore(128, '\n');
            } else {
                numToFlip = AIdistribution(generator);
            }
        }
    } else {
        while (std::cin.fail() || numToFlip < 1 || numToFlip > 9
            || (numToFlip != dice1 && numToFlip != dice2 && (numToFlip != (dice1 + dice2)))
            || flipped[numToFlip - 1] == true) {
            if (player) {
                output << "Invalid number entered! Enter a new number: ";
                std::cin >> numToFlip;
                std::cin.clear();
                std::cin.ignore(128, '\n');
            } else {
                numToFlip = AIdistribution(generator);
            }
        }
    }
    output << numToFlip << " was flipped.\n";

    if (player) {
        player = false;
    }
}

void JackpotBoard::updateBoard() {
    if (dice1 == dice2) {
        flipped[numToFlip - 1] == false ? flipped[numToFlip - 1] = true : flipped[numToFlip - 1] = false;
    } else if (flipped[numToFlip - 1] == false) {
        flipped[numToFlip - 1] = true;
    } else {
        std::cerr << "Error, attempt to JackpotBoard::updateBoard() index " << numToFlip - 1;
        std::cerr << " for numToFlip " << numToFlip << " is invalid!\n";
    }

    if (currentPosition >= numPlayers) {
        currentPosition = 0;
    }
}

bool JackpotBoard::isGameOver() const {
    if ((dice1 == dice2) ||(flipped[dice1 - 1] == false) ||(flipped[dice2 - 1] == false)) return false;
    else if ((dice1 + dice2) <= 9) {
        if (flipped[dice1 + dice2 - 1] == false) return false;
    }

    return true;
}

bool JackpotBoard::wonJackpot() const {
    for (int i = 0; i < SIZE; ++i) {
        if (flipped[i] == false) return false;
    }

    return true;
}

bool JackpotBoard::playAgain(std::ostream& output) const {
    if (player) {
        output << "You ran out of numbers to flip! Bottoms up!\n";
    } else if (wonJackpot()) {
        printBoard(output);
        output << "JACKPOT!!! You won! Everyone else has to drink! Down the hatch!\n";
    } else {
        output << "The AI ran out of numbers to flip! The AI lost!\n";
    }

    char input{};
    bool entered{false};

    while (!entered) {
        output << "Would you like to play again?\nY/N: ";
        std::cin >> input;
        input = toupper(input);

        switch (input) {
            case 'Y':
                entered = true; // redundant?
                return true;
            case 'N':
                output << "Thanks for playing!\n";
                entered = true; // redundant?
                return false;
            default:
                output << "Please enter Y or N!\n";
                break;
        }

        std::cin.clear();
        std::cin.ignore(128, '\n');
    }

    std::cerr << "Error: exited JackBoard::playAgain() loop without indicating Y/N\n";
    return false;
}

void JackpotBoard::resetBoard() {
    for (int i = 0; i < SIZE; ++i) {
        flipped[i] = false;
    }
}
