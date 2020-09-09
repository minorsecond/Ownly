//
// Created by rwardrup on 9/4/2020.
//

#include "ExportOptions.h"
#include <QFileDialog>
#include <iostream>
#include <QPointer>
#include <set>
#include <utility>
#include "Database.h"

ExportDialog::ExportDialog([[maybe_unused]] QWidget *parent, std::string database_path) {
    /*
     * Dialog box for data export options
     * @param parent: Parent widget.
     */

    ui.setupUi(this);
    this->setFixedSize(490, 88);
    populate_categories(std::move(database_path));
    ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setText("Save");
    connect(ui.ExportBrowseButton, SIGNAL(clicked()), this, SLOT(open_file_save_picker()));
}

void ExportDialog::open_file_save_picker() {
    /*
     * Open the file save dialog box when user clicks the Browse button.
     */

    QString filter;
    if (ui.CSVRadioButton->isChecked())
        filter = "CSV Files (*.csv";

    QString filename_qstring = QFileDialog::getSaveFileName(this, "Save File", "ownly_export.csv", filter, &filter);
    if (filename_qstring.isEmpty()) {
        if (ui.ExportOutputPathInput->text().isEmpty()) {
            ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
        } else
            ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
        return;
    }
    else {
        ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui.ExportOutputPathInput->setText(filename_qstring);
    }
}

std::string ExportDialog::get_file_path() {
    /*.
     * Getter for returning file path to MainWindow
     * @return: String containing path to CSV export location.
     */
    return ui.ExportOutputPathInput->text().toStdString();
}

std::string ExportDialog::get_filter_value() {
    /*
     * Getter for returning filter value back to the MainWindow class.
     * @return: String containing filter value to pass back to database query.
     */

    return ui.ExportCategoryFilter->currentText().toStdString();
}

void ExportDialog::populate_categories(std::string database_path) {
    /*
     * Populate the ExportCategoryFilter combo box with categories that exist in the database.
     */

    // TODO: Refactor this into the database class

    std::set<QString> categories;

    std::vector<Item> allItems = Database::read(std::move(database_path));

    ui.ExportCategoryFilter->clear();

    std::cout << "Cleared ComboBox" << std::endl;
    // This is the default option.
    ui.ExportCategoryFilter->addItem(QString::fromStdString("All Items"));
    std::cout << "Added All Items" << std::endl;
    for(const auto& item : allItems) {
        QString item_string = QString::fromStdString(item.category);
        categories.insert(item_string);
    }

    for (const auto& category : categories){
        ui.ExportCategoryFilter->addItem(category);
    }
}
