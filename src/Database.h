//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"

class Database {

    static auto get();
    static void read(const std::string& file_name);
public:
    static int open_or_create(const std::string& file_name);
};


#endif //NOTCH_DATABASE_H
