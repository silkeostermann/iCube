/********************************************************************************
** Form generated from reading UI file 'configure.ui'
**
** Created: Fri Mar 16 08:39:10 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURE_H
#define UI_CONFIGURE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigureDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidget;

    void setupUi(QDialog *ConfigureDialog)
    {
        if (ConfigureDialog->objectName().isEmpty())
            ConfigureDialog->setObjectName(QString::fromUtf8("ConfigureDialog"));
        ConfigureDialog->resize(544, 324);
        buttonBox = new QDialogButtonBox(ConfigureDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(190, 280, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableWidget = new QTableWidget(ConfigureDialog);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 521, 261));

        retranslateUi(ConfigureDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConfigureDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConfigureDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConfigureDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigureDialog)
    {
        ConfigureDialog->setWindowTitle(QApplication::translate("ConfigureDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigureDialog: public Ui_ConfigureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURE_H
