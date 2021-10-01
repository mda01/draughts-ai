//
// Created by mdano on 10/1/21.
//

#include "minMax.h"

minMax::minMax(bool color) {
    aiColor = color;
}

int minMax::alphaBeta(const board &state, vector<pair<coordinate, coordinate>> &actions) const {
    actions.clear();
    return maxValue(state, INT32_MIN, INT32_MAX, actions, MAX_DEPTH);
}

int minMax::maxValue(const board &state, int alpha, int beta, vector<pair<coordinate, coordinate>> &actions,
                     int depth) const {
    if (state.isOver()) return state.heuristic(aiColor);
    if (depth == 0) return state.heuristic(aiColor);
    auto children = state.children();
    int v = INT32_MIN;
    for (const auto &s : children) {
        vector<pair<coordinate, coordinate>> tmp;
        if(s.second.isChainEat()) depth++;
        int v2 = minValue(s.second, alpha, beta, tmp, depth - 1);
        if (v2 > v) {
            v = v2;
            actions = tmp;
            actions.insert(actions.begin(), s.first);
        }
        if (v >= beta) return v;
        alpha = max(alpha, v);
    }
    return v;
}

int minMax::minValue(const board &state, int alpha, int beta, vector<pair<coordinate, coordinate>> &actions,
                     int depth) const {
    if (state.isOver()) return state.heuristic(aiColor);
    if (depth == 0) return state.heuristic(aiColor);
    auto children = state.children();
    int v = INT32_MAX;
    for (const auto &s : children) {
        vector<pair<coordinate, coordinate>> tmp;
        int v2 = maxValue(s.second, alpha, beta, tmp, depth - 1);
        if (v2 < v) {
            v = v2;
            actions = tmp;
            actions.insert(actions.begin(), s.first);
        }
        if (v <= alpha) return v;
        beta = min(beta, v);
    }
    return v;
}
