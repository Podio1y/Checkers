#pragma once
#include "Board.h"

class Game
{
public:
	Game(Board*);
	~Game();

	void takeUserInput();

	bool validateSelection(int, int);
	bool pieceHasMoves(int, int);
	bool inBounds(cords);

	bool validateTarget(move);
	bool equalCords(cords, cords);
	void nextTurn();
	bool earnedPromotion(move);

	void calculateAllPossibleMovesForPiece(cords);

	bool evalWinConditions();

	move blankMove();

	Board* b;
	move currentMove;
	bool blacksTurn;
	bool activeCapture;

	std::vector<cords>possibleMoves;

private:
	
};

