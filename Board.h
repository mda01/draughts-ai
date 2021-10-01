//
// Created by mdano on 22/09/2021.
//

#ifndef QTTEST_BOARD_H
#define QTTEST_BOARD_H

#include <vector>
#include <iostream>

using namespace std;

class Coordinate {
public:
    int x, y;

    static bool is_valid(int x, int y) {
        return x >= 0 && x <= 9 && y >= 0 && y <= 9;
    };
};

class Board {
private:
    /**
     * x
     * ^
     * |
     * |
     * |
     * |
     * |
     * ------------------------> y
     */
    vector<vector<int>> grid; // 0 empty 1 white 2 black 3 white queen 4 black queen
    int nb_turn;
    bool turn; // true -> white to play

    int nb_white_pawns, nb_black_pawns;

    bool chain_eat;
    Coordinate pawn_chain{0, 0};

    void init_grid();

    [[nodiscard]] bool is_free(const int &x, const int &y) const { return !grid[x][y]; }

    [[nodiscard]] pair<bool, vector<Coordinate>> possible_moves(const Coordinate &piece) const;

public:
    Board() {
        turn = true;
        nb_turn = 0;
        init_grid();
        nb_white_pawns = 20;
        nb_black_pawns = 20;
        chain_eat = false;
    }

    Board(const Board &b) {
        grid = vector<vector<int>>(b.grid);
        turn = b.turn;
        nb_turn = b.nb_turn;
        nb_white_pawns = b.nb_white_pawns;
        nb_black_pawns = b.nb_black_pawns;
        chain_eat = b.chain_eat;
        pawn_chain = b.pawn_chain;
    }


    [[nodiscard]] vector<vector<int>> get_grid() const { return grid; };

    void print_grid() const;

    void print_state() const;

    [[nodiscard]] vector<pair<Coordinate, Coordinate>> get_moves() const;

    void play_move(const Coordinate &start, const Coordinate &end);

    [[nodiscard]] bool is_over() const;

    [[nodiscard]] int heuristic() const;
};


#endif //QTTEST_BOARD_H
