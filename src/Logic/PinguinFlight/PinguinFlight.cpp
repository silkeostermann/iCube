#include "PinguinFlight.h"
#include <cstdio>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QImage>
#include <QtGui/QColor>
#include <QtGui/QTransform>
#include <QtCore/QRect>
#include <QThread>
#include <opencv/highgui.h>

// Here goes member definition

//


//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

PinguinFlight::PinguinFlight()
{
	chosenImage=0;

	northpole = QImage("./Logic/PinguinFlight/northpole.jpg");
	penguin0a = QImage("./Logic/PinguinFlight/pinguin0a.png");
	penguin90a = QImage("./Logic/PinguinFlight/pinguin90a.png");
	penguin180a = QImage("./Logic/PinguinFlight/pinguin180a.png");
	penguin270a = QImage("./Logic/PinguinFlight/pinguin270a.png");
	penguin0b = QImage("./Logic/PinguinFlight/pinguin0b.png");
	penguin90b = QImage("./Logic/PinguinFlight/pinguin90b.png");
	penguin180b = QImage("./Logic/PinguinFlight/pinguin180b.png");
	penguin270b = QImage("./Logic/PinguinFlight/pinguin270b.png");


}

void PinguinFlight::ProcessSquares (const Square *recognizedSquares, int size)
{
	//printf("IN PENGUIN: %d\n", QThread::currentThreadId());
  printf("[PinguinFlight] ProcessSquares\n");
  
	Image *images = new Image [size+1];


	images[0] = Image (northpole, QPoint (1, 1));
	for (int i=0, t = 1; i < size; i++, t++)
	{
		QImage *img;
		if(recognizedSquares[i].GetAngle() == 0) {
			if(chosenImage==0){
				img = &penguin0a;
			} else {
				img = &penguin0b;
			}
		}
		else if(recognizedSquares[i].GetAngle() == 90) {
			if(chosenImage==0){
				img = &penguin90a;
			} else {
				img = &penguin90b;
			}		}
		else if(recognizedSquares[i].GetAngle() == 180) {
			if(chosenImage==0){
				img = &penguin180a;
			} else {
				img = &penguin180b;
			}		}
		else if(recognizedSquares[i].GetAngle() == 270) {
			if(chosenImage==0){
				img = &penguin270a;
			} else {
				img = &penguin270b;
			}		}
		CvPoint centCoord = recognizedSquares [i].GetCenterCoordinates ();
		centCoord.x = centCoord.x * 6;
		centCoord.y = centCoord.y * 4;
		images[t] = Image (*img, QPoint (centCoord.x, centCoord.y));
	}

	if(chosenImage==0){
		chosenImage=1;
	} else {
		chosenImage=0;
	}

	emit SquaresProcessed (images, size+1);
	delete [] images;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

PinguinFlight::~PinguinFlight ()
{

}

//void GetColor()
