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
#include "Logic/Pong/pong.h"
#include <QtGui/QMainWindow>
#include <QLabel>
#include <QCloseEvent>
#include "ui_icubes.h"

class iCubes : public QMainWindow
{
	Q_OBJECT

	public:
		iCubes (QWidget* parent = 0);
		void closeEvent (QCloseEvent*);

		~iCubes ();

	public slots:
		void ShowObjects (const Image*, int);
		void ShowConfigureDialog ();
    		void ChangeModule (const QString &text);

		void StartStop ();

	private:
		void ConfigureInterface ();
    		void SetupModules ();
    		void SetupModule (QObject* module);
    		void DisconnectModule (QObject* module);
	
		static const int MAX_VIRTUAL_OBJECT_COUNT = 10;

		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 466;

		Ui::iCubesClass m_ui;

    		QHash <QString, QObject*> m_modules;
    		QObject* m_currentModule;

		FrameProcessor m_frameProcessor;
		BinaryMath m_binMath;
		ColorPalette m_colorPalette;
		PinguinFlight m_pinguinFlight;
		Pong m_pong;

		QLabel* m_labels [MAX_VIRTUAL_OBJECT_COUNT];
};
#endif
