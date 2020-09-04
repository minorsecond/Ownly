//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace sqlite_orm;

std::vector<Item> Database::read(std::string file_name) {
    /*
     * Read items from sqlite database.
     * The Item struct is defined in Database.h
     *
     * @param: file_name String denoting file name of sqlite file.
     * @return: vector of Items.
     */

    Storage storage = initStorage(file_name);
    std::vector<Item> allItems = storage.get_all<Item>();

    return allItems;
}

Storage Database::write(Item item) {
    /*
     * Write an Item to the sqlite database.
     *
     * @param: item an Item containing attributes of a household item
     * @return: Storage instance.
     */

    Storage storage = initStorage("ownly.db");

    auto insertedId = storage.insert(item);
    std::cout << "insertedId = " << insertedId << std::endl;
    item.id = insertedId;

    writeDbToDisk(storage);

    return storage;
}

int Database::writeDbToDisk(Storage storage) {
    /*
     * Write in-memory items to sqlite file.
     * @param storage: A storage instance.
     */
    //TODO: refactor this to a void
    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
    return 0;
}

void Database::truncate(Storage storage) {
    /*
     * Remove all rows from the sqlite database.
     * @param storage: A storage instance.
     */

    storage.remove_all<Item>();
    writeDbToDisk(storage);
}

void Database::deleteRow(Storage storage, int row_number) {
    /*
     * Delete a specific row from the sqlite database.
     * @param storage: A storage instance.
     * @param row_number: Row number to delete. This is the primary key in the sqlite file.
     */

    storage.remove<Item>(row_number);
}

Item Database::read_row(Storage storage, int row) {
    /*
     * Read a specific row from the sqlite database.
     * @param storage: A storage instance.
     * @param row: The primary key id denoting the row to read.
     */

    Item item = storage.get<Item>(row);
    return item;
}

void Database::update(const Item& item) {
    /*
     * Update an Item that exists in the database.
     * @param item: The Item to update.
     */

    Storage storage = initStorage("ownly.db");
    storage.update(item);
}

std::vector<Item> Database::filter(std::string category, std::string file_name) {
    /*
     * Filter database by a category.
     * @param category: Category to filter database on.
     * @param file_name: file name of sqlite file.
     */

    Storage storage = initStorage(file_name);
    std::vector<Item> items_by_category;
    if (category == "All Items") {
        items_by_category = read(file_name);
    } else {
        items_by_category = storage.get_all<Item>(sqlite_orm::where(sqlite_orm::c(&Item::category) == category));
    }

    return items_by_category;
}
