#include "Board.h"

Board::Board() {
	initBoard();
}

Board::~Board() {

}

void Board::initBoard() {
	bool putPiece = false;

	for (int row = 0; row < 8; row++) {

		for (int col = 0; col < 8; col++) {

			board[row][col] = ' ';

			if (row == 3 || row == 4)
				continue;

			if (putPiece) {
				board[row][col] = (row < 4) ? 'b' : 'w';
			}

			if (col != 7)
				putPiece = !putPiece;
		}
	}

	board[0][1] = 'W';
}

void Board::printBoard(bool blacksTurn) {
	system("cls");

	std::cout << "If you captured a piece and can again, but dont \nwant to, input x as column, and any number as row.\n\n";

	if (blacksTurn)
		std::cout << "Black's turn\n";
	else
		std::cout << "White's turn\n";

	std::cout << "   a b c d e f g h\n";
	for (int row = 0; row < 8; row++) {
		std::cout << "  +_+_+_+_+_+_+_+_+\n";
		std::cout << row << " ";

		for (int col = 0; col < 8; col++) {

			std::cout << "|" << board[row][col];

		}
		std::cout << "|\n";
	}
	std::cout << "  +_+_+_+_+_+_+_+_+\n";
}

void Board::movePiece(move m) {
	board[m.target.y][m.target.x] = board[m.selected.y][m.selected.x];
	board[m.selected.y][m.selected.x] = ' ';
}

void Board::capturePiece(move m) {
	int row = (m.target.y + m.selected.y) / 2;
	int col = (m.target.x + m.selected.x) / 2;
	
	board[row][col] = ' ';
}

void Board::promotePiece(cords c) {
	if (isBlack(c.y, c.x))
		board[c.y][c.x] = 'B';
	else
		board[c.y][c.x] = 'W';
}

bool Board::isCapture(move m) {
	return (m.target.x - m.selected.x) > 1 || (m.target.x - m.selected.x) < -1;
}

bool Board::isBlack(int row, int col) {
	return (board[row][col] == 'b') || (board[row][col] == 'B');
}

bool Board::isPiece(int row, int col) {
	return board[row][col] != ' ';
}

bool Board::isKing(int row, int col) {
	return (board[row][col] < 97) && (board[row][col] != ' ');
}