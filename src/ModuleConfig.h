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
  static void invalidateModule(QString module);
	
private:
  QString module;
  static QHash<QString, bool> shouldReload; /**< This dict is used to reload config for some module */
	QHash<int, QString> logicDict;
	QHash<int, QString>	recogDict;
	
  void load();
	void buildDictFromFile(QHash<int, QString> *dict, QString *filename);
	QString objectById(int id);
	QString objectByContoursCount(int contourCount);
  void reloadIfNeeded();

};

#endif