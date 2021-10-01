#include <QApplication>
#include <QPushButton>
#include "board.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    board b{};
    while (!b.isOver()) {
        b.printState();
        for (auto &move: b.getMoves()) {
            cout << move.first.x << " " << move.first.y << " -> " << move.second.x << " " << move.second.y << endl;
        }
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        b.playMove(coordinate{startx, starty}, coordinate{endx, endy});
    }
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
