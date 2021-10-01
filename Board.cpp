//
// Created by mdano on 22/09/2021.
//

#include "Board.h"

void Board::init_grid() {
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


void Board::print_grid() const {
    for (int i = 9; i >= 0; i--) {
        for (auto &y : grid[i]) {
            cout << y << " ";
        }
        cout << endl;
    }
}

void Board::print_state() const {
    cout << "Tour n°" << nb_turn << endl;
    cout << (turn ? "Blanc" : "Noir") << " va jouer" << endl;
    cout << "--------------------" << endl;
    this->print_grid();
    cout << "--------------------" << endl;

}

pair<bool, vector<Coordinate>> Board::possible_moves(const Coordinate &piece) const {
    if (grid[piece.x][piece.y] == 0)
        return make_pair(false, vector<Coordinate>());
    vector<Coordinate> moves;
    vector<Coordinate> eat_moves;
    int x = piece.x, y = piece.y;
    bool can_eat = false;
    if (grid[x][y] == 1) { // white pawn
        // if an enemy piece is in front or behind us && there is space behind it -> must take it
        if (Coordinate::is_valid(x + 2, y - 2) && is_free(x + 2, y - 2) &&
            (grid[x + 1][y - 1] == 2 || grid[x + 1][y - 1] == 4)) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x + 2, y - 2});
        }
        if (Coordinate::is_valid(x + 2, y + 2) && is_free(x + 2, y + 2) &&
            (grid[x + 1][y + 1] == 2 || grid[x + 1][y + 1] == 4)) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x + 2, y + 2});
        }
        if (Coordinate::is_valid(x - 2, y + 2) && is_free(x - 2, y + 2) &&
            (grid[x - 1][y + 1] == 2 || grid[x - 1][y + 1] == 4)) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x - 2, y + 2});
        }
        if (Coordinate::is_valid(x - 2, y - 2) && is_free(x - 2, y - 2) &&
            (grid[x - 1][y - 1] == 2 || grid[x - 1][y - 1] == 4)) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x - 2, y - 2});
        }
        if (!can_eat) {
            // if there is a free space, you can advance
            if (Coordinate::is_valid(x + 1, y - 1) && is_free(x + 1, y - 1))
                moves.push_back(Coordinate{x + 1, y - 1});
            if (Coordinate::is_valid(x + 1, y + 1) && is_free(x + 1, y + 1))
                moves.push_back(Coordinate{x + 1, y + 1});
        }
    } else if (grid[x][y] == 2) { // black pawn
        // if an enemy piece is in front or behind us && there is space behind it -> must take it
        if (Coordinate::is_valid(x + 2, y - 2) && is_free(x + 2, y - 2) &&
            grid[x + 1][y - 1] & 1) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x + 2, y - 2});
        }
        if (Coordinate::is_valid(x + 2, y + 2) && is_free(x + 2, y + 2) &&
            grid[x + 1][y + 1] & 1) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x + 2, y + 2});
        }
        if (Coordinate::is_valid(x - 2, y + 2) && is_free(x - 2, y + 2) &&
            grid[x - 1][y + 1] & 1) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x - 2, y + 2});
        }
        if (Coordinate::is_valid(x - 2, y - 2) && is_free(x - 2, y - 2) &&
            grid[x - 1][y - 1] & 1) {
            can_eat = true;
            eat_moves.push_back(Coordinate{x - 2, y - 2});
        }
        if (!can_eat) {
            // if there is a free space, you can advance
            if (Coordinate::is_valid(x - 1, y - 1) && is_free(x - 1, y - 1))
                moves.push_back(Coordinate{x - 1, y - 1});
            if (Coordinate::is_valid(x - 1, y + 1) && is_free(x - 1, y + 1))
                moves.push_back(Coordinate{x - 1, y + 1});
        }
    } else if (grid[x][y] == 3) { // white draught
        // pain is starting
        bool blocked = false;
        int i;
        for (i = 1; i <= 9; i++) {
            if (Coordinate::is_valid(x + i, y + i)) {
                if (is_free(x + i, y + i)) {
                    moves.emplace_back(Coordinate{x + i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && Coordinate::is_valid(x + (i + 1), y + (i + 1)) && is_free(x + (i + 1), y + (i + 1)) &&
            (grid[x + i][y + i] & 1) == 0) {
            can_eat = true;
            eat_moves.emplace_back(Coordinate{x + (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (Coordinate::is_valid(x - i, y + i)) {
                if (is_free(x - i, y + i)) {
                    moves.emplace_back(Coordinate{x - i, y + i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && Coordinate::is_valid(x - (i + 1), y + (i + 1)) && is_free(x - (i + 1), y + (i + 1)) &&
            (grid[x - i][y + i] & 1) == 0) {
            can_eat = true;
            eat_moves.emplace_back(Coordinate{x - (i + 1), y + (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (Coordinate::is_valid(x + i, y - i)) {
                if (is_free(x + i, y - i)) {
                    moves.emplace_back(Coordinate{x + i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && Coordinate::is_valid(x + (i + 1), y - (i + 1)) && is_free(x + (i + 1), y - (i + 1)) &&
            (grid[x + i][y - i] & 1) == 0) {
            can_eat = true;
            eat_moves.emplace_back(Coordinate{x + (i + 1), y - (i + 1)});
        }
        blocked = false;
        for (i = 1; i <= 9; i++) {
            if (Coordinate::is_valid(x - i, y - i)) {
                if (is_free(x - i, y - i)) {
                    moves.emplace_back(Coordinate{x - i, y - i});
                } else {
                    blocked = true;
                    break;
                }
            } else {
                break;
            }
        }
        // if there is something blocking and there is space behind and the thing blocking is an enemy, eat
        if (blocked && Coordinate::is_valid(x - (i + 1), y - (i + 1)) && is_free(x - (i + 1), y - (i + 1)) &&
            (grid[x - i][y - i] & 1) == 0) {
            can_eat = true;
            eat_moves.emplace_back(Coordinate{x - (i + 1), y - (i + 1)});
        }
    }
    return make_pair(can_eat, can_eat ? eat_moves : moves);
}

vector<pair<Coordinate, Coordinate>> Board::get_moves() const {
    vector<pair<Coordinate, Coordinate>> moves, eat_moves;
    if (chain_eat) {
        auto move = possible_moves(pawn_chain);
        for (auto &m: move.second) {
            eat_moves.emplace_back(pawn_chain, m);
        }
        return eat_moves;
    }
    bool can_eat = false;
    if (turn) {
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                if (grid[x][y] & 1) {
                    Coordinate tile{x, y};
                    auto move = possible_moves(tile);
                    if (move.first) {
                        can_eat = true;
                        for (auto &m : move.second) {
                            eat_moves.emplace_back(tile, m);
                        }
                    } else {
                        if (!can_eat) {
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
                    Coordinate tile{x, y};
                    auto move = possible_moves(tile);
                    if (move.first) {
                        can_eat = true;
                        for (auto &m : move.second) {
                            eat_moves.emplace_back(tile, m);
                        }
                    } else {
                        if (!can_eat) {
                            for (auto &m: move.second) {
                                moves.emplace_back(tile, m);
                            }
                        }
                    }
                }
            }
        }
    }
    return can_eat ? eat_moves : moves;
}

void Board::play_move(const Coordinate &start, const Coordinate &end) {
    // get pos of possible piece eaten (or start if it's a pawn move)
    int x = end.x - (end.x - start.x) / abs(end.x - start.x);
    int y = end.y - (end.y - start.y) / abs(end.y - start.y);
    // if the case where something could be eaten in free, or if this case is actually the start -> it's a move
    bool moving = x == start.x || is_free(x, y);
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
        nb_turn++;
    } else { // eating

        // remove a pawn
        grid[x][y] & 1 ? nb_white_pawns : nb_black_pawns--;
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
        auto next_moves = possible_moves(end);
        if (next_moves.first) {
            chain_eat = true;
            pawn_chain = end;
        } else {
            chain_eat = false;
            turn = !turn;
            nb_turn++;
        }
    }
}

bool Board::is_over() const {
    return !(nb_white_pawns && nb_black_pawns);
}

int Board::heuristic() const {
    int h;
    if (nb_white_pawns == 0) {
        h = -100;
    } else if (nb_black_pawns == 0) {
        h = 100;
    } else {
        h = nb_white_pawns - nb_black_pawns;
    }
    if (!turn) h = -h;
    return h;
}
