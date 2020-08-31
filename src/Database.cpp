//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>

std::vector<Item> Database::read() {
    Storage storage = initStorage("ownly.db");
    std::vector<Item> allItems = storage.get_all<Item>();

    for(auto &item : allItems) {
        std::cout << storage.dump(item) << std::endl;
    }

    return allItems;
}

Storage Database::write(Item item) {
    Storage storage = initStorage("ownly.db");

    auto insertedId = storage.insert(item);
    std::cout << "insertedId = " << insertedId << std::endl;
    item.id = insertedId;

    writeDbToDisk(storage);

    return storage;
}

int Database::open_or_create() {
    int res = access(std::string("ownly.db").c_str(), R_OK);

    if(res < 0) {
        if (errno == ENOENT) {// DB file doesn't exist
            std::cout << "Creating new SQLite3 file at : " << "ownly.db" << std::endl;
            Storage storage = initStorage("ownly.db");
            Database::writeDbToDisk(storage);
        } else if (errno == EACCES) {  // DB file exists but isn't readable
            std::cout << "SQLite3 File exists at: " << "ownly.db" << " but is corrupt." << std::endl;
        }
    } else if (res == 0) {
        std::cout << "Reading existing SQLite3 file at: " << "ownly.db" << std::endl;
        Storage storage = Database::read();
    }

    return res;
}

int Database::writeDbToDisk(Storage storage) {
    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
    return 0;
}
