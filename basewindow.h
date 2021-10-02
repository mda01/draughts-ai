//
// Created by mdano on 10/2/21.
//

#ifndef QTTEST_BASEWINDOW_H
#define QTTEST_BASEWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class baseWindow; }
QT_END_NAMESPACE

class baseWindow : public QWidget {
Q_OBJECT

public:
    explicit baseWindow(QWidget *parent = nullptr);

    ~baseWindow() override;

private:
    Ui::baseWindow *ui;
};

#endif //QTTEST_BASEWINDOW_H
