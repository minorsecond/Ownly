//
// Created by rwardrup on 8/26/2020.
//

#ifndef NOTCH_DATABASE_H
#define NOTCH_DATABASE_H
#include "string"
#include <vector>

class Database {
private:
    struct Item {
        int id;
        std::string itemName;
        std::string category;
        int purchaseYear;
        int purchaseMonth;
        int purchaseDay;
        double purchasePrice;
        int count;
        bool usedInLastSixMonths;
        std::string notes;
    };
    static auto get();
    void read(const std::string& file_name);
    int write(const std::string& file_name, std::vector<std::string> payload);
public:
    int open_or_create(const std::string& file_name);
};


#endif //NOTCH_DATABASE_H
