//
// Created by rwardrup on 9/4/2020.
//

#ifndef OWNLY_EXPORTOPTIONS_H
#define OWNLY_EXPORTOPTIONS_H

#include <QDialog>
#include "ui_export_options.h"

class ExportDialog : public QDialog, public Ui::ExportOptions {
    Q_OBJECT
public:
    ExportDialog(QWidget * parent = nullptr);
};

#endif //OWNLY_EXPORTOPTIONS_H
