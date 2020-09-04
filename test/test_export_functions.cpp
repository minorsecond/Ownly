//
// Created by rwardrup on 9/4/2020.
//

#include "../include/Catch2.h"
#include "../src/exporters.h"
#include "iostream"
#include <fstream>
#include <ios>

TEST_CASE("Create CSV", "[CSV Creation]") {
    std::cout << "Starting CSV test" << std::endl;
    std::string csv_file_name = "test.csv";
    const char *db_file_name = "testdb.sqlite";
    Database db;

    if (remove(csv_file_name.c_str())) {
        std::cout << "Removed existing test.csv file";
    }

    if (remove(db_file_name)) {
        std::cout << "Removed existing testb.sqlite file";
    }

    // Create and populate the database
    Storage storage = initStorage(db_file_name);
    db.writeDbToDisk(storage);
    Item item{-1, "The Silmarillion", "Book", 1998,
              3, 7, 8.99, 1, true,
              "This is absolutely my favorite Tolkien book."};
    storage.insert(item);

    Item secondItem{-1, "HF Ham Radio", "Electronics", 2001, 8,
                    14, 599.99, 1, true, "Great radio."};
    storage.insert(secondItem);
    db.writeDbToDisk(storage);
    // Write the CSV from DB
    std::vector<Item> all_items = db.read("testdb.sqlite");
    exporters::to_csv(all_items, csv_file_name);

    // Read the CSV
    std::ifstream csv_file(csv_file_name);
    std::vector<std::string> csv_data;

    REQUIRE(csv_file.good() == true);
    REQUIRE(csv_file.is_open() == true);

    std::string line;
    int row_counter = 0;
    std::vector<std::string> rows;
    while (std::getline(csv_file, line)) {
        std::istringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            //std::cout << "Token: " << token;
        }
        rows.push_back(line);
    }
    REQUIRE(rows.at(0) == "item_name,category,purchase_date,purchase_price,count,used_recently,notes,");
    REQUIRE(rows.at(1) == "The Silmarillion,Book,1998/3/7,8.990000,1,Yes,This is absolutely my favorite Tolkien book.,");
    REQUIRE(rows.at(2) == "HF Ham Radio,Electronics,2001/8/14,599.990000,1,Yes,Great radio.,");
}