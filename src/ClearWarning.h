//
// Created by rwardrup on 9/9/2020.
//

#ifndef OWNLY_CLEARWARNING_H
#define OWNLY_CLEARWARNING_H

#include <QDialog>
#include "ui_clear_warning.h"


class ClearWarning : public QDialog, public Ui::ClearDialog {
    /*
     * QDialog methods
     */

Q_OBJECT
    Ui::ClearDialog ui{};

public:
    void ClearDialog(QWidget *parent = nullptr);

private slots:
    static void clear_database();
};

#endif //OWNLY_CLEARWARNING_H
