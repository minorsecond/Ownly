//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>

std::vector<Item> Database::read(std::string file_name) {
    Storage storage = initStorage(file_name);
    std::vector<Item> allItems = storage.get_all<Item>();

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

int Database::writeDbToDisk(Storage storage) {
    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
    return 0;
}

void Database::truncate(Storage storage) {
    storage.remove_all<Item>();
    writeDbToDisk(storage);
}
