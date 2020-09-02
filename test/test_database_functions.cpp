//
// Created by rwardrup on 8/27/2020.
//

#include "../include/Catch2.h"
#include "../src/Database.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

Database db;

inline bool exists(const std::string& filename){
    std::ifstream f(filename.c_str());
    return f.good();
}

TEST_CASE("Init DB", "[DB Creation]") {
    const char *file_name = "testdb.sqlite";

    if (remove(file_name)) {
        std::cout << "Removed existing testdb.sqlite file";
    }

    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);
    std::vector table_names = storage.table_names();
    REQUIRE( exists(file_name) == true);
    REQUIRE( table_names.at(0) == "items");
    std::remove(file_name);
}

TEST_CASE( "DB IO", "[DB IO]" ) {
    const char *file_name = "testdb.sqlite";

    if (remove(file_name)) {
        std::cout << "Removed existing testdb.sqlite file";
    }

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

    std::remove(file_name);
}

TEST_CASE( "DB Truncate", "[DB Truncate]" ) {
    const char *file_name = "testdb.sqlite";

    if (remove(file_name)) {
        std::cout << "Removed existing testdb.sqlite file";
    }

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

TEST_CASE( "Delete Row", "[Delete Row]" ) {
    const char *file_name = "testdb.sqlite";
    int min_id = 3;
    int max_id = -1;

    if (remove(file_name)) {
        std::cout << "Removed existing testdb.sqlite file";
    }

    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);

    Item firstItem{-1, "The Silmarillion", "Book", 1998,
              3, 7, 8.99, 1, true,
              "This is absolutely my favorite Tolkien book."};

    Item secondItem{-1, "HF Ham Radio", "Electronics", 2001, 8,
                    14, 599.99, 1, true, "Great radio."};
    storage.insert(secondItem);
    storage.insert(firstItem);

    db.writeDbToDisk(storage);
    db.deleteRow(storage, 1);
    db.writeDbToDisk(storage);
    std::vector<Item> items = db.read(file_name);

    for(const auto& item : items) {
        if(item.id > max_id)
            max_id = item.id;
        if(item.id < min_id)
            min_id = item.id;
    }

    REQUIRE(items.empty() == false);
    REQUIRE(items.size() == 1);
    REQUIRE(max_id == min_id);
}