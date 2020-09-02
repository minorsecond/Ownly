//
// Created by rwardrup on 8/27/2020.
//

#ifndef OWNLY_MAIN_H
#define OWNLY_MAIN_H

#include "MainWindow.h"
#include "QFileDialog"
#include <QApplication>

class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow ui{};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void updateMainTable();

private slots:
    void truncate_db();
    void remove_row();
    void clicked_submit();
};

#endif //OWNLY_MAIN_H
