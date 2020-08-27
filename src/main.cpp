#include <iostream>
#include <QApplication>
#include "MainWindow.h"
#include "Database.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(800, 537);
    // connect(ui.db_submit_button, SIGNAL(clicked()), this, SLOT(clicked_submit()));
}

void MainWindow::clicked_submit(){
    // Do something
}

int main(int argc, char** argv) {
    Database db;
    db.open_or_create("db.sqlite");

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();

    return 0;
}
