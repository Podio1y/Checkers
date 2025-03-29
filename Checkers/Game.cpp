#include "Game.h"

Game::Game(Board* board) {
	b = board;
	currentMove = blankMove();
	blacksTurn = true;
	activeCapture = false;
}

Game::~Game() {

}

move Game::blankMove() {
	return { {-1, -1}, {-1, -1} };
}

bool Game::inBounds(cords c) {
	return (c.x >= 0) && (c.x < 8) && (c.y >= 0) && (c.y < 8);
}

void Game::nextTurn() {
	blacksTurn = !blacksTurn;
}

void Game::calculateAllPossibleMovesForPiece(cords piece) {
	int direction = (blacksTurn) ? 1 : -1; // 1 is down

	possibleMoves.clear();

	for (int y = -1; y < 2; y += 2) {

		for (int x = -1; x < 2; x += 2) {

			if (!inBounds({ piece.x + x, piece.y + y }))
				continue;

			if (!b->isKing(piece.y, piece.x) && direction != y)
				continue;

			// If not a piece, then we can move there.
			if (!activeCapture && !b->isPiece(piece.y + y, piece.x + x)) {
				possibleMoves.push_back({ piece.x + x, piece.y + y });
			}

			// else if its a piece of the opposite color, check if we can capture.
			else if (b->isBlack(piece.y + y, piece.x + x) != blacksTurn) {

				if (inBounds({ piece.x + 2 * x, piece.y + 2 * y })) {

					if (!b->isPiece(piece.y + 2 * y, piece.x + 2 * x))
						possibleMoves.push_back({ piece.x + 2 * x, piece.y + 2 * y });
				}
			}
		}
	}
}

bool Game::pieceHasMoves(int row, int col) {
	calculateAllPossibleMovesForPiece({ col, row });
	return possibleMoves.size() > 0;
}

bool Game::validateSelection(int row, int col) {
	if (!inBounds({col, row}))
		return false;

	return b->isPiece(row, col) && (blacksTurn == b->isBlack(row, col)) && pieceHasMoves(row, col);
}

bool Game::equalCords(cords a, cords b) {
	return (a.x == b.x) && (a.y == b.y);
}

bool Game::validateTarget(move m) {
	for (cords c : possibleMoves) {
		if (equalCords(c, m.target))
			return true;
	}

	return false;
}

void Game::takeUserInput() {
	char col = '.';
	int row = -1;

	if (!activeCapture) {
		currentMove = blankMove();
		do {
			std::cout << "Select piece (<row> <col>): ";
			std::cin >> col >> row;

			currentMove.selected.x = col - 97;
			currentMove.selected.y = row;

		} while (!validateSelection(currentMove.selected.y, currentMove.selected.x));

		std::cout << "\n";
	}
	else {
		currentMove.selected = currentMove.target;
	}

	do {

		std::cout << "Target move (<row> <col>): ";
		std::cin >> col >> row;

		currentMove.target.x = col - 97;
		currentMove.target.y = row;

		if (col == 'x' && activeCapture) {
			activeCapture = false;
			return;
		}

	} while (!validateTarget(currentMove));

	std::cout << "\n";

	b->movePiece(currentMove);

	if (earnedPromotion(currentMove))
		b->promotePiece(currentMove.target);

	if (b->isCapture(currentMove)) {
		b->capturePiece(currentMove);

		activeCapture = true;
		activeCapture = pieceHasMoves(currentMove.target.y, currentMove.target.x);
		b->printBoard(blacksTurn);
	}
}

bool Game::earnedPromotion(move m) {
	if (b->isKing(m.target.y, m.target.x))
		return false;

	return (blacksTurn && m.target.y == 7) || (!blacksTurn && m.target.y == 0);
}

bool Game::evalWinConditions() {
	bool blackCanMove = false;
	bool whiteCanMove = false;

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {

			if (b->isPiece(i, j)) {
				calculateAllPossibleMovesForPiece({ j, i });

				if (possibleMoves.size() > 0) {

					if (b->isBlack(i, j))
						blackCanMove = true;
					else
						whiteCanMove = true;
				}
			}
		}
	}

	return (!blackCanMove && blacksTurn) || (!whiteCanMove && !blacksTurn);
}