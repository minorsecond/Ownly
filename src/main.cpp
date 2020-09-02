#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include "Database.h"
#include "main.h"
#include <string>
#include <vector>
#include <cmath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(1053, 520);
    QHeaderView* header = ui.inventoryList->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);

    ui.deleteItemButton->setDisabled(true);

    QDate date = QDate::currentDate();
    ui.ItemPurchaseDate->setDate(date);

    QPalette pal = ui.deleteItemButton->palette();
    pal.setColor(QPalette::Button, QColor(255, 99, 71));
    ui.deleteItemButton->setAutoFillBackground(true);
    ui.deleteItemButton->setPalette(pal);
    ui.deleteItemButton->update();

    QItemSelectionModel *sm = ui.inventoryList->selectionModel();

    // Slots
    connect(ui.inventoryList->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(table_row_clicked(const QItemSelection &, const QItemSelection &)));
    connect(ui.actionClear_Data, SIGNAL(triggered()), this, SLOT(truncate_db()));
    connect(ui.deleteItemButton, SIGNAL(clicked()), this, SLOT(remove_row()));
    connect(ui.dbSubmitButton, SIGNAL(clicked()), this, SLOT(clicked_submit()));
    connect(ui.NewItemButton, SIGNAL(clicked()), this, SLOT(new_item()));

    updateMainTable();
}

std::string MainWindow::double_to_string(double input_double) {
    double purchase_price = std::ceil(input_double * 100.0) / 100.0;
    std::ostringstream price_stream;
    price_stream << purchase_price;

    return price_stream.str();
}

void MainWindow::clicked_submit(){
    Database db;
    QMessageBox error_message;
    std::cout << "Clicked dbSubmitButton" << std::endl;

    std::string item_name = ui.ItemName->text().toUtf8().constData();
    std::string item_category = ui.ItemCategory->currentText().toUtf8().constData();
    std::string item_price_string = ui.ItemPurchasePrice->text().toUtf8().constData();
    double item_price;
    std::string item_count_str = ui.ItemCount->text().toUtf8().constData();
    bool usedInLastSixMonths = ui.ItemUsedInLastSixMonths->isChecked();
    std::string notes = ui.ItemNotes->toPlainText().toUtf8().constData();
    int purchase_year = ui.ItemPurchaseDate->date().year();
    int purchase_month = ui.ItemPurchaseDate->date().month();
    int purchase_day = ui.ItemPurchaseDate->date().day();

    // Handle blank item counts that may happen if user uses the new item button.
    int item_count;
    if (!item_count_str.empty())
        item_count = std::stoi(ui.ItemCount->text().toUtf8().constData());
    else
        item_count = 0;

    if (item_price_string.empty())
        item_price = 0.00;
    else
        item_price = std::stod(item_price_string);

    if(item_name.empty() || item_category.empty() || item_count == 0){
        error_message.critical(0, "Error", "Please enter item name, category, and count.");
        error_message.setFixedSize(200, 200);
    } else {
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
        updateMainTable();
    }
}

void MainWindow::updateMainTable() {
    Database db;
    std::vector<Item> items = db.read("ownly.db");

    int current_row = 0;

    ui.inventoryList->setRowCount(items.size());
    ui.inventoryList->setColumnCount(7);
    ui.inventoryList->setColumnHidden(6, true);

    for(const auto& entry : items) {
        auto *name = new QTableWidgetItem(entry.itemName.c_str());
        auto *category = new QTableWidgetItem(entry.category.c_str());
        int purchase_year = entry.purchaseYear;
        int purchase_month = entry.purchaseMonth;
        int purchase_day = entry.purchaseDay;
        auto *item_count = new QTableWidgetItem(std::to_string(entry.count).c_str());
        bool usedInLastSixMonths = entry.usedInLastSixMonths;
        auto *id = new QTableWidgetItem(std::to_string(entry.id).c_str());
        QTableWidgetItem *used_recently;

        // Limit prices on table to two digits
        std::string purchase_price = double_to_string(entry.purchasePrice);
        //double purchase_price = std::ceil(entry.purchasePrice * 100.0) / 100.0;
        //std::ostringstream price_stream;
        //price_stream << purchase_price;
        auto *purchase_price_str = new QTableWidgetItem(purchase_price.c_str());


        std::string date = std::to_string(purchase_year) + "/" + std::to_string(purchase_month) + "/" + std::to_string(purchase_day);
        auto *date_qtwi = new QTableWidgetItem(date.c_str());

        if(usedInLastSixMonths) {
            used_recently = new QTableWidgetItem("Yes");
        } else {
            used_recently = new QTableWidgetItem("No");
        }

        std::string notes = entry.notes;

        ui.inventoryList->setItem(current_row, 0, name);
        ui.inventoryList->setItem(current_row, 1, category);
        ui.inventoryList->setItem(current_row, 2, date_qtwi);
        ui.inventoryList->setItem(current_row, 3, purchase_price_str);
        ui.inventoryList->setItem(current_row, 4, item_count);
        ui.inventoryList->setItem(current_row, 5, used_recently);
        ui.inventoryList->setItem(current_row, 6, id);

        current_row +=1;
    }
}

void MainWindow::truncate_db() {
    Database db;
    std::cout << "Truncate db clicked." << std::endl;
    Storage storage = initStorage("ownly.db");
    db.truncate(storage);
    updateMainTable();
}

void MainWindow::remove_row() {
    std::cout << "CLicked remove row" << std::endl;

    Database db;
    Storage storage = initStorage("ownly.db");

    // Get selected row
    int select = ui.inventoryList->selectionModel()->currentIndex().row();
    std::cout << "Selected row: " << select << std::endl;
    //select->hasSelection();
    //QModelIndexList selected_rows = select->selectedRows();

    //for(int i=0; i<selected_rows.count(); i++) {
    //    int index = selected_rows.at(i).data().toString().toInt();
    //    std::cout << "DB index to delete: " << index << std::endl;
    //    qDebug() << "Deleting DB row at index " << ui.inventoryList->item(index, 6)->text();
    //}

    int row_to_delete = (ui.inventoryList->item(select, 6)->text()).toUtf8().toInt();

    std::cout << "Deleting DB row at index " << row_to_delete << std::endl;
    db.deleteRow(storage, row_to_delete);
    updateMainTable();
}

void MainWindow::table_row_clicked(const QItemSelection &, const QItemSelection &) {
    Database db;
    Storage storage = initStorage("ownly.db");

    QItemSelectionModel *select = ui.inventoryList->selectionModel();

    int selection = ui.inventoryList->selectionModel()->currentIndex().row();
    int row_to_get = ui.inventoryList->item(selection, 6)->text().toUtf8().toInt();

    if(select->isRowSelected(selection))
        ui.deleteItemButton->setEnabled(true);
    else
        ui.deleteItemButton->setDisabled(true);

    Item item = db.read_row(storage, row_to_get);

    int id = item.id;
    std::string item_name = item.itemName;
    std::string item_category = item.category;
    int purchase_year = item.purchaseYear;
    int purchase_month = item.purchaseMonth;
    int purchase_day = item.purchaseDay;
    std::string purchase_price = double_to_string(item.purchasePrice);
    int count = item.count;
    bool usedInLastSixMonths = item.usedInLastSixMonths;

    std::string date_from_db = std::to_string(purchase_day) + "/" + std::to_string(purchase_month) + "/" + std::to_string(purchase_year);
    QDate date = QDate::fromString(QString::fromUtf8(date_from_db.c_str()), "dd/MM/yyyy");

    ui.ItemName->setText(QString::fromStdString(item_name));
    ui.ItemCategory->setCurrentText(QString::fromStdString(item_category));
    ui.ItemPurchaseDate->setDate(date);
    ui.ItemPurchasePrice->setText(QString::fromStdString(purchase_price.c_str()));
    ui.ItemCount->setValue(count);

    if(usedInLastSixMonths == true)
        ui.ItemUsedInLastSixMonths->setChecked(true);
    else
        ui.ItemUsedInLastSixMonths->setChecked(false);
}

void MainWindow::new_item() {
    ui.ItemName->clear();
    ui.ItemCategory->clearEditText();
    QDate date = QDate::currentDate();
    ui.ItemPurchaseDate->setDate(date);
    ui.ItemPurchasePrice->clear();
    ui.ItemCount->clear();
    ui.ItemUsedInLastSixMonths->setChecked(false);
    ui.ItemNotes->clear();
}

int main(int argc, char** argv) {
    Database db;
    initStorage("ownly.db");

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();

    return 0;
}
