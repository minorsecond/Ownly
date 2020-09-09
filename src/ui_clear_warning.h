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

class Ui_Dialog
{
public:
    QDialogButtonBox *clearWarningButtons;
    QLabel *clearWarningLabel;
    QLabel *clearWarningText;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 99);
        clearWarningButtons = new QDialogButtonBox(Dialog);
        clearWarningButtons->setObjectName(QString::fromUtf8("clearWarningButtons"));
        clearWarningButtons->setGeometry(QRect(290, 20, 81, 241));
        clearWarningButtons->setOrientation(Qt::Vertical);
        clearWarningButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        clearWarningLabel = new QLabel(Dialog);
        clearWarningLabel->setObjectName(QString::fromUtf8("clearWarningLabel"));
        clearWarningLabel->setGeometry(QRect(16, 10, 261, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        clearWarningLabel->setFont(font);
        clearWarningLabel->setTextFormat(Qt::AutoText);
        clearWarningLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        clearWarningText = new QLabel(Dialog);
        clearWarningText->setObjectName(QString::fromUtf8("clearWarningText"));
        clearWarningText->setGeometry(QRect(10, 30, 271, 51));
        clearWarningText->setWordWrap(true);

        retranslateUi(Dialog);
        QObject::connect(clearWarningButtons, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(clearWarningButtons, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Clear Data", nullptr));
        clearWarningLabel->setText(QCoreApplication::translate("Dialog", "Warning", nullptr));
        clearWarningText->setText(QCoreApplication::translate("Dialog", "You are about to erase all of your data. Proceed with caution.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEAR_WARNING_H
