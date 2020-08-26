//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"

class Database {

    static void build();  // Build database
public:
    int open_or_create(std::string file_name);
};


#endif //NOTCH_DATABASE_H
