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

PinguinFlight::PinguinFlight() {
  QString fileName = "./Logic/PinguinFlight/pinguin.png";
	this->image =         new QImage(fileName);
}

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
	printf("[PENGUIN] Processing the squares\n");
	Image images[size];
	for (int i=0;i<size;i++) {
		Square pinguin = recognizedSquares[i];
		CvPoint point	= pinguin.GetCenterCoordinates();
		Image *pinguinImage =  new Image(*(this->image), QPoint(point.x, point.y));
		images[i] = *pinguinImage;
	}

	SquaresProcessed((const Image *)images, size);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

PinguinFlight::~PinguinFlight ()
{
}

//void GetColor()
