/********************************************************************************
** Form generated from reading UI file 'icubes.ui'
**
** Created: Fri Mar 16 08:39:10 2012
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICUBES_H
#define UI_ICUBES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_iCubesClass
{
public:
    QWidget *centralwidget;
    QLabel *labelModule;
    QComboBox *comboboxModule;
    QPushButton *buttonConfigure;
    QGroupBox *groupBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *iCubesClass)
    {
        if (iCubesClass->objectName().isEmpty())
            iCubesClass->setObjectName(QString::fromUtf8("iCubesClass"));
        iCubesClass->resize(800, 466);
        centralwidget = new QWidget(iCubesClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        labelModule = new QLabel(centralwidget);
        labelModule->setObjectName(QString::fromUtf8("labelModule"));
        labelModule->setGeometry(QRect(30, 20, 57, 14));
        comboboxModule = new QComboBox(centralwidget);
        comboboxModule->setObjectName(QString::fromUtf8("comboboxModule"));
        comboboxModule->setGeometry(QRect(130, 20, 131, 24));
        buttonConfigure = new QPushButton(centralwidget);
        buttonConfigure->setObjectName(QString::fromUtf8("buttonConfigure"));
        buttonConfigure->setGeometry(QRect(300, 20, 83, 25));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 60, 761, 361));
        iCubesClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(iCubesClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        iCubesClass->setMenuBar(menubar);
        statusbar = new QStatusBar(iCubesClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        iCubesClass->setStatusBar(statusbar);

        retranslateUi(iCubesClass);

        QMetaObject::connectSlotsByName(iCubesClass);
    } // setupUi

    void retranslateUi(QMainWindow *iCubesClass)
    {
        iCubesClass->setWindowTitle(QApplication::translate("iCubesClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        labelModule->setText(QApplication::translate("iCubesClass", "Module", 0, QApplication::UnicodeUTF8));
        comboboxModule->clear();
        comboboxModule->insertItems(0, QStringList()
         << QApplication::translate("iCubesClass", "Binary Math", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("iCubesClass", "Color Palette", 0, QApplication::UnicodeUTF8)
        );
        buttonConfigure->setText(QApplication::translate("iCubesClass", "Configure", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("iCubesClass", "Canvas", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class iCubesClass: public Ui_iCubesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICUBES_H
