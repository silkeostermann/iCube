#ifndef ICUBES_H
#define ICUBES_H

#include "configure.h"
#include "Recognition/FrameProcessor.h"
#include "Recognition/Square.h"
#include "Logic/Image.h"
#include "Logic/ModuleBinaryMath/BinaryMath.h"
#include "Logic/ModuleColorPalette/ColorPalette.h"
#include "Logic/PinguinFlight/PinguinFlight.h"
#include <QtGui/QMainWindow>
#include <QLabel>
#include "ui_icubes.h"
#include <QTimer>
#include <cstdio>

class iCubes : public QMainWindow
{
    Q_OBJECT

	public:
		iCubes(QWidget *parent = 0);

		void setupModule (QObject *module);

		~iCubes();

	public slots:
		void ShowObjects (const Image*, int);

		void demoSquares();

		void ShowConfigureDialog ();

	private:
		const static int SIZE = 10;

		Ui::iCubesClass ui;

		FrameProcessor m_frameProcessor;
		BinaryMath m_binMath;
		ColorPalette m_colorPalette;
		PinguinFlight m_pinguinFlight;

		Configure* m_configurator;
		QLabel* m_labels [SIZE];

};

#endif // ICUBES_H
