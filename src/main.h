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
    Q_OBJECT
    Ui::MainWindow ui{};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void updateMainTable();
    void populate_categories();
    void export_to_csv();

private:
    void populate_fields(Item item);
    void populate_table(std::vector<Item> items);

private slots:
    void truncate_db();
    void remove_row();
    void table_row_clicked(const QItemSelection &, const QItemSelection &);
    void clicked_submit();
    std::string double_to_string(double input_double);
    void clear_fields();
    void filter_by_categories();
    void open_export_dialog();
};

#endif //OWNLY_MAIN_H
