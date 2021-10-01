#include <QApplication>
#include <QPushButton>
#include "Board.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    Board b{};
    while (!b.is_over()) {
        b.print_state();
        for (auto &move: b.get_moves()) {
            cout << move.first.x << " " << move.first.y << " -> " << move.second.x << " " << move.second.y << endl;
        }
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        b.play_move(Coordinate{startx, starty}, Coordinate{endx, endy});
    }
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
