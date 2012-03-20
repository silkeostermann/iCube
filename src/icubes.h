#ifndef ICUBES_H
#define ICUBES_H

#include <cstdio>
#include <QLabel>
#include <QTimer>
#include <QHash>
#include <QtGui/QMainWindow>

#include "configure.h"
#include "Recognition/FrameProcessor.h"
#include "Recognition/Square.h"
#include "Logic/ModuleInterface.h"
#include "Logic/Image.h"
#include "ui_icubes.h"

class iCubes : public QMainWindow
{
    Q_OBJECT

	public:
		iCubes(QWidget *parent = 0);
		~iCubes();

	public slots:
		void ShowObjects (const Image*, int);
		void ShowConfigureDialog();
    void changeModule(const QString &text);

	private:
		const static int SIZE = 10;
    
    void configureInterface();
    void setupModules();
    void registerModule(ModuleInterface *module);
    void updateModulesCombo();
    
    void setupModule (QObject *module); // TODO: Rename this method to connectModule
    void disconnectModule(QObject *module);

		Ui::iCubesClass ui;

    QHash<QString, QObject *> modules;
    QObject *currentModule;

		FrameProcessor  m_frameProcessor;

		QLabel* m_labels [SIZE];

};

#endif // ICUBES_H
