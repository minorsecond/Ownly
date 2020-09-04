//
// Created by rwardrup on 9/4/2020.
//

#include "ExportOptions.h"
#include "ui_export_options.h"
#include <QFileDialog>

ExportDialog::ExportDialog(QWidget *parent) {
    //setupUi(this);
    Ui::ExportOptions ui{};
    ui.setupUi(this);

    connect(ui.ExportBrowseButton, SIGNAL(clicked()), this, SLOT(open_file_save_picker()));
}

void ExportDialog::open_file_save_picker() {
    QString filename_qstring = QFileDialog::getSaveFileName(this, "Save File", ".csv");
    this->ExportOutputPathInput->setText(filename_qstring);
}