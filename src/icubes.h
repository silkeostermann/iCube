#ifndef ICUBES_H
#define ICUBES_H

#include "Recognition/FrameProcessor.h"
#include "Recognition/Square.h"
#include "Logic/ModuleBinaryMath/BinaryMath.h"
#include "Logic/ModuleColorPalette/ColorPalette.h"
#include <QtGui/QMainWindow>
#include "ui_icubes.h"

class iCubes : public QMainWindow
{
    Q_OBJECT

	public:
		iCubes(QWidget *parent = 0);
		~iCubes();

	public slots:
		void ShowObjects (const Image** processedQuadrilaterals);

	private:
		Ui::iCubesClass ui;

		FrameProcessor m_videoStreamProcessor;
		BinaryMath m_objectProcessor;
};

#endif // ICUBES_H
