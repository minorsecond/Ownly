//
// Created by rwardrup on 8/27/2020.
//

#include "../include/Catch2.h"
#include "../src/Database.h"
#include <iostream>
#include "sqlite3.h"
#include "../include/sqlite_orm.h"
#include <vector>

TEST_CASE("Init DB", "[DB Read]") {
    Storage storage = initStorage();
    //std::vector table_names = storage.table_names();

    //for(auto i = table_names.begin(); i != table_names.end(); ++i)
    //    std::cout << *i << std::endl;
}