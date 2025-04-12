#pragma once
#include <iostream>

typedef struct _cords {
	int y;
	int x;
} cords;

typedef struct _move {
	cords selected;
	cords target;
} move;

class Board
{
public:
	Board();
	~Board();

	void initBoard();
	void printBoard(bool);

	bool isPiece(cords);
	bool isBlack(cords);
	bool isKing(cords);
	bool isCapture(move);

	void movePiece(move);
	void capturePiece(move);
	void promotePiece(cords);

private:
	char board[8][8];
};