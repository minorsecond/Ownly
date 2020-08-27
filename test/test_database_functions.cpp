//
// Created by rwardrup on 8/27/2020.
//

#include "../include/Catch2.h"
#include "../src/Database.h"

TEST_CASE("Init DB", "[DB Read]") {
    Database db;
    auto storage = db.initStorage();

}