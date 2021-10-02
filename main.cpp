#include <QApplication>
#include <QWindow>
#include "basewindow.h"
#include "board.h"
#include "minMax.h"


void playMove(board &b, const minMax &ai) {
    vector<pair<coordinate, coordinate>> actions;
    int confidence = ai.alphaBeta(b, actions);
    auto action = actions.front();
    b.playMove(action.first, action.second);
    cout << "Played " << board::coordToTile(action.first) << " -> "
         << board::coordToTile(action.second) << " (confidence: " << confidence << ")" << endl;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    board b{};
    minMax mwhite(true);
    minMax mblack(false);
    vector<pair<coordinate, coordinate>> actions;
    while (!b.isOver()) {
//    while (false) {
        b.printState();
        if (b.getTurn()) {
            playMove(b, mwhite);
        } else {
            int start, end;
            //cin >> start >> end;
            //b.playMove(board::tileToCoord(start), board::tileToCoord(end));
            playMove(b, mblack);
        }
    }
    baseWindow bw;
    bw.show();
    return QApplication::exec();
}
