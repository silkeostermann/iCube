#include "PinguinFlight.h"
#include <cstdio>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QTransform>
#include <QtCore/QRect>

#include <opencv/highgui.h>

// Here goes member definition


//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

PinguinFlight::PinguinFlight()
{
	penguin0 = QImage("./Logic/PinguinFlight/pinguin0.png");
	penguin90 = QImage("./Logic/PinguinFlight/pinguin90.png");
	penguin180 = QImage("./Logic/PinguinFlight/pinguin180.png");
	penguin270 = QImage("./Logic/PinguinFlight/pinguin270.png");
}

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
	//printf ("[PENGUIN] Processing the squares\n");

	Image images [1];
	for (int i=0; i < 1; i++)
	{
		QImage *img;
		if(recognizedSquares[i].GetAngle() == 0) {
			img = &penguin0;
		}
		else if(recognizedSquares[i].GetAngle() == 90) {
			img = &penguin90;
		}
		else if(recognizedSquares[i].GetAngle() == 180) {
			img = &penguin180;
		}
		else if(recognizedSquares[i].GetAngle() == 270) {
			img = &penguin270;
		}
		CvPoint centCoord = recognizedSquares [i].GetCenterCoordinates ();
		images[i] = Image (*img, QPoint (centCoord.x, centCoord.y));
	}
	
	//printf ("[PENGUIN] %d pinguins found.\n", size);
	SquaresProcessed (images, size);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

PinguinFlight::~PinguinFlight ()
{

}

//void GetColor()
