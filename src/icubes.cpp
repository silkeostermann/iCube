#include "icubes.h"
#include <stdio.h>

iCubes::iCubes(QWidget *parent)
    : QMainWindow(parent)
{
	printf("Consturctor of iCubes called");
	ui.setupUi(this);

    FrameProcessor m_videoStreamProcessor;

    BinaryMath m_objectProcessor;

	QObject::connect(&m_videoStreamProcessor, SIGNAL (QuadrilateralsRecognized (const Quadrilateral**)),
						&m_objectProcessor, SLOT (ProcessQuadrilaterals (const Quadrilateral**)));

	int webCamId = 1;
	int fps = 30;
	m_videoStreamProcessor.BeginRead (webCamId, fps);


	QObject::connect(&m_objectProcessor, SIGNAL (QuadrilateralsProcessed (const Image**)),
						this, SLOT (ShowObjects (const Image**)));
}


//---------------------------------------------------------------
// Gets processed objects which to draw.
// Expects pointer on valid processed objects array.
//---------------------------------------------------------------

void iCubes::ShowObjects (const Image** processedQuadrilaterals)
{
	// NOTE: Find out if it is safe to change GUI elements from invoked signal.
	// NOTE: It might be required to use InvokeMethod ()
}

//---------------------------------------------------------------

iCubes::~iCubes()
{
	m_videoStreamProcessor.EndRead ();
}
