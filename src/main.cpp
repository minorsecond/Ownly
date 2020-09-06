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
#include <iomanip>
#include "exporters.h"
#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow([[maybe_unused]] QWidget *parent) {
    /*
     * Main Window for program
     * @param parent: Parent QWidget object
     */

    database_path = set_db_path();
    Storage storage = initStorage(database_path);
    Database::writeDbToDisk(storage);

    ui.setupUi(this);
    this->setFixedSize(1053, 520);

    QHeaderView* header = ui.inventoryList->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);

    // Only allow single-row selection on table widget
    ui.inventoryList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.inventoryList->setSelectionMode(QAbstractItemView::SingleSelection);

    ui.inventoryList->setSortingEnabled(true);

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

    // Disconnect the corner button slot
    auto *cornerButton = ui.inventoryList->findChild<QAbstractButton*>();
    if (cornerButton)
        cornerButton->disconnect();

    // Slots
    connect(cornerButton, SIGNAL(clicked()), this, SLOT(reset_table_sort()));
    connect(ui.inventoryList->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(table_row_clicked(const QItemSelection &, const QItemSelection &)));
    connect(ui.actionClear_Data, SIGNAL(triggered()), this, SLOT(truncate_db()));
    connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(open_export_dialog()));
    connect(ui.deleteItemButton, SIGNAL(clicked()), this, SLOT(remove_row()));
    connect(ui.dbSubmitButton, SIGNAL(clicked()), this, SLOT(clicked_submit()));
    connect(ui.NewItemButton, SIGNAL(clicked()), this, SLOT(new_item_button()));
    connect(ui.ViewCategoryComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(filter_by_categories()));

    updateMainTable();
    ui.inventoryList->sortByColumn(6, Qt::AscendingOrder);  // Sort by ID in database
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

    // Check if a row is selected
    QItemSelectionModel *selectionModel = ui.inventoryList->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    std::string item_name = ui.ItemName->text().toUtf8().constData();
    std::string item_category = ui.ItemCategory->currentText().toUtf8().constData();
    std::string item_price_string = ui.ItemPurchasePrice->text().toUtf8().constData();
    double item_price;
    std::string item_count_str = ui.ItemCount->text().toUtf8().constData();
    bool usedFrequently = ui.UsedFrequently->isChecked();
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
        QMessageBox::critical(nullptr, "Error", "Please enter item name, category, and count.");
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
                    usedFrequently,
                    notes
            };

            Database::update(item, database_path);
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
                    usedFrequently,
                    notes
            };
            Database::write(item, database_path);  // Write new item
        }

        updateMainTable();

        if (selectedRows.empty())
            clear_fields();

        populate_categories();
    }
}

void MainWindow::updateMainTable() {
    /*
     * Reads Items from the database and populates the main table with them.
     */

    std::vector<Item> items = Database::read(database_path);

    ui.inventoryList->setRowCount(items.size());
    ui.inventoryList->setColumnCount(7);
    ui.inventoryList->setColumnHidden(6, true);

    populate_table(items);
}

void MainWindow::truncate_db() {
    /*
     * Truncate the database and update the main table and category dropdowns.
     */

    std::cout << "Truncate db clicked." << std::endl;
    Storage storage = initStorage(database_path);
    Database::truncate(storage);
    updateMainTable();
    populate_categories();
}

void MainWindow::remove_row() {
    /*
     * Delete a row that is selected in the main table.
     */

    Storage storage = initStorage(database_path);

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
    Database::deleteRow(storage, row_to_delete);
    updateMainTable();
}

void MainWindow::table_row_clicked(const QItemSelection &, const QItemSelection &) {
    /*
     * Populate fields in right pane when user clicks on a row in the QTableWidget.
     * @param QItemSelection: The selected row in the table.
     */

    Storage storage = initStorage(database_path);

    QItemSelectionModel *select = ui.inventoryList->selectionModel();

    int selection = ui.inventoryList->selectionModel()->currentIndex().row();
    int row_to_get = ui.inventoryList->item(selection, 6)->text().toUtf8().toInt();

    if(select->isRowSelected(selection))
        ui.deleteItemButton->setEnabled(true);
    else
        ui.deleteItemButton->setDisabled(true);

    Item item = Database::read_row(storage, row_to_get);
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
    ui.UsedFrequently->setChecked(false);
    ui.ItemNotes->clear();
}

void MainWindow::populate_categories() {
    /*
     * Read all rows in database, make a set containing all of the categories, and populate
     * the QComboBoxes with them.
     */

    std::set<QString> categories;

    std::vector<Item> allItems = Database::read(database_path);

    // Block the signal while updating the combobox. The program crashes without this.
    QSignalBlocker ViewCategorySignalBlocker(ui.ViewCategoryComboBox);

    ui.ItemCategory->clear();
    ui.ViewCategoryComboBox->clear();

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

    std::string selection = ui.ViewCategoryComboBox->currentText().toStdString();
    std::vector<Item> selected_items = Database::filter(selection, database_path);

    clear_fields();

    ui.inventoryList->setRowCount(selected_items.size());
    ui.inventoryList->setColumnCount(7);
    ui.inventoryList->setColumnHidden(6, true);

    populate_table(selected_items);
}

void MainWindow::populate_fields(const Item& item) {
    /*
     * Populate user-entry fields when user clicks on a table row.
     */

    std::string item_name = item.itemName;
    std::string item_category = item.category;
    int purchase_year = item.purchaseYear;
    int purchase_month = item.purchaseMonth;
    int purchase_day = item.purchaseDay;
    std::string purchase_price = double_to_string(item.purchasePrice);
    int count = item.count;
    bool usedFrequently = item.usedFrequently;
    std::string notes = item.notes;

    std::ostringstream month_padded;
    std::ostringstream day_padded;
    month_padded << std::setw(2) << std::setfill('0') << purchase_month;
    day_padded << std::setw(2) << std::setfill('0') << purchase_day;

    std::string date_from_db = day_padded.str() + "/" + month_padded.str() + "/" + std::to_string(purchase_year);
    QDate date = QDate::fromString(QString::fromUtf8(date_from_db.c_str()), "dd/MM/yyyy");

    ui.ItemName->setText(QString::fromStdString(item_name));
    ui.ItemCategory->setCurrentText(QString::fromStdString(item_category));
    ui.ItemPurchaseDate->setDate(date);
    ui.ItemPurchasePrice->setText(QString::fromStdString(purchase_price));
    ui.ItemCount->setValue(count);

    if(usedFrequently)
        ui.UsedFrequently->setChecked(true);
    else
        ui.UsedFrequently->setChecked(false);
    ui.ItemNotes->setText(QString::fromStdString(notes));
}

void MainWindow::populate_table(const std::vector<Item>& items) {
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
        bool usedFrequently = entry.usedFrequently;
        auto *id = new QTableWidgetItem(std::to_string(entry.id).c_str());
        QTableWidgetItem *used_recently;

        // Limit prices on table to two digits
        std::string purchase_price = double_to_string(entry.purchasePrice);
        //double purchase_price = std::ceil(entry.purchasePrice * 100.0) / 100.0;
        //std::ostringstream price_stream;
        //price_stream << purchase_price;
        auto *purchase_price_str = new QTableWidgetItem(purchase_price.c_str());


        std::string date = std::to_string(purchase_year) + "/" + std::to_string(purchase_month) + "/" + \
            std::to_string(purchase_day);

        auto *date_qtwi = new QTableWidgetItem(date.c_str());

        if(usedFrequently) {
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

void MainWindow::open_export_dialog() {
    /*
     * Open the export dialog window where user can enter settings.
     */

    //ExportDialog export_options = new ExportDialog(this, database_path);
    ExportDialog export_options = ExportDialog(nullptr, database_path);
    export_options.setModal(true);
    std::string file_path;
    std::string filter_value;

    if(export_options.exec() == QDialog::Accepted) {
        std::cout << "Accepted" <<std::endl;
        file_path = export_options.get_file_path();
        filter_value = export_options.get_filter_value();
    }
    std::cout << "CSV output path: " << file_path << std::endl;
    std::cout << "Filter value: " << filter_value << std::endl;

    std::vector<Item> items = Database::filter(filter_value, database_path);
    exporters::to_csv(items, file_path);
}

void MainWindow::new_item_button() {
    /*
     * Clear table row selection and fields when user clicks the New Item button
     */

    ui.inventoryList->selectionModel()->clearSelection();
    clear_fields();
}

void MainWindow::reset_table_sort() {
    /*
     * Reset table sorting to default sorting order (Sorted by ID in database)
     */

    qDebug() << "Reset table sort";
    ui.inventoryList->sortByColumn(6, Qt::AscendingOrder);
}

std::string set_db_path() {
    /*
     * Get the path to the users APPDATA directory for database storage.
     * @return database_path: Path where database will be stored.
     */

    std::string database_path;
    PWSTR localAppData = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &localAppData) == S_OK) {
        std::wstring ws_path(localAppData);
        std::string database_directory;
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        database_directory = converter.to_bytes(ws_path) + "\\Ownly";
        database_path = database_directory + "\\ownly_data.db";
        CoTaskMemFree(static_cast<void*>(localAppData));

        CreateDirectory(database_directory.c_str(), nullptr);
        std::cout << "DB path: " << database_path << std::endl;
    }

    return database_path;
}

int main(int argc, char** argv) {
    /*
     * Run the main window.
     */

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}