//
// Created by rwardrup on 8/27/2020.
//

#include "../include/Catch2.h"
#include "../src/Database.h"
#include <iostream>
#include <fstream>

Database db;

inline bool exists(const std::string& filename){
    std::ifstream f(filename.c_str());
    return f.good();
}

TEST_CASE("Init DB", "[DB Creation]") {
    std::string file_name = "testdb.sqlite";
    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);
    std::vector table_names = storage.table_names();
    REQUIRE( exists(file_name) == true);
    REQUIRE( table_names.at(0) == "items");
    std::remove(file_name.c_str());
}

TEST_CASE( "DB IO", "[DB IO]" ) {
    std::string file_name = "testdb.sqlite";
    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);

    Item item{-1, "The Silmarillion", "Book", 1998,
              3, 7, 8.99, 1, true,
              "This is absolutely my favorite Tolkien book."};
    int firstInsertedId = storage.insert(item);

    Item secondItem{-1, "HF Ham Radio", "Electronics", 2001, 8,
                    14, 599.99, 1, true, "Great radio."};
    int secondInsertedId = storage.insert(secondItem);

    Item book = storage.get<Item>(firstInsertedId);
    Item radio = storage.get<Item>(secondInsertedId);

    REQUIRE ( firstInsertedId == 1 );
    REQUIRE ( secondInsertedId == 2 );
    REQUIRE( book.itemName == "The Silmarillion" );
    REQUIRE( book.purchasePrice == 8.99 );
    REQUIRE( book.notes == "This is absolutely my favorite Tolkien book." );

    std::remove(file_name.c_str());
}

TEST_CASE( "DB Truncate", "[DB Truncate]" ) {
    std::string file_name = "testdb.sqlite";
    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);

    Item item{-1, "The Silmarillion", "Book", 1998,
              3, 7, 8.99, 1, true,
              "This is absolutely my favorite Tolkien book."};
    int firstInsertedId = storage.insert(item);

    Item secondItem{-1, "HF Ham Radio", "Electronics", 2001, 8,
                    14, 599.99, 1, true, "Great radio."};
    int secondInsertedId = storage.insert(secondItem);
    db.writeDbToDisk(storage);
    db.truncate(storage);
    std::vector<Item> allItems = db.read(file_name);

    REQUIRE( allItems.empty() == true);
}