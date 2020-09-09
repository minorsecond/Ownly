//
// Created by rwardrup on 9/9/2020.
//

#include "ClearWarning.h"
#include "Database.h"

void ClearWarning::ClearDialog(QWidget *parent) {
    ui.setupUi(this);

    connect(ui.clearWarningButtons, SIGNAL(accepted), this, SLOT(clear_database()));
}

void ClearWarning::clear_database() {
    std::string database_path = Database::set_db_path();
    Storage storage = initStorage(database_path);
    Database::truncate(storage);
}
