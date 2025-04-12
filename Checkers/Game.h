#pragma once
#include <vector>
#include "Board.h"

class Game
{
public:
	Game(Board*);
	~Game();
	
	// User input
	void takeValidUserInput();
	void performUserInput();

	// User input validation
	bool validateSelection(cords);
	bool validateTarget(move);
	void calculateAllPossibleMovesForPiece(cords);
	bool pieceHasMoves(cords);

	// Misc.
	bool inBounds(cords);

	bool equalCords(cords, cords);

	bool earnedPromotion(move);

	bool evalWinConditions();

	move blankMove();

	// Getters
	Board* getBoard();
	move getCurrentMove();
	bool isBlacksTurn();
	bool isCurrentlyActiveCapture();
	int getCurrentNumberOfPossibleMoves();
	const std::vector<cords> getCachedPossibleMoves();

	// Setters
	void setCurrentMove(move);
	void nextTurn();
	void setCaptureState(bool);
	void addPossibleMove(cords);
	void clearPossibleMoves();

private:
	Board* b;
	move currentMove;
	bool blacksTurn;
	bool activeCapture;

	std::vector<cords>possibleMoves;
};

