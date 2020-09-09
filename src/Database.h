//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"
#include "../include/sqlite_orm.h"
#include <vector>
#include <windows.h>
#include <shlobj.h>
#include <locale>
#include <codecvt>

#include <iostream>

struct Item {  // Struct for storing item attributes
    int id;
    std::string itemName;
    std::string category;
    int purchaseYear;
    int purchaseMonth;
    int purchaseDay;
    double purchasePrice;
    int count;
    bool usedFrequently;
    std::string notes;
};

inline static auto initStorage(const std::string& database_path) {
    /*
     * Initialize the sqlite database. This creates a new file
     * if one doesn't already exist. If one already exists, it
     * will use it.
     * @param file_name: Path to location of sqlite file
     * @return: A Storage instance.
     */

    return sqlite_orm::make_storage(database_path,
                                    sqlite_orm::make_table("items",
                                                           sqlite_orm::make_column("id", &Item::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
                                                           sqlite_orm::make_column("item_name", &Item::itemName),
                                                           sqlite_orm::make_column("category", &Item::category),
                                                           sqlite_orm::make_column("purchase_year", &Item::purchaseYear),
                                                           sqlite_orm::make_column("purchase_month", &Item::purchaseMonth),
                                                           sqlite_orm::make_column("purchase_day", &Item::purchaseDay),
                                                           sqlite_orm::make_column("purchase_price", &Item::purchasePrice),
                                                           sqlite_orm::make_column("count", &Item::count),
                                                           sqlite_orm::make_column("used_frequently", &Item::usedFrequently, sqlite_orm::default_value(
                                                                   false)),
                                                           sqlite_orm::make_column("notes", &Item::notes)));

}

using Storage = decltype(initStorage(""));  // Get Storage return type

class Database {
    /*
     * Various database related methods.
     */
public:
    static void deleteRow(Storage storage, int row_number);
    static void writeDbToDisk(Storage storage);  // Flush in-memory data to file
    static std::vector<Item> read(std::string database_path);
    static Storage write(Item item, std::string database_path);
    static void truncate(Storage);
    static Item read_row(Storage storage, int row);
    static std::vector<Item> filter(const std::string& category, const std::string& database_path);
    static void update(const Item& item, std::string database_path);
    static std::string set_db_path();
};

#endif //NOTCH_DATABASE_H
