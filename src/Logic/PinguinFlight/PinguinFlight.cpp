#include "PinguinFlight.h"
#include <cstdio>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtCore/QRect>

#include <opencv/highgui.h>

// Here goes member definition


//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

PinguinFlight::PinguinFlight()
{
	this->image = new QImage ("./Logic/PinguinFlight/pinguin.png");
}

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
	printf ("[PENGUIN] Processing the squares\n");

	Image images [size];
	for (int i=0; i < size; i++)
	{
		CvPoint centCoord = recognizedSquares [i].GetCenterCoordinates ();
		images [i] = Image (*image, QPoint (centCoord.x, centCoord.y));
	}

	printf ("[PENGUIN] %d pinguins found.\n", size);
	SquaresProcessed (images, size);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

PinguinFlight::~PinguinFlight ()
{
	delete image;
}

//void GetColor()
