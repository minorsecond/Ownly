//
// Created by rwardrup on 9/4/2020.
//

#include "ExportOptions.h"
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QPointer>

ExportDialog::ExportDialog(QWidget *parent) {
    ui.setupUi(this);
    ui.ExportButtonOkCancelButtons->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui.ExportBrowseButton, SIGNAL(clicked()), this, SLOT(open_file_save_picker()));
}

void ExportDialog::open_file_save_picker() {
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
    return ui.ExportOutputPathInput->text().toStdString();
}
