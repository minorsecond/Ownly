//
// Created by rwardrup on 9/4/2020.
//

#ifndef OWNLY_EXPORTOPTIONS_H
#define OWNLY_EXPORTOPTIONS_H

#include <QDialog>
#include "ui_export_options.h"

class ExportDialog : public QDialog, public Ui::ExportOptions {
    Q_OBJECT
    Ui::ExportOptions ui{};
public:
    ExportDialog(QWidget *parent = nullptr);

private slots:
    void open_file_save_picker();
};

#endif //OWNLY_EXPORTOPTIONS_H
