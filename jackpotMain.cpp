#include "jackpotBoard.h"

int main() {

    JackpotBoard board;
    bool runGame{true};

    board.setUpGame(std::cout);

    do {
        board.setupNewTurn();
        board.printBoard(std::cout);
        board.printDiceRolling(std::cout);
        board.rollDice(std::cout);

        if (board.isGameOver()) {
            if (!board.playAgain(std::cout)) {
                runGame = false;
                break;
            }

            board.resetBoard();
            board.setUpGame(std::cout);
            continue;
        }

        board.inputToFlipBoard(std::cout);
        board.updateBoard();

        if (board.wonJackpot()) {
            if (!board.playAgain(std::cout)) {
                runGame = false;
                break;
            }

            board.resetBoard();
            board.setUpGame(std::cout);
            continue;
        }

    } while (runGame);

    return 0;
}
