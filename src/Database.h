//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"
#include <vector>

class Database {
public:
    inline auto initStorage();
    int writeDbToDisk(auto storage);
    auto read(const std::string& file_name);
    int write(const std::string& file_name, std::vector<std::string> payload);
    int open_or_create(const std::string& file_name);
};


#endif //NOTCH_DATABASE_H
