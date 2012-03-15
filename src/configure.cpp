/*
 * Configure.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: Andrea Cuttone and Ethiel Figueira
 */

#include "configure.h"
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "ConfigurationFileHelper.h"

Configure::Configure(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle("Configure Bindings");
	QStringList headers;
	headers.append("Contour Count");
	headers.append("Name");
	QList<QStringList> recognitionConfig = ConfigurationFileHelper::ReadConfiguration("BinaryMath.recognition");
	QList<QStringList> logicConfig = ConfigurationFileHelper::ReadConfiguration("BinaryMath.logic");
	QStringList availableObjects;
	for(int row = 0; row < logicConfig.length(); row++)
	{
		availableObjects.append(logicConfig.at(row).at(1));
	}

	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setRowCount(recognitionConfig.length());
	ui.tableWidget->setHorizontalHeaderLabels(headers);
	ui.tableWidget->verticalHeader()->hide();
	for(int row = 0; row < recognitionConfig.length(); row++)
	{
		QSpinBox* spinbox = new QSpinBox(ui.tableWidget);
		spinbox->setRange(-20, 20);
		spinbox->setSingleStep(1);
		spinbox->setValue(recognitionConfig.at(row).at(0).toInt(0, 10));
		ui.tableWidget->setCellWidget(row, 0, spinbox);
		QComboBox *cbo = new QComboBox(ui.tableWidget);
		cbo->clear();
		cbo->insertItems(0, availableObjects);
		ui.tableWidget->setCellWidget(row, 1, cbo);
	}
}
//---------------------------------------------------------------

Configure::~Configure()
{

}
