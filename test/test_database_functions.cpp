//
// Created by rwardrup on 8/27/2020.
//

#include "../include/Catch2.h"
#include "../src/Database.h"

TEST_CASE("Read DB", "[DB Read]") {
    Database db;
    db.open_or_create("test-db.sqlite");
}