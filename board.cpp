//
// Created by mdano on 22/09/2021.
//

#include "board.h"

void board::initGrid() {
    grid = vector<vector<int>>(10, vector<int>(10, 0));
    grid[0] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    grid[2] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    grid[1] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};
    grid[3] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0};

    grid[6] = {0, 2, 0, 2, 0, 2, 0, 2, 0, 2};
    grid[8] = {0, 2, 0, 2, 0, 2, 0, 2, 0, 2};
    grid[7] = {2, 0, 2, 0, 2, 0, 2, 0, 2, 0};
    grid[9] = {2, 0, 2, 0, 2, 0, 2, 0, 2, 0};

}


void board::printGrid() const {
    for (int i = 9; i >= 0; i--) {
        for (auto &y : grid[i]) {
            cout << y << " ";
        }
        cout << endl;
    }
}

void board::printState() const {
    cout << "Tour n°" << nbTurn << endl;
    cout << "Blanc a " << nbWhitePawns << " pions et Noir en a " << nbBlackPawns << endl;
    cout << (turn ? "Blanc" : "Noir") << " va jouer" << endl;
    cout << "--------------------" << endl;
    this->printGrid();
    cout << "--------------------" << endl;
    for (auto &move: getMoves()) {
        cout << move.first.x << " " << move.first.y << " -> " << move.second.x << " " << move.second.y << endl;
    }

}

pair<bool, vector<coordinate>> board::possibleMoves(const coordinate &piece) const {
    if (grid[piece.x][piece.y] == 0)
        return make_pair(false, vector<coordinate>());
    vector<coordinate> moves;
    vector<coordinate> eatMoves;
    int x = piece.x, y = piece.y;
    bool canEat = false;
    if (grid[x][y] == 1) { // white pawn
        // if an enemy piece is in front or behind us && there is space behind it -> must take it
        if (coordinate::isValid(x + 2, y - 2) && isFree(x + 2, y - 2) &&
            (grid[x + 1][y - 1] == 2 || grid[x + 1][y - 1] == 4)) {
            canEat = true;
            eatMoves.push_back(coordinate{x + 2, y - 2});
        }
        if (coordinate::isValid(x + 2, y + 2) && isFree(x + 2, y + 2) &&
            (grid[x + 1][y + 1] == 2 || grid[x + 1][y + 1] == 4)) {
            canEat = true;
            eatMoves.push_back(coordinate{x + 2, y + 2});
        }
        if (coordinate::isValid(x - 2, y + 2) && isFree(x - 2, y + 2) &&
            (grid[x - 1][y + 1] == 2 || grid[x - 1][y + 1] == 4)) {
            canEat = true;
            eatMoves.push_back(coordinate{x - 2, y + 2});
        }
        if (coordinate::isValid(x - 2, y - 2) && isFree(x - 2, y - 2) &&
            (grid[x - 1][y - 1] == 2 || grid[x - 1][y - 1] == 4)) {
            canEat = true;
            eatMoves.push_back(coordinate{x - 2, y - 2});
        }
        if (!canEat) {
            // if there is a free space, you can advance
            if (coordinate::isValid(x + 1, y - 1) && isFree(x + 1, y - 1))
                moves.push_back(coordinate{x + 1, y - 1});
            if (coordinate::isValid(x + 1, y + 1) && isFree(x + 1, y + 1))
                moves.push_back(coordinate{x + 1, y + 1});
        }
    } else if (grid[x][y] == 2) { // black pawn
        // if an enemy piece is in front or behind us && there is space behind it -> must take it
        if (coordinate::isValid(x + 2, y - 2) && isFree(x + 2, y - 2) &&
            grid[x + 1][y - 1] & 1) {
            canEat = true;
            eatMoves.push_back(coordinate{x + 2, y - 2});
        }
        if (coordinate::isValid(x + 2, y + 2) && isFree(x + 2, y + 2) &&
            grid[x + 1][y + 1] & 1) {
            canEat = true;
            eatMoves.push_back(coordinate{x + 2, y + 2});
        }
        if (coordinate::isValid(x - 2, y + 2) && isFree(x - 2, y + 2) &&
            grid[x - 1][y + 1] & 1) {
            canEat = true;
            eatMoves.push_back(coordinate{x - 2, y + 2});
        }
        if (coordinate::isValid(x - 2, y - 2) && isFree(x - 2, y - 2) &&
            grid[x - 1][y - 1] & 1) {
            canEat = true;
            eatMoves.push_back(coordinate{x - 2, y - 2});
        }
        if (!canEat) {
            // if there is a free space, you can advance
            if (coordinate::isValid(x - 1, y - 1) && isFree(x - 1, y - 1))
                moves.push_back(coordinate{x - 1, y - 1});
            if (coordinate::isValid(x - 1, y + 1) && isFree(x - 1, y + 1))
                moves.push_back(coordinate{x - 1, y + 1});
        }
    } else if (grid[x][y] == 3) { // white draught
        // pain is starting
        bool blocked = false;
        int i;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x + i, y + i)) {
                if (isFree(x + i, y + i)) {
                    moves.emplace_back(coordinate{x + i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x + (i + 1), y + (i + 1)) && isFree(x + (i + 1), y + (i + 1)) &&
            (grid[x + i][y + i] & 1) == 0) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x + (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x - i, y + i)) {
                if (isFree(x - i, y + i)) {
                    moves.emplace_back(coordinate{x - i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x - (i + 1), y + (i + 1)) && isFree(x - (i + 1), y + (i + 1)) &&
            (grid[x - i][y + i] & 1) == 0) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x - (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x + i, y - i)) {
                if (isFree(x + i, y - i)) {
                    moves.emplace_back(coordinate{x + i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x + (i + 1), y - (i + 1)) && isFree(x + (i + 1), y - (i + 1)) &&
            (grid[x + i][y - i] & 1) == 0) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x + (i + 1), y - (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x - i, y - i)) {
                if (isFree(x - i, y - i)) {
                    moves.emplace_back(coordinate{x - i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x - (i + 1), y - (i + 1)) && isFree(x - (i + 1), y - (i + 1)) &&
            (grid[x - i][y - i] & 1) == 0) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x - (i + 1), y - (i + 1)});
        }
    }else if (grid[x][y] == 4) { // black draught
        bool blocked = false;
        int i;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x + i, y + i)) {
                if (isFree(x + i, y + i)) {
                    moves.emplace_back(coordinate{x + i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x + (i + 1), y + (i + 1)) && isFree(x + (i + 1), y + (i + 1)) &&
            (grid[x + i][y + i] & 1)) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x + (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x - i, y + i)) {
                if (isFree(x - i, y + i)) {
                    moves.emplace_back(coordinate{x - i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x - (i + 1), y + (i + 1)) && isFree(x - (i + 1), y + (i + 1)) &&
            (grid[x - i][y + i] & 1)) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x - (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x + i, y - i)) {
                if (isFree(x + i, y - i)) {
                    moves.emplace_back(coordinate{x + i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x + (i + 1), y - (i + 1)) && isFree(x + (i + 1), y - (i + 1)) &&
            (grid[x + i][y - i] & 1)) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x + (i + 1), y - (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (coordinate::isValid(x - i, y - i)) {
                if (isFree(x - i, y - i)) {
                    moves.emplace_back(coordinate{x - i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && coordinate::isValid(x - (i + 1), y - (i + 1)) && isFree(x - (i + 1), y - (i + 1)) &&
            (grid[x - i][y - i] & 1)) {
            canEat = true;
            eatMoves.emplace_back(coordinate{x - (i + 1), y - (i + 1)});
        }
    }
    return make_pair(canEat, canEat ? eatMoves : moves);
}

vector<pair<coordinate, coordinate>> board::getMoves() const {
    vector<pair<coordinate, coordinate>> moves, eatMoves;
    if (chainEat) {
        auto move = possibleMoves(pawnChain);
        for (auto &m: move.second) {
            eatMoves.emplace_back(pawnChain, m);
        }
        return eatMoves;
    }
    bool canEat = false;
    if (turn) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                if (grid[x][y] & 1) {
                    coordinate tile{x, y};
                    auto move = possibleMoves(tile);
                    if (move.first) {
                        canEat = true;
                        for (auto &m : move.second) {
                            eatMoves.emplace_back(tile, m);
                        }
                    } else {
                        if (!canEat) {
                            for (auto &m: move.second) {
                                moves.emplace_back(tile, m);
                            }
                        }
                    }
                }
            }
        }
    } else {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                if (grid[x][y] == 2 || grid[x][y] == 4) {
                    coordinate tile{x, y};
                    auto move = possibleMoves(tile);
                    if (move.first) {
                        canEat = true;
                        for (auto &m : move.second) {
                            eatMoves.emplace_back(tile, m);
                        }
                    } else {
                        if (!canEat) {
                            for (auto &m: move.second) {
                                moves.emplace_back(tile, m);
                            }
                        }
                    }
                }
            }
        }
    }
    return canEat ? eatMoves : moves;
}

void board::playMove(const coordinate &start, const coordinate &end) {
    // get pos of possible piece eaten (or start if it's a pawn move)
    int x = end.x - (end.x - start.x) / abs(end.x - start.x);
    int y = end.y - (end.y - start.y) / abs(end.y - start.y);
    // if the case where something could be eaten is free, or if this case is actually the start -> it's a move
    bool moving = x == start.x || isFree(x, y);
    if (moving) { // moving
        grid[end.x][end.y] = grid[start.x][start.y];
        grid[start.x][start.y] = 0;
        // transformation?
        if (end.x == 9 && grid[end.x][end.y] == 1) { // white draught
            grid[end.x][end.y] = 3;
        } else if (end.x == 0 && grid[end.x][end.y] == 2) { // black draught
            grid[end.x][end.y] = 4;
        }
        turn = !turn;
        nbTurn++;
    } else { // eating
        // remove a pawn
        if (grid[x][y] & 1) {
            nbWhitePawns--;
        } else {
            nbBlackPawns--;
        }
        grid[x][y] = 0;
        // move piece
        grid[end.x][end.y] = grid[start.x][start.y];
        grid[start.x][start.y] = 0;
        // transformation?
        if (end.x == 9 && grid[end.x][end.y] == 1) { // white draught
            grid[end.x][end.y] = 3;
        } else if (end.x == 0 && grid[end.x][end.y] == 2) { // black draught
            grid[end.x][end.y] = 4;
        }
        // chain eat?
        auto nextMoves = possibleMoves(end);
        if (nextMoves.first) {
            chainEat = true;
            pawnChain = end;
        } else {
            chainEat = false;
            turn = !turn;
            nbTurn++;
        }
    }
}

bool board::isOver() const {
    return !(nbWhitePawns && nbBlackPawns);
}

int board::heuristic(bool color) const {
    int h;
    if (nbWhitePawns == 0) {
        h = -100;
    } else if (nbBlackPawns == 0) {
        h = 100;
    } else {
        h = nbWhitePawns - nbBlackPawns;
    }
    if (!color) h = -h;
    return h;
}

vector<pair<pair<coordinate, coordinate>, board>> board::children() const {
    vector<pair<pair<coordinate, coordinate>, board>> children;
    for (auto &move: getMoves()) {
        board b(*this);
        b.playMove(move.first, move.second);
        children.emplace_back(move, b);
    }
    return children;
}

bool board::getTurn() const {
    return turn;
}

bool board::isChainEat() const {
    return chainEat;
}
