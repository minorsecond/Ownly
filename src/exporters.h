//
// Created by rwardrup on 9/4/2020.
//

#ifndef OWNLY_EXPORTERS_H
#define OWNLY_EXPORTERS_H

#include "Database.h"

class exporters {
    /*
     * Methods for exporting from database file to flat files.
     */
public:
    static void to_csv(const std::vector<Item>& items, const std::string& path);
};

#endif //OWNLY_EXPORTERS_H
