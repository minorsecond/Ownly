#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include "MainWindow.h"
#include "ExportOptions.h"
#include "Database.h"
#include "main.h"
#include <string>
#include <vector>
#include <cmath>
#include "exporters.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) {
    /*
     * Main Window for program
     * @param parent: Parent QWidget object
     */

    ui.setupUi(this);
    this->setFixedSize(1053, 520);

    QHeaderView* header = ui.inventoryList->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);

    ui.deleteItemButton->setDisabled(true);
    ui.ViewCategoryComboBox->setDuplicatesEnabled(false);
    ui.ItemCategory->setDuplicatesEnabled(false);

    QDate date = QDate::currentDate();
    ui.ItemPurchaseDate->setDate(date);

    populate_categories();

    // Change the delete button color
    QPalette pal = ui.deleteItemButton->palette();
    pal.setColor(QPalette::Button, QColor(250, 180, 174));
    ui.deleteItemButton->setAutoFillBackground(true);
    ui.deleteItemButton->setPalette(pal);
    ui.deleteItemButton->update();

    // Slots
    connect(ui.inventoryList->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(table_row_clicked(const QItemSelection &, const QItemSelection &)));
    connect(ui.actionClear_Data, SIGNAL(triggered()), this, SLOT(truncate_db()));
    connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(open_export_dialog()));
    connect(ui.deleteItemButton, SIGNAL(clicked()), this, SLOT(remove_row()));
    connect(ui.dbSubmitButton, SIGNAL(clicked()), this, SLOT(clicked_submit()));
    connect(ui.NewItemButton, SIGNAL(clicked()), this, SLOT(clear_fields()));
    connect(ui.ViewCategoryComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(filter_by_categories()));

    updateMainTable();
}

std::string MainWindow::double_to_string(double input_double) {
    /*
     * Convert a double to a string with two decimal points.
     * @param input_double: Number of type Double to convert.
     * @return price_stream.str(): String denoting double with two decimal points.
     */

    double purchase_price = std::ceil(input_double * 100.0) / 100.0;
    std::ostringstream price_stream;
    price_stream << purchase_price;

    return price_stream.str();
}

void MainWindow::clicked_submit(){
    /*
     * Handle when user clicks the Submit button on the main window.
     * This does various things such as sending data from the UI fields to the database,
     * Updating the main table, and clearing the UI fields.
     */

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
    if (!item_count_str.empty()) {
        item_count = std::stoi(ui.ItemCount->text().toUtf8().constData());
    }
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
        // Handle updating existing rows
        QItemSelectionModel *select = ui.inventoryList->selectionModel();
        if (select->hasSelection()) {
            int selection = select->selectedRows().at(0).row();
            int row_to_update = ui.inventoryList->item(selection, 6)->text().toUtf8().toInt();
            std::cout << "Updating row: " << row_to_update << std::endl;

            Item item{
                    row_to_update,
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

            db.update(item);
        } else {
            std::cout << "Creating new row" << std::endl;
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
            db.write(item);  // Write new item
        }

        updateMainTable();

        clear_fields();

        populate_categories();
    }
}

void MainWindow::updateMainTable() {
    /*
     * Reads Items from the database and populates the main table with them.
     */

    Database db;
    std::vector<Item> items = db.read("ownly.db");

    ui.inventoryList->setRowCount(items.size());
    ui.inventoryList->setColumnCount(7);
    ui.inventoryList->setColumnHidden(6, true);

    populate_table(items);
}

void MainWindow::truncate_db() {
    /*
     * Truncate the database and update the main table and category dropdowns.
     */

    Database db;
    std::cout << "Truncate db clicked." << std::endl;
    Storage storage = initStorage("ownly.db");
    db.truncate(storage);
    updateMainTable();
    populate_categories();
}

void MainWindow::remove_row() {
    /*
     * Delete a row that is selected in the main table.
     */

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

    // Convert from row position on table to row position in DB, and return it.
    int row_to_delete = (ui.inventoryList->item(select, 6)->text()).toUtf8().toInt();

    std::cout << "Deleting DB row at index " << row_to_delete << std::endl;
    db.deleteRow(storage, row_to_delete);
    updateMainTable();
}

void MainWindow::table_row_clicked(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate fields in right pane when user clicks on a row in the QTableWidget.
     * @param QItemSelection: The selected row in the table.
     */

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
    populate_fields(item);
}

void MainWindow::clear_fields() {
    /*
     * Clear all user entry fields.
     */

    ui.ItemName->clear();
    ui.ItemCategory->clearEditText();
    QDate date = QDate::currentDate();
    ui.ItemPurchaseDate->setDate(date);
    ui.ItemPurchasePrice->clear();
    ui.ItemCount->clear();
    ui.ItemUsedInLastSixMonths->setChecked(false);
    ui.ItemNotes->clear();
}

void MainWindow::populate_categories() {
    /*
     * Read all rows in database, make a set containing all of the categories, and populate
     * the QComboBoxes with them.
     */

    std::set<QString> categories;
    Database db;
    std::vector<Item> allItems = db.read("ownly.db");

    // Block the signal while updating the combobox. The program crashes without this.
    QSignalBlocker ViewCategorySignalBlocker(ui.ViewCategoryComboBox);

    ui.ItemCategory->clear();
    ui.ViewCategoryComboBox->clear();
    std::cout << "Cleared ComboBox" << std::endl;
    // This is the default option.
    ui.ViewCategoryComboBox->addItem(QString::fromStdString("All Items"));

    for(const auto& item : allItems) {
        QString item_string = QString::fromStdString(item.category);
        categories.insert(item_string);
    }

    for (const auto& category : categories){
        ui.ItemCategory->addItem(category);
        ui.ViewCategoryComboBox->addItem(category);
    }
}

void MainWindow::filter_by_categories() {
    /*
     * Run a where statement, based on the category selected, against the database,
     * and return the results to the main table.
     */

    Database db;
    std::string selection = ui.ViewCategoryComboBox->currentText().toStdString();
    std::vector<Item> selected_items = db.filter(selection, "ownly.db");

    clear_fields();

    ui.inventoryList->setRowCount(selected_items.size());
    ui.inventoryList->setColumnCount(7);
    ui.inventoryList->setColumnHidden(6, true);

    populate_table(selected_items);
}

void MainWindow::populate_fields(Item item) {
    /*
     * Populate user-entry fields when user clicks on a table row.
     */

    int id = item.id;
    std::string item_name = item.itemName;
    std::string item_category = item.category;
    int purchase_year = item.purchaseYear;
    int purchase_month = item.purchaseMonth;
    int purchase_day = item.purchaseDay;
    std::string purchase_price = double_to_string(item.purchasePrice);
    int count = item.count;
    bool usedInLastSixMonths = item.usedInLastSixMonths;
    std::string notes = item.notes;

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
    ui.ItemNotes->setText(QString::fromStdString(notes));
}

void MainWindow::populate_table(std::vector<Item> items) {
    /*
     * Populate the main table widget with items.
     * @param items: A vector of Items containing item information.
     */

    int current_row = 0;
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

void MainWindow::export_to_csv(std::string output_path) {
    /*
     * Export the database to a CSV file
     * @param output_path: Path where CSV should be saved.
     */

    Database db;
    exporters exporter;
    std::vector<Item> all_items = db.read("ownly.db");
    exporter.to_csv(all_items, output_path);
}

void MainWindow::open_export_dialog() {
    /*
     * Open the export dialog window where user can enter settings.
     */

    exporters exports;
    ExportDialog export_options = new ExportDialog(this);
    export_options.setModal(true);
    std::string file_path;
    if(export_options.exec() == QDialog::Accepted) {
        std::cout << "Accepted" <<std::endl;
        file_path = export_options.get_file_path();
    }
    std::cout << "CSV output path: " << file_path;
    export_to_csv(file_path);
}

int main(int argc, char** argv) {
    /*
     * Run the mainw indow.
     */
    Database db;
    Storage storage = initStorage("ownly.db");
    db.writeDbToDisk(storage);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();

    return 0;
}