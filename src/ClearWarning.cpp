//
// Created by rwardrup on 9/9/2020.
//

#include "ClearWarning.h"
#include "Database.h"
#include <QPushButton>

ClearWarning::ClearWarning(QWidget *parent) {
    ui.setupUi(this);

    this->setFixedSize(400, 99);

    // Change the Clear button attributes
    ui.clearWarningButtons->button(QDialogButtonBox::Ok)->setText("Clear");
    QColor clear_button_color = QColor(250, 180, 174);
    ui.clearWarningButtons->button(QDialogButtonBox::Ok)->setStyleSheet(QString("background:%1").arg(clear_button_color.name()));

    connect(ui.clearWarningButtons, SIGNAL(accepted()), this, SLOT(clear_database()));
}

void ClearWarning::clear_database() {
    std::string database_path = Database::set_db_path();
    Storage storage = initStorage(database_path);
    Database::truncate(storage);
}
