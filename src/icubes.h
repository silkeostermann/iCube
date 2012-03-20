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
#include "Logic/Image.h"
#include "Logic/ModuleBinaryMath/BinaryMath.h"
#include "Logic/ModuleColorPalette/ColorPalette.h"
#include "Logic/PinguinFlight/PinguinFlight.h"
#include <QtGui/QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include "ui_icubes.h"

class iCubes : public QMainWindow
{
    Q_OBJECT

	public:
		iCubes(QWidget *parent = 0);
		void closeEvent(QCloseEvent *);

		~iCubes();

	public slots:
		void ShowObjects (const Image*, int);
		void demoSquares();
		void ShowConfigureDialog();
    void changeModule(const QString &text);

		void StartStop();

	private:
		const static int SIZE = 10;
    
    void configureInterface();
    void setupModules();
    void setupModule (QObject *module);
    void disconnectModule(QObject *module);

		Ui::iCubesClass ui;

    QHash<QString, QObject *> modules;
    QObject *currentModule;

		FrameProcessor  m_frameProcessor;
		BinaryMath      m_binMath;
		ColorPalette    m_colorPalette;
		PinguinFlight   m_pinguinFlight;

		QLabel* m_labels [SIZE];

};

#endif // ICUBES_H
