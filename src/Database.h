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
    bool usedInLastSixMonths;
    std::string notes;
};

inline static std::string set_db_path() {
    /*
     * Get the path to the users APPDATA directory for database storage.
     * @return database_path: Path where database will be stored.
     */

    std::string database_path;
    PWSTR localAppData = NULL;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &localAppData) == S_OK) {
        std::wstring ws_path(localAppData);
        std::string database_directory;
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        database_directory = converter.to_bytes(ws_path) + "\\Ownly";
        database_path = database_directory + "\\ownly_data.db";
        CoTaskMemFree(static_cast<void*>(localAppData));

        CreateDirectory(database_directory.c_str(), NULL);
        std::cout << "DB path: " << database_path << std::endl;
    }

    return database_path;
}

inline static auto initStorage() {
    /*
     * Initialize the sqlite database. This creates a new file
     * if one doesn't already exist. If one already exists, it
     * will use it.
     * @param file_name: Path to location of sqlite file
     * @return: A Storage instance.
     */

    std::string database_path = set_db_path();
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
                                                           sqlite_orm::make_column("used_in_last_six_months", &Item::usedInLastSixMonths, sqlite_orm::default_value(
                                                                   false)),
                                                           sqlite_orm::make_column("notes", &Item::notes)));

}

using Storage = decltype(initStorage());  // Get Storage return type

class Database {
    /*
     * Various database related methods.
     */
public:
    void deleteRow(Storage storage, int row_number);
    int writeDbToDisk(Storage storage);  // Flush in-memory data to file
    std::vector<Item> read();
    Storage write(Item item);
    void truncate(Storage);
    Item read_row(Storage storage, int row);
    std::vector<Item> filter(std::string category);
    static void update(const Item& item);
};

#endif //NOTCH_DATABASE_H
