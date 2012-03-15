/*
 * ConfigurationFileHelper.cpp
 *
 *  Created on: Mar 15, 2012
 *      Author: Andrea Cuttone and Ethiel Figueira
 */

#include "ConfigurationFileHelper.h"
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>

QList<QStringList> ConfigurationFileHelper::ReadConfiguration(QString filename)
{
	QFile file(filename);
	QTextStream in(&file);
	QList<QStringList> list;
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	         return list;

	in.readLine(); // skip header row
	while(!in.atEnd()) {
		QString line = in.readLine();
	    QStringList  fields = line.split(";");
	    list.append(fields);
	}
	file.close();
	return list;
}
