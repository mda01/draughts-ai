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

void Board::print_grid() {
    for (int i = 9; i >= 0; i--) {
        for (auto &y : grid[i]) {
            cout << y << " ";
        }
        cout << endl;
    }
}

void Board::print_state() {
    cout << "Tour n°" << nb_turn << endl;
    cout << (turn ? "blanc" : "noir") << " à jouer" << endl;
    cout << "--------------------" << endl;
    this->print_grid();
    cout << "--------------------" << endl;

}

pair<bool, vector<Coordinate>> Board::possible_moves(const Coordinate &piece) {
    if (grid[piece.x][piece.y] == 0)
        return make_pair(false, vector<Coordinate>());
    vector<Coordinate> moves;
    vector<Coordinate> eat_moves;
    int x = piece.x, y = piece.y;
    bool can_eat = false;
    if (grid[x][y] == 1) { // white piece
        // if an enemy piece is in front or behind us && there is space behind it -> must take it
        // TODO

        if(!can_eat) {
            // if there is a free space, you can advance
            if (Coordinate::is_valid(x + 1, y - 1) && is_free(x + 1, y - 1))
                moves.push_back(Coordinate{x + 1, y - 1});
            if (Coordinate::is_valid(x + 1, y + 1) && is_free(x + 1, y + 1))
                moves.push_back(Coordinate{piece.x + 1, piece.y + 1});
        }
    }
    return make_pair(can_eat, can_eat?eat_moves:moves);
}
