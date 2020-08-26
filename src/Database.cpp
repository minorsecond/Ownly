//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>

auto Database::get() {
    auto storage = sqlite_orm::make_storage("db.sqlite",
                                            sqlite_orm::make_table("items",
                                                                   sqlite_orm::make_column("id", &Item::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                                                                   sqlite_orm::make_column("item_name", &Item::itemName),
                                                                   sqlite_orm::make_column("category", &Item::category),
                                                                   sqlite_orm::make_column("purchase_year", &Item::purchaseYear),
                                                                   sqlite_orm::make_column("purchase_month", &Item::purchaseMonth),
                                                                   sqlite_orm::make_column("purchase_day", &Item::purchaseDay),
                                                                   sqlite_orm::make_column("purchase_price", &Item::purchasePrice),
                                                                   sqlite_orm::make_column("count", &Item::count),
                                                                   sqlite_orm::make_column("used_in_last_six_months", &Item::usedInLastSixMonths, sqlite_orm::default_value(
                                                                           false)),
                                                                   sqlite_orm::make_column("notes", &Item::notes)));

    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
    return storage;
}

void Database::read(const std::string& file_name) {
    auto storage = Database::get();
    auto allItems = storage.get_all<Item>();

    for(auto &item : allItems) {
        std::cout << storage.dump(item) << std::endl;
    }
}

int Database::open_or_create(const std::string& file_name) {
    int res = access(file_name.c_str(), R_OK);

    if(res < 0) {
        if (errno == ENOENT) {// DB file doesn't exist
            Database::get();
            std::cout << "Creating new SQLite3 file at : " << file_name << std::endl;
        } else if (errno == EACCES) {  // DB file exists but isn't readable
            std::cout << "SQLite3 File exists at: " << file_name << " but is corrupt." << std::endl;
        }
    } else if(res == 0) {
        Database::read(file_name);
        std::cout << "Reading existing SQLite3 file at: " << file_name << std::endl;
    }

    return res;
}