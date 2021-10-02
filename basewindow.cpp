//
// Created by mdano on 10/2/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_basewindow.h" resolved

#include "basewindow.h"
#include "ui_basewindow.h"

baseWindow::baseWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::baseWindow) {
    ui->setupUi(this);
}

baseWindow::~baseWindow() {
    delete ui;
}
