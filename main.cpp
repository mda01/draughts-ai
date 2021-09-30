#include <QApplication>
#include <QPushButton>
#include "Board.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    Board b{};
    b.print_state();
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
