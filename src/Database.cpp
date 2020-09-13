//
// Created by rwardrup on 8/26/2020.
//

#include "Database.h"
#include "../include/sqlite_orm.h"
#include <unistd.h>
#include <iostream>
#include <utility>
#include <vector>

using namespace sqlite_orm;

std::vector<Item> Database::read(std::string database_path) {
    /*
     * Read items from sqlite database.
     * The Item struct is defined in Database.h
     *
     * @param: file_name String denoting file name of sqlite file.
     * @return: vector of Items.
     */

    Storage storage = initStorage(std::move(database_path));
    std::vector<Item> allItems = storage.get_all<Item>();

    return allItems;
}

Storage Database::write(Item item, std::string database_path) {
    /*
     * Write an Item to the sqlite database.
     *
     * @param: item an Item containing attributes of a household item
     * @return: Storage instance.
     */


    Storage storage = initStorage(std::move(database_path));

    auto insertedId = storage.insert(item);
    std::cout << "insertedId = " << insertedId << std::endl;
    item.id = insertedId;

    writeDbToDisk(storage);

    return storage;
}

void Database::writeDbToDisk(Storage storage) {
    /*
     * Write in-memory items to sqlite file.
     * @param storage: A storage instance.
     */
    std::map<std::string, sqlite_orm::sync_schema_result> schema_sync_result = storage.sync_schema(false);
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
    writeDbToDisk(storage);
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

void Database::update(const Item& item, std::string database_path) {
    /*
     * Update an Item that exists in the database.
     * @param item: The Item to update.
     */

    Storage storage = initStorage(std::move(database_path));
    storage.update(item);
}

std::vector<Item> Database::filter(const std::string& category, const std::string& database_path) {
    /*
     * Filter database by a category.
     * @param category: Category to filter database on.
     * @param file_name: file name of sqlite file.
     */

    Storage storage = initStorage(database_path);
    std::vector<Item> items_by_category;
    if (category == "All Items") {
        items_by_category = read(database_path);
    } else {
        items_by_category = storage.get_all<Item>(sqlite_orm::where(sqlite_orm::c(&Item::category) == category));
    }

    return items_by_category;
}

std::string Database::set_db_path() {
    /*
     * Get the path to the users APPDATA directory for database storage.
     * @return database_path: Path where database will be stored.
     */

    std::string database_path;
    PWSTR localAppData = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &localAppData) == S_OK) {
        std::wstring ws_path(localAppData);
        std::string database_directory;
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        database_directory = converter.to_bytes(ws_path) + "\\Ownly";
        database_path = database_directory + "\\ownly_data.db";
        CoTaskMemFree(static_cast<void*>(localAppData));

        CreateDirectory(database_directory.c_str(), nullptr);
        std::cout << "DB path: " << database_path << std::endl;
    }

    return database_path;
}

std::vector<Item> Database::search_by_name(const std::string &item_name, const std::string &database_path) {
    /*
     * Filter database by an item name.
     * @param category: name to filter database on.
     * @param file_name: file name of sqlite file.
     */

    Storage storage = initStorage(database_path);
    std::vector<Item> items_by_name;
    std::string query_string = "%" + item_name + "%";
    items_by_name = storage.get_all<Item>(sqlite_orm::where(like(&Item::itemName, query_string)));

    return items_by_name;
}
