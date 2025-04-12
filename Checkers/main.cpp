#include "Game.h"

int main(int argc, char** argv) {

	/*
	new game

	while (gameRunning) {
		outputBoard

		do{
			takeUserInput
				validate()
					check if we captured before. If cached "selected piece" exists, then we have.

			performMove()
			
		}
		while(noMoreCapturesOrChoseExit(piece))


		evalwinconditions

		next turn
	}

	victory message
	*/
	Board b;
	Game g(&b);

	while (true) {
		b.printBoard(g.isBlacksTurn());

		do {
			g.takeValidUserInput();
			g.performUserInput();
		} while (g.isCurrentlyActiveCapture());

		g.nextTurn();

		if (g.evalWinConditions())
			break;
	}

	if (g.isBlacksTurn())
		std::cout << "White wins!";
	else
		std::cout << "Black wins!";

	return 0;
}