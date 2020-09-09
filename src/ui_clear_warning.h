/********************************************************************************
** Form generated from reading UI file 'ui_clear_warning.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLEAR_WARNING_H
#define UI_CLEAR_WARNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ClearDialog
{
public:
    QDialogButtonBox *clearWarningButtons;
    QLabel *clearWarningLabel;
    QLabel *clearWarningText;

    void setupUi(QDialog *ClearDialog)
    {
        if (ClearDialog->objectName().isEmpty())
            ClearDialog->setObjectName(QString::fromUtf8("ClearDialog"));
        ClearDialog->resize(400, 99);
        clearWarningButtons = new QDialogButtonBox(ClearDialog);
        clearWarningButtons->setObjectName(QString::fromUtf8("clearWarningButtons"));
        clearWarningButtons->setGeometry(QRect(290, 20, 81, 241));
        clearWarningButtons->setOrientation(Qt::Vertical);
        clearWarningButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        clearWarningLabel = new QLabel(ClearDialog);
        clearWarningLabel->setObjectName(QString::fromUtf8("clearWarningLabel"));
        clearWarningLabel->setGeometry(QRect(16, 10, 261, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        clearWarningLabel->setFont(font);
        clearWarningLabel->setTextFormat(Qt::AutoText);
        clearWarningLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        clearWarningText = new QLabel(ClearDialog);
        clearWarningText->setObjectName(QString::fromUtf8("clearWarningText"));
        clearWarningText->setGeometry(QRect(10, 30, 271, 51));
        clearWarningText->setWordWrap(true);

        retranslateUi(ClearDialog);
        QObject::connect(clearWarningButtons, SIGNAL(accepted()), ClearDialog, SLOT(accept()));
        QObject::connect(clearWarningButtons, SIGNAL(rejected()), ClearDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ClearDialog);
    } // setupUi

    void retranslateUi(QDialog *ClearDialog)
    {
        ClearDialog->setWindowTitle(QCoreApplication::translate("ClearDialog", "Clear Data", nullptr));
        clearWarningLabel->setText(QCoreApplication::translate("ClearDialog", "Warning", nullptr));
        clearWarningText->setText(QCoreApplication::translate("ClearDialog", "You are about to erase all of your data. Proceed with caution.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClearDialog: public Ui_ClearDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEAR_WARNING_H
