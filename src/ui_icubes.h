/********************************************************************************
** Form generated from reading UI file 'icubes.ui'
**
** Created: Fri Mar 9 01:05:37 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICUBES_H
#define UI_ICUBES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_iCubesClass
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *iCubesClass)
    {
        if (iCubesClass->objectName().isEmpty())
            iCubesClass->setObjectName(QString::fromUtf8("iCubesClass"));
        iCubesClass->resize(800, 600);
        centralwidget = new QWidget(iCubesClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
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
    } // retranslateUi

};

namespace Ui {
    class iCubesClass: public Ui_iCubesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICUBES_H
