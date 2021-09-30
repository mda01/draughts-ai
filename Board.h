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

    void init_grid();

    bool is_free(int x, int y) { return !grid[x][y]; }

    pair<bool, vector<Coordinate>> possible_moves(const Coordinate& piece);

public:
    Board() {
        turn = true;
        nb_turn = 0;
        init_grid();
    }

    Board(const Board &b) {
        grid = vector<vector<int>>(b.grid);
        turn = b.turn;
        nb_turn = b.nb_turn;
    }

    bool turn; // true -> white to play

    vector<vector<int>> get_grid() { return grid; };

    void print_grid();

    void print_state();

    vector<pair<Coordinate, Coordinate>> get_moves();

    void play_move(Coordinate start, Coordinate end);
};


#endif //QTTEST_BOARD_H
