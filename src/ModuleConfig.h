/*
 * ModuleConfig.h
 *
 *      Author: Vojto Rinik
 */

#ifndef MODULE_CONFIG_H
#define MODULE_CONFIG_H

#include <QList>
#include <QStringList>
#include <QHash>

#include "Recognition/Square.h"

class ModuleConfig {

public:
	ModuleConfig(QString module);
	QString objectForSquare(Square *square);
	
private:
	QHash<int, QString> logicDict;
	QHash<int, QString>	recogDict;
	
	void buildDictFromFile(QHash<int, QString> *dict, QString *filename);
	QString objectById(int id);
	QString objectByContoursCount(int contourCount);

};

#endif