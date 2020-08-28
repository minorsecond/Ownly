#include <iostream>
#include <QApplication>
#include "MainWindow.h"
#include "Database.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(800, 537);

    connect(ui.dbSubmitButton, SIGNAL(clicked()), this, SLOT(clicked_submit()));
}

void MainWindow::clicked_submit(){
    std::cout << "Clicked dbSubmitButton" << std::endl;

    std::string item_name = ui.ItemName->text().toUtf8().constData();
    std::string item_category = ui.ItemCategory->currentText().toUtf8().constData();
    std::string item_price_string = ui.ItemPurchasePrice->text().toUtf8().constData();
    double item_price;
    std::string purchase_date = ui.ItemPurchaseDate->text().toUtf8().constData();
    int item_count = std::stoi(ui.ItemCount->text().toUtf8().constData());
    bool usedInLastSixMonths = ui.ItemUsedInLastSixMonths->isChecked();
    std::string notes = ui.ItemCount->text().toUtf8().constData();

    if (item_price_string.empty())
        item_price = 0.00;
    else
        item_price = std::stod(item_price_string);

    std::cout << "Item price: " << item_price << std::endl;

    //Item item{
    //    -1,
    //    ui.ItemName->trUtf8().constData();
    //};
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
