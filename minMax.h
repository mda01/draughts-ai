//
// Created by mdano on 10/1/21.
//

#ifndef QTTEST_MINMAX_H
#define QTTEST_MINMAX_H


#include "board.h"

#define MAX_DEPTH 10

class minMax {
private:
    bool aiColor;

public:
    /**
     * Creates a minmax AI, that maximise the @param color score
     * @param color the player we want to maximise
     */
    explicit minMax(bool color);

    /**
     * Starts the minmax algorithm and uses alpha beta pruning, from a @param state, and memorises the best
     * path into @param actions
     * @param state the initial state
     * @param actions the path
     * @return the confidence of the AI as int
     */
    int alphaBeta(const board &state, vector<pair<coordinate, coordinate>> &actions) const;

    /**
     * Tries to maximize the score
     * @param state initial state
     * @param alpha alpha bound
     * @param beta beta bound
     * @param actions best path
     * @param depth how far we can explore from this state
     * @return the confidence of the AI as int
     */
    int
    maxValue(const board &state, int alpha, int beta, vector<pair<coordinate, coordinate>> &actions, int depth) const;

    /**
     * Tries to minimize the score
     * @param state initial state
     * @param alpha alpha bound
     * @param beta beta bound
     * @param actions best path
     * @param depth how far we can explore from this state
     * @return the confidence of the AI as int
     */
    int
    minValue(const board &state, int alpha, int beta, vector<pair<coordinate, coordinate>> &actions, int depth) const;


};


#endif //QTTEST_MINMAX_H
