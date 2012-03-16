#include "configure.h"
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "ConfigurationFileHelper.h"
#include <QFile>
#include <QTextStream>

Configure::Configure(QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle("Configure bindings");
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
		QString id = recognitionConfig.at(row).at(1);
		QString objectName;
		spinbox->setRange(0, 20);
		spinbox->setSingleStep(1);
		spinbox->setValue(recognitionConfig.at(row).at(0).toInt(0, 10));
		ui.tableWidget->setCellWidget(row, 0, spinbox);

		QComboBox *cbo = new QComboBox(ui.tableWidget);
		cbo->clear();
		cbo->insertItems(0, availableObjects);
		for(int rowLogic = 0; rowLogic < logicConfig.length(); rowLogic++)
		{
			if (logicConfig.at(rowLogic).at(0) == id)
				cbo->setCurrentIndex(rowLogic);
		}
		ui.tableWidget->setCellWidget(row, 1, cbo);
	}

	QObject::connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(ChangeFile()));
}

void Configure::ChangeFile()
{
	QList<QStringList> logicConfig = ConfigurationFileHelper::ReadConfiguration("BinaryMath.logic");
	
	QFile file("BinaryMath.recognition");
	QTextStream out(&file);
	QStringList listObjectsName;
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	    return;
	
	out << "ContourCount;ID\n";
	for(int row = 0; row < ui.tableWidget->rowCount(); row++)
	{
		QSpinBox* spinbox = (QSpinBox *) ui.tableWidget->cellWidget(row, 0);
		int contour = spinbox->value();
		QComboBox *cbo = (QComboBox *) ui.tableWidget->cellWidget(row, 1);
		QString name = cbo->currentText();
		QString id;
		for(int i = 0; i < logicConfig.length(); i++)
		{			
			if(QString::compare(logicConfig.at(i).at(1), name) == 0)
			{
				id = logicConfig.at(i).at(0);
			}	
		}
		out << contour << ";" << id << "\n";
	}	
	file.close();
}
//------------------------------------------------
Configure::~Configure()
{

}

