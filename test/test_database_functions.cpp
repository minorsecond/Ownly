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

TEST_CASE("Init DB", "[DB Read]") {
    std::string file_name = "testdb.sqlite";
    Storage storage = initStorage(file_name);
    db.writeDbToDisk(storage);
    std::vector table_names = storage.table_names();
    REQUIRE( exists(file_name) == true);
    REQUIRE( table_names.at(0) == "items");
    std::remove(file_name.c_str());
}