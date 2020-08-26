/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Item;
    QAction *actionQt5;
    QWidget *centralwidget;
    QComboBox *ViewCategoryComboBox;
    QLabel *ViewCategoryLabel;
    QListWidget *InventoryList;
    QFrame *line;
    QLineEdit *ItemName;
    QFrame *line_2;
    QLabel *ItemNameLabel;
    QLabel *ItemCategoryLabel;
    QDateEdit *ItemPurchaseDate;
    QLabel *ItemPurchaseDateLabel;
    QTextEdit *ItemNotes;
    QLabel *ItemNotesLabel;
    QLabel *ItemPurchasePriceLabel;
    QLineEdit *ItemPurchasePrice;
    QLabel *InventoryListLabel;
    QComboBox *ItemCategory;
    QCheckBox *ItemUsedInLastSixMonths;
    QFrame *line_3;
    QLabel *ItemCountLabel;
    QSpinBox *ItemCount;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 537);
        actionNew_Item = new QAction(MainWindow);
        actionNew_Item->setObjectName(QString::fromUtf8("actionNew_Item"));
        actionQt5 = new QAction(MainWindow);
        actionQt5->setObjectName(QString::fromUtf8("actionQt5"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ViewCategoryComboBox = new QComboBox(centralwidget);
        ViewCategoryComboBox->setObjectName(QString::fromUtf8("ViewCategoryComboBox"));
        ViewCategoryComboBox->setGeometry(QRect(10, 50, 211, 22));
        ViewCategoryComboBox->setMaxVisibleItems(29);
        ViewCategoryLabel = new QLabel(centralwidget);
        ViewCategoryLabel->setObjectName(QString::fromUtf8("ViewCategoryLabel"));
        ViewCategoryLabel->setGeometry(QRect(10, 30, 211, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(10);
        ViewCategoryLabel->setFont(font);
        ViewCategoryLabel->setAlignment(Qt::AlignCenter);
        InventoryList = new QListWidget(centralwidget);
        InventoryList->setObjectName(QString::fromUtf8("InventoryList"));
        InventoryList->setGeometry(QRect(10, 120, 391, 371));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 80, 781, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        ItemName = new QLineEdit(centralwidget);
        ItemName->setObjectName(QString::fromUtf8("ItemName"));
        ItemName->setGeometry(QRect(420, 120, 371, 20));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(406, 100, 10, 391));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        ItemNameLabel = new QLabel(centralwidget);
        ItemNameLabel->setObjectName(QString::fromUtf8("ItemNameLabel"));
        ItemNameLabel->setGeometry(QRect(420, 100, 371, 20));
        ItemNameLabel->setFont(font);
        ItemNameLabel->setAlignment(Qt::AlignCenter);
        ItemCategoryLabel = new QLabel(centralwidget);
        ItemCategoryLabel->setObjectName(QString::fromUtf8("ItemCategoryLabel"));
        ItemCategoryLabel->setGeometry(QRect(420, 150, 191, 20));
        ItemCategoryLabel->setFont(font);
        ItemCategoryLabel->setAlignment(Qt::AlignCenter);
        ItemPurchaseDate = new QDateEdit(centralwidget);
        ItemPurchaseDate->setObjectName(QString::fromUtf8("ItemPurchaseDate"));
        ItemPurchaseDate->setGeometry(QRect(620, 170, 171, 22));
        ItemPurchaseDateLabel = new QLabel(centralwidget);
        ItemPurchaseDateLabel->setObjectName(QString::fromUtf8("ItemPurchaseDateLabel"));
        ItemPurchaseDateLabel->setGeometry(QRect(620, 150, 171, 20));
        ItemPurchaseDateLabel->setFont(font);
        ItemPurchaseDateLabel->setAlignment(Qt::AlignCenter);
        ItemNotes = new QTextEdit(centralwidget);
        ItemNotes->setObjectName(QString::fromUtf8("ItemNotes"));
        ItemNotes->setGeometry(QRect(420, 290, 371, 201));
        ItemNotesLabel = new QLabel(centralwidget);
        ItemNotesLabel->setObjectName(QString::fromUtf8("ItemNotesLabel"));
        ItemNotesLabel->setGeometry(QRect(420, 270, 371, 20));
        ItemNotesLabel->setFont(font);
        ItemNotesLabel->setAlignment(Qt::AlignCenter);
        ItemPurchasePriceLabel = new QLabel(centralwidget);
        ItemPurchasePriceLabel->setObjectName(QString::fromUtf8("ItemPurchasePriceLabel"));
        ItemPurchasePriceLabel->setGeometry(QRect(420, 200, 191, 20));
        ItemPurchasePriceLabel->setFont(font);
        ItemPurchasePriceLabel->setAlignment(Qt::AlignCenter);
        ItemPurchasePrice = new QLineEdit(centralwidget);
        ItemPurchasePrice->setObjectName(QString::fromUtf8("ItemPurchasePrice"));
        ItemPurchasePrice->setGeometry(QRect(420, 220, 191, 20));
        InventoryListLabel = new QLabel(centralwidget);
        InventoryListLabel->setObjectName(QString::fromUtf8("InventoryListLabel"));
        InventoryListLabel->setGeometry(QRect(10, 100, 391, 20));
        InventoryListLabel->setFont(font);
        InventoryListLabel->setAlignment(Qt::AlignCenter);
        ItemCategory = new QComboBox(centralwidget);
        ItemCategory->setObjectName(QString::fromUtf8("ItemCategory"));
        ItemCategory->setGeometry(QRect(420, 170, 191, 22));
        ItemCategory->setEditable(true);
        ItemUsedInLastSixMonths = new QCheckBox(centralwidget);
        ItemUsedInLastSixMonths->setObjectName(QString::fromUtf8("ItemUsedInLastSixMonths"));
        ItemUsedInLastSixMonths->setGeometry(QRect(670, 220, 121, 20));
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(550, 260, 118, 3));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        ItemCountLabel = new QLabel(centralwidget);
        ItemCountLabel->setObjectName(QString::fromUtf8("ItemCountLabel"));
        ItemCountLabel->setGeometry(QRect(620, 200, 41, 20));
        ItemCountLabel->setFont(font);
        ItemCountLabel->setAlignment(Qt::AlignCenter);
        ItemCount = new QSpinBox(centralwidget);
        ItemCount->setObjectName(QString::fromUtf8("ItemCount"));
        ItemCount->setGeometry(QRect(620, 220, 42, 22));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionQt5);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_Item->setText(QCoreApplication::translate("MainWindow", "New Item", nullptr));
        actionQt5->setText(QCoreApplication::translate("MainWindow", "Qt5", nullptr));
        ViewCategoryComboBox->setCurrentText(QCoreApplication::translate("MainWindow", "All", nullptr));
        ViewCategoryComboBox->setPlaceholderText(QCoreApplication::translate("MainWindow", "All", nullptr));
        ViewCategoryLabel->setText(QCoreApplication::translate("MainWindow", "View Category", nullptr));
        ItemNameLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        ItemCategoryLabel->setText(QCoreApplication::translate("MainWindow", "Category", nullptr));
        ItemPurchaseDateLabel->setText(QCoreApplication::translate("MainWindow", "Purchase Date", nullptr));
        ItemNotesLabel->setText(QCoreApplication::translate("MainWindow", "Notes", nullptr));
        ItemPurchasePriceLabel->setText(QCoreApplication::translate("MainWindow", "Purchase Price", nullptr));
        InventoryListLabel->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        ItemCategory->setCurrentText(QString());
        ItemCategory->setPlaceholderText(QCoreApplication::translate("MainWindow", "All", nullptr));
        ItemUsedInLastSixMonths->setText(QCoreApplication::translate("MainWindow", "Used in last 6 months", nullptr));
        ItemCountLabel->setText(QCoreApplication::translate("MainWindow", "Count", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
