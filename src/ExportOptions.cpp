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

    connect(ui.ExportBrowseButton, SIGNAL(clicked()), this, SLOT(open_file_save_picker()));
}

void ExportDialog::open_file_save_picker() {
    QString filter = "CSV Files (*.csv";
    QString filename_qstring = QFileDialog::getSaveFileName(this, "Save File", "ownly_export.csv", filter, &filter);
    if (filename_qstring.isEmpty())
        return;
    else {
        ui.ExportOutputPathInput->setText(filename_qstring);
        //std::cout << "Set the text: " << ui.ExportOutputPathInput->text().toStdString() << std::endl;
    }
}