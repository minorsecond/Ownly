//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>

Storage Database::read(const std::string& file_name) {
    auto storage = initStorage(file_name);
    auto allItems = storage.get_all<Item>();

    for(auto &item : allItems) {
        std::cout << storage.dump(item) << std::endl;
    }

    return storage;
}

Storage Database::write(const std::string &file_name, std::vector<std::string> payload) {
    Storage storage = initStorage(file_name);
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

    Item item{-1, item_name, item_category, purchaseYear, purchaseMonth, purchaseDay, purchase_price, count, usedInLastSixMonths, notes};
    auto insertedId = storage.insert(item);
    std::cout << "insertedId = " << insertedId << std::endl;
    item.id = insertedId;

    return storage;
}

int Database::open_or_create(const std::string& file_name) {
    int res = access(file_name.c_str(), R_OK);

    if(res < 0) {
        if (errno == ENOENT) {// DB file doesn't exist
            std::cout << "Creating new SQLite3 file at : " << file_name << std::endl;
            Storage storage = initStorage(file_name);
            Database::writeDbToDisk(storage);
        } else if (errno == EACCES) {  // DB file exists but isn't readable
            std::cout << "SQLite3 File exists at: " << file_name << " but is corrupt." << std::endl;
        }
    } else if (res == 0) {
        std::cout << "Reading existing SQLite3 file at: " << file_name << std::endl;
        Storage storage = Database::read("db.sqlite");
    }

    return res;
}

int Database::writeDbToDisk(Storage storage) {
    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
    return 0;
}
