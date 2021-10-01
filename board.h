//
// Created by mdano on 22/09/2021.
//

#ifndef QTTEST_BOARD_H
#define QTTEST_BOARD_H

#include <vector>
#include <iostream>

using namespace std;

class coordinate {
public:
    int x, y;

    static bool isValid(int x, int y) {
        return x >= 0 && x <= 9 && y >= 0 && y <= 9;
    };
};

class board {
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
    int nbTurn;
    bool turn; // true -> white to play

    int nbWhitePawns, nbBlackPawns;

    bool chainEat;
    coordinate pawnChain{0, 0};

    void initGrid();

    [[nodiscard]] bool isFree(const int &x, const int &y) const { return !grid[x][y]; }

    [[nodiscard]] pair<bool, vector<coordinate>> possibleMoves(const coordinate &piece) const;

public:
    board() {
        turn = true;
        nbTurn = 0;
        initGrid();
        nbWhitePawns = 20;
        nbBlackPawns = 20;
        chainEat = false;
    }

    board(const board &b) {
        grid = vector<vector<int>>(b.grid);
        turn = b.turn;
        nbTurn = b.nbTurn;
        nbWhitePawns = b.nbWhitePawns;
        nbBlackPawns = b.nbBlackPawns;
        chainEat = b.chainEat;
        pawnChain = b.pawnChain;
    }


    [[nodiscard]] vector<vector<int>> getGrid() const { return grid; };

    void printGrid() const;

    void printState() const;

    [[nodiscard]] vector<pair<coordinate, coordinate>> getMoves() const;

    void playMove(const coordinate &start, const coordinate &end);

    [[nodiscard]] bool isOver() const;

    [[nodiscard]] int heuristic() const;
};


#endif //QTTEST_BOARD_H
