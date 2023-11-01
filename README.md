Introduction to Jackpot
=======================

Jackpot is a multiplayer game where players roll dice and flip one of nine panels on a board.

The goal of the game is to avoid running out of panels to flip.

Players roll 2 dice, and are allowed to flip panels corresponding to the number rolled on the dice,
or the sum of the values of the two dice.

The board panels run from numbers one to nine, and any sums above 9 do not count for flipping.

If you roll doubles, where both dice are the same number, you have the additional option of
flipping any panel back to its original state.

The current implementation supports up to 4 players in AI singleplayer.
(The AI makes random valid inputs).

You may also play local multiplayer by having one player and passing the machine running this
program between the other players.


How To Run
----------
Compile jackpotMain.cpp and jackpotBoard.cpp at the same time,
with jackpotBoard.h in the same directory path,
and then run the compiled program on your local system.


Rules
-----

Jackpot was originally a drinking game, which is why the following occurs when players lose:

- When a player loses by running out of panels to flip that correspond to their dice
or sum of dice, they are obligated to take a shot of alcohol.

- If a player is the one to flip over the last panel remaining on the board and all panels are
facing the flipped, letter side, they win JACKPOT! and all other players at the table are obligated
to drink.

Notes
-----

The project is a demo and in its early alpha stages. There will be further developments to make the program more accessible and cross-platform.
