#include <iostream>
#include "MainWindow.h"
#include "Database.h"

int open_main_window(int argc, char** argv) {
    QApplication app(argc, argv);
    QMainWindow mainWindow;
    QWidget widget;
    Ui::MainWindow ui;
    ui.setupUi(&mainWindow);

    mainWindow.show();
    return QApplication::exec();
}

int main(int argc, char** argv) {
    Database db;
    auto storage = db.open_or_create("db.sqlite");
    open_main_window(argc, argv);
    return 0;
}
