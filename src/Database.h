//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"
#include "../include/sqlite_orm.h"
#include <vector>

struct Item {
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

inline static auto initStorage(const std::string& file_name) {
    return sqlite_orm::make_storage(file_name,
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

using Storage = decltype(initStorage(""));  // Get Storage return type

class Database {
public:
    void deleteRow(Storage storage, int row_number);
    int writeDbToDisk(Storage storage);
    std::vector<Item> read(std::string);
    Storage write(Item item);
    void truncate(Storage);
};

#endif //NOTCH_DATABASE_H
