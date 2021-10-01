#include <QApplication>
#include <QPushButton>
#include "board.h"
#include "minMax.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    board b{};
    minMax m(false);
    minMax m2(true);
    vector<pair<coordinate, coordinate>> actions;
    b.printState();
    while (!b.isOver()){
        //int startx, starty, endx, endy;
        //cin >> startx >> starty >> endx >> endy;
        //b.playMove(coordinate{startx, starty}, coordinate{endx, endy});

        if (b.getTurn()) {
            m2.alphaBeta(b, actions);
            b.playMove(actions.front().first, actions.front().second);
            b.printState();
        } else {
            m.alphaBeta(b, actions);
            b.playMove(actions.front().first, actions.front().second);
            b.printState();
        }
    }
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
