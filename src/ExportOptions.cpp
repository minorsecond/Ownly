//
// Created by rwardrup on 9/4/2020.
//

#include "ExportOptions.h"
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QPointer>

ExportDialog::ExportDialog(QWidget *parent) {
    /*
     * Dialog box for data export options
     * @param parent: Parent widget.
     */

    ui.setupUi(this);
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
