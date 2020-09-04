/********************************************************************************
** Form generated from reading UI file 'ExportOptions.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef EXPORTOPTIONS_H
#define EXPORTOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ExportOptions
{
public:
    QDialogButtonBox *ExportButtonOkCancelButtons;
    QLabel *PathLabel;
    QLineEdit *ExportOutputPathInput;
    QRadioButton *CSVRadioButton;
    QComboBox *ExportCategoryFilter;
    QLabel *label;

    void setupUi(QDialog *ExportOptions)
    {
        if (ExportOptions->objectName().isEmpty())
            ExportOptions->setObjectName(QString::fromUtf8("ExportOptions"));
        ExportOptions->resize(490, 88);
        ExportButtonOkCancelButtons = new QDialogButtonBox(ExportOptions);
        ExportButtonOkCancelButtons->setObjectName(QString::fromUtf8("ExportButtonOkCancelButtons"));
        ExportButtonOkCancelButtons->setGeometry(QRect(400, 20, 81, 241));
        ExportButtonOkCancelButtons->setOrientation(Qt::Vertical);
        ExportButtonOkCancelButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        PathLabel = new QLabel(ExportOptions);
        PathLabel->setObjectName(QString::fromUtf8("PathLabel"));
        PathLabel->setGeometry(QRect(10, 20, 31, 16));
        ExportOutputPathInput = new QLineEdit(ExportOptions);
        ExportOutputPathInput->setObjectName(QString::fromUtf8("ExportOutputPathInput"));
        ExportOutputPathInput->setGeometry(QRect(40, 20, 331, 20));
        CSVRadioButton = new QRadioButton(ExportOptions);
        CSVRadioButton->setObjectName(QString::fromUtf8("CSVRadioButton"));
        CSVRadioButton->setGeometry(QRect(270, 50, 41, 17));
        CSVRadioButton->setChecked(true);
        ExportCategoryFilter = new QComboBox(ExportOptions);
        ExportCategoryFilter->setObjectName(QString::fromUtf8("ExportCategoryFilter"));
        ExportCategoryFilter->setGeometry(QRect(40, 50, 221, 22));
        label = new QLabel(ExportOptions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 31, 16));

        retranslateUi(ExportOptions);
        QObject::connect(ExportButtonOkCancelButtons, SIGNAL(accepted()), ExportOptions, SLOT(accept()));
        QObject::connect(ExportButtonOkCancelButtons, SIGNAL(rejected()), ExportOptions, SLOT(reject()));

        QMetaObject::connectSlotsByName(ExportOptions);
    } // setupUi

    void retranslateUi(QDialog *ExportOptions)
    {
        ExportOptions->setWindowTitle(QCoreApplication::translate("ExportOptions", "Export Options", nullptr));
        PathLabel->setText(QCoreApplication::translate("ExportOptions", "Path:", nullptr));
        CSVRadioButton->setText(QCoreApplication::translate("ExportOptions", "CSV", nullptr));
        label->setText(QCoreApplication::translate("ExportOptions", "Filter:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportOptions: public Ui_ExportOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // EXPORTOPTIONS_H
