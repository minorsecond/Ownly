//
// Created by rwardrup on 8/27/2020.
//

#ifndef OWNLY_MAIN_H
#define OWNLY_MAIN_H

#include "MainWindow.h"
#include "Database.h"
#include <QApplication>
#include <QtGui>

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
