#include <iostream>
#include <QApplication>
#include "MainWindow.h"
#include "Database.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(800, 537);

    std::string item_name;
    std::string item_category;
    double item_price;
    int purchaseYear;
    int purchaseMonth;
    int purchaseDay;
    int itemCount;
    bool usedInLastSixMonths;
    std::string notes;

    connect(ui.dbSubmitButton, SIGNAL(clicked()), this, SLOT(clicked_submit()));
}

void MainWindow::clicked_submit(){
    std::cout << "Clicked dbSubmitButton" << std::endl;
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
