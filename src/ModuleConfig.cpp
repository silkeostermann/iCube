#include "ModuleConfig.h"
#include "ConfigurationFileHelper.h"
#include <cstdio>
#include <stdlib.h>

QHash<QString, bool> ModuleConfig::shouldReload;

ModuleConfig::ModuleConfig(QString module) {
  this->module = module;
  this->load();
}

void ModuleConfig::load() {
  QString logicFilename = this->module + ".logic";
	QString recogFilename = this->module + ".recognition";

	this->buildDictFromFile(&logicDict, &logicFilename);
	this->buildDictFromFile(&recogDict, &recogFilename);
}

void ModuleConfig::reloadIfNeeded() {
  QString module = this->module;
  if (shouldReload[module] == true) {
    this->load();
    shouldReload[module] = false;
  }
}

void ModuleConfig::buildDictFromFile(QHash<int, QString> *dict, QString *filename) {
  dict->clear();
  
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
  this->reloadIfNeeded();
	return this->logicDict[id];
}

QString ModuleConfig::objectForSquare(Square *square) {
	return this->objectByContoursCount(square->GetContoursCount());
}

void ModuleConfig::invalidateModule(QString module) {
  printf("Invalidating module %s!\n", qPrintable(module));
  shouldReload[module] = true;
}