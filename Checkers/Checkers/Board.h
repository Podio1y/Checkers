#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

typedef struct _cords {
	int x;
	int y;
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

	bool isPiece(int, int);
	bool isBlack(int, int);
	bool isKing(int, int);
	bool isCapture(move);

	void movePiece(move);
	void capturePiece(move);
	void promotePiece(cords);

	std::vector<cords>blackPieces;
	std::vector<cords>whitePieces;

	char board[8][8];

private:
	// vec of black pieces
	// vec of white pieces

};