//
// Created by rwardrup on 8/27/2020.
//

#ifndef OWNLY_MAIN_H
#define OWNLY_MAIN_H

#include "MainWindow.h"
#include "Database.h"
#include <QApplication>
#include <QtGui>

inline static std::string set_db_path() {
    /*
     * Get the path to the users APPDATA directory for database storage.
     * @return database_path: Path where database will be stored.
     */

    std::string database_path;
    PWSTR localAppData = NULL;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &localAppData) == S_OK) {
        std::wstring ws_path(localAppData);
        std::string database_directory;
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;
        database_directory = converter.to_bytes(ws_path) + "\\Ownly";
        database_path = database_directory + "\\ownly_data.db";
        CoTaskMemFree(static_cast<void*>(localAppData));

        CreateDirectory(database_directory.c_str(), NULL);
        std::cout << "DB path: " << database_path << std::endl;
    }

    return database_path;
}

class MainWindow : public QMainWindow {
    /*
     * Main Window GUI methods.
     */

    Q_OBJECT
    Ui::MainWindow ui{};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void updateMainTable();
    void populate_categories();

private:
    void populate_fields(Item item);
    void populate_table(std::vector<Item> items);
    std::string database_path;

private slots:
    void truncate_db();
    void remove_row();
    void table_row_clicked(const QItemSelection &, const QItemSelection &);  // Handle event where table row is clicked.
    void clicked_submit();
    std::string double_to_string(double input_double);  // Convert a double to a string with two decimal points.
    void clear_fields();  // Clear all user-entry fields.
    void filter_by_categories();  // Filter table by category.
    void open_export_dialog();
};

#endif //OWNLY_MAIN_H
