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

void Game::calculateAllPossibleMovesForPiece(cords piece) {
	int direction = (isBlacksTurn()) ? 1 : -1; // 1 is down
	cords adjacentDiagCords = piece;
	cords captureDiagCords = piece;

	clearPossibleMoves();

	for (int y = -1; y < 2; y += 2) {

		for (int x = -1; x < 2; x += 2) {

			adjacentDiagCords = { piece.y + y, piece.x + x };

			if (!inBounds(adjacentDiagCords))
				continue;

			if (!b->isKing(piece) && direction != y)
				continue;

			// If not a piece, then we can move there.
			if (!activeCapture && !b->isPiece(adjacentDiagCords)) {
				addPossibleMove(adjacentDiagCords);
			}
			// else if its a piece of the opposite color, check if we can capture.
			else if (b->isBlack(adjacentDiagCords) != isBlacksTurn()) {

				captureDiagCords = { piece.y + 2 * y, piece.x + 2 * x };

				if (inBounds(captureDiagCords) && !b->isPiece(captureDiagCords))
					addPossibleMove(captureDiagCords);

			}
		}
	}
}

bool Game::pieceHasMoves(cords c) {
	calculateAllPossibleMovesForPiece(c);
	return getCurrentNumberOfPossibleMoves() > 0;
}

bool Game::validateSelection(cords c) {
	if (!inBounds(c))
		return false;

	return b->isPiece(c) && (isBlacksTurn() == b->isBlack(c)) && pieceHasMoves(c);
}

bool Game::equalCords(cords a, cords b) {
	return (a.x == b.x) && (a.y == b.y);
}

bool Game::validateTarget(move m) {
	for (cords c : getCachedPossibleMoves()) {
		if (equalCords(c, m.target))
			return true;
	}

	return false;
}

void Game::takeValidUserInput() {
	char col = '.';
	int row = -1;

	if (!isCurrentlyActiveCapture()) {
		setCurrentMove(blankMove());
		do {
			std::cout << "Select piece (<row> <col>): ";
			std::cin >> col >> row;

			currentMove.selected.x = col - 97;
			currentMove.selected.y = row;

		} while (!validateSelection(currentMove.selected));

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
}

void Game::performUserInput() {
	b->movePiece(currentMove);

	if (earnedPromotion(currentMove))
		b->promotePiece(currentMove.target);

	if (b->isCapture(currentMove)) {
		b->capturePiece(currentMove);

		activeCapture = true;
		activeCapture = pieceHasMoves(currentMove.target);
		b->printBoard(blacksTurn);
	}
}

bool Game::earnedPromotion(move m) {
	if (b->isKing(m.target))
		return false;

	return (blacksTurn && m.target.y == 7) || (!blacksTurn && m.target.y == 0);
}

bool Game::evalWinConditions() {
	bool blackCanMove = false;
	bool whiteCanMove = false;
	cords c;

	for (int i = 0; i < 8; i++) {

		for (int j = 0; j < 8; j++) {

			c = { j, i };

			if (b->isPiece(c)) {
				calculateAllPossibleMovesForPiece(c);

				if (possibleMoves.size() > 0) {

					if (b->isBlack(c))
						blackCanMove = true;
					else
						whiteCanMove = true;
				}
			}
		}
	}

	return (!blackCanMove && blacksTurn) || (!whiteCanMove && !blacksTurn);
}

// Getters
Board* Game::getBoard() {
	return b;
}

move Game::getCurrentMove() {
	return currentMove;
}

bool Game::isBlacksTurn() {
	return blacksTurn;
}

bool Game::isCurrentlyActiveCapture() {
	return activeCapture;
}

int Game::getCurrentNumberOfPossibleMoves() {
	return possibleMoves.size();
}

const std::vector<cords> Game::getCachedPossibleMoves() {
	return possibleMoves;
}

// Setters
void Game::setCurrentMove(move m) {
	currentMove = m;
}

void Game::setCaptureState(bool newState) {
	activeCapture = newState;
}

void Game::addPossibleMove(cords possibleTarget) {
	possibleMoves.push_back(possibleTarget);
}

void Game::clearPossibleMoves() {
	possibleMoves.clear();
}

void Game::nextTurn() {
	blacksTurn = !blacksTurn;
}