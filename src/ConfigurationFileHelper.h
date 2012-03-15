/*
 * ConfigurationFileHelper.h
 *
 *  Created on: Mar 15, 2012
 *      Author: Andrea Cuttone and Ethiel Figueira
 */

#ifndef CONFIGURATIONFILEHELPER_H_
#define CONFIGURATIONFILEHELPER_H_

#include <QList>
#include <QStringList>

class ConfigurationFileHelper {

public:
	static QList<QStringList> ReadConfiguration(QString filename);
};

#endif /* CONFIGURATIONFILEHELPER_H_ */
