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
    Database db;
    std::cout << "Clicked dbSubmitButton" << std::endl;

    std::string item_name = ui.ItemName->text().toUtf8().constData();
    std::string item_category = ui.ItemCategory->currentText().toUtf8().constData();
    std::string item_price_string = ui.ItemPurchasePrice->text().toUtf8().constData();
    double item_price;
    int item_count = std::stoi(ui.ItemCount->text().toUtf8().constData());
    bool usedInLastSixMonths = ui.ItemUsedInLastSixMonths->isChecked();
    std::string notes = ui.ItemCount->text().toUtf8().constData();
    int purchase_year = ui.ItemPurchaseDate->date().year();
    int purchase_month = ui.ItemPurchaseDate->date().month();
    int purchase_day = ui.ItemPurchaseDate->date().day();

    if (item_price_string.empty())
        item_price = 0.00;
    else
        item_price = std::stod(item_price_string);

    Item item{
        -1,
        item_name,
        item_category,
        purchase_year,
        purchase_month,
        purchase_day,
        item_price,
        item_count,
        usedInLastSixMonths,
        notes
    };

    db.write(item);
}

int main(int argc, char** argv) {
    Database db;
    db.open_or_create();

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();

    return 0;
}
