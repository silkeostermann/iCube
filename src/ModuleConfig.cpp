#include "ModuleConfig.h"
#include "ConfigurationFileHelper.h"
#include <cstdio>
#include <stdlib.h>

ModuleConfig::ModuleConfig(QString module) {
	QString logicFilename = module + ".logic";
	QString recogFilename = module + ".recognition";
	
	this->buildDictFromFile(&logicDict, &logicFilename);
	this->buildDictFromFile(&recogDict, &recogFilename);
	
	QString objectName = this->objectByContoursCount(3);
}

void ModuleConfig::buildDictFromFile(QHash<int, QString> *dict, QString *filename) {
	printf("Loading file %s\n", qPrintable(*filename));
	QList<QStringList> list = ConfigurationFileHelper::ReadConfiguration(*filename);
	
	for (int i = 0; i < list.size(); i++) {
		QStringList row = list.at(i);
		QString idString = row.at(0);
		int id = atoi(qPrintable(idString));
		QString objectName = row.at(1);
		
		(* dict)[id] = objectName;
	}
}

QString ModuleConfig::objectByContoursCount(int contourCount) {
	QString idString = this->recogDict[contourCount];
	int id = atoi(qPrintable(idString));
	return this->objectById(id);
}

QString ModuleConfig::objectById(int id) {
	return this->logicDict[id];
}
