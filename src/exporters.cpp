//
// Created by rwardrup on 9/4/2020.
//

#include <fstream>
#include "exporters.h"

void exporters::to_csv(const std::vector<Item>& items, const std::string& path) {
    /*
     * Creates a CSV file containing the current contents of the database.
     * @param items: Vector of Items containing attributes for individual items.
     * @param path: path to CSV save location
     */

    std::ofstream output_csv(path);

    // Create header
    output_csv << "item_name,";
    output_csv << "category,";
    output_csv << "purchase_date,";
    output_csv << "purchase_price,";
    output_csv << "count,";
    output_csv << "used_frequently,";
    output_csv << "notes,\n";

    for (const auto& item : items) {
        std::string used_frequently = "No";
        std::string purchase_date = std::to_string(item.purchaseYear) + "/" + std::to_string(item.purchaseMonth) + "/" + std::to_string(item.purchaseDay);

        if (item.usedFrequently)
            used_frequently = "Yes";

        output_csv << item.itemName + ",";
        output_csv << item.category + ",";
        output_csv << purchase_date + ",";
        output_csv << std::to_string(item.purchasePrice) + ",";
        output_csv << std::to_string(item.count) + ",";
        output_csv << used_frequently + ",";
        output_csv << item.notes + ",\n";
    }

    output_csv.close();
}
