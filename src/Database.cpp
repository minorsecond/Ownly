//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>

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

auto Database::read(const std::string& file_name) {
    auto storage = Database::get();
    auto allItems = storage.get_all<Item>();

    for(auto &item : allItems) {
        std::cout << storage.dump(item) << std::endl;
    }

    return storage;
}

int Database::write(const std::string &file_name, std::vector<std::string> payload) {
    auto storage = Database::get();
    std::string item_name = payload.at(0);
    std::string item_category = payload.at(1);
    std::string purchase_date = payload.at(2);
    int purchaseYear = 0;
    int purchaseMonth = 0 ;
    int purchaseDay= 0;
    double purchase_price = std::stod(payload.at(3));
    int count = std::stoi(payload.at(3));
    bool usedInLastSixMonths = false;
    std::string notes = payload.at(5);

    if(std::strcmp(payload.at(4).c_str(), "true") == 0)
        usedInLastSixMonths = true;
    else if(std::strcmp(payload.at(4).c_str(), "false") == 0)
        usedInLastSixMonths = false;

    // QDateEdit returns string as dd/mm/yyyy
    scanf("%d/%d/%d", &purchaseMonth, &purchaseDay, &purchaseYear);

    Item item{-1, item_name, item_category, purchaseYear, purchaseMonth, purchaseDay, purchase_price, count, usedInLastSixMonths, notes};
    auto insertedId = storage.insert(item);
    std::cout << "insertedId = " << insertedId << std::endl;
    item.id = insertedId;

    return insertedId;
}

auto Database::open_or_create(const std::string& file_name) {
    int res = access(file_name.c_str(), R_OK);

    if(res < 0) {
        if (errno == ENOENT) {// DB file doesn't exist
            std::cout << "Creating new SQLite3 file at : " << file_name << std::endl;
            return Database::get();
        } else if (errno == EACCES) {  // DB file exists but isn't readable
            std::cout << "SQLite3 File exists at: " << file_name << " but is corrupt." << std::endl;
        }
    } else if(res == 0) {
        std::cout << "Reading existing SQLite3 file at: " << file_name << std::endl;
        return Database::read(file_name);
    }
}