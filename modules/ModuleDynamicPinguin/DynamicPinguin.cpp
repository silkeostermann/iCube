#include "DynamicPinguin.h"
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

QString DynamicPinguin::moduleName() {
  return "Pinguing Flight";
}

DynamicPinguin::DynamicPinguin()
{
	penguin0 = QImage("./Logic/ModuleDynamicPinguin/pinguin0.png");
	penguin90 = QImage("./Logic/ModuleDynamicPinguin/pinguin90.png");
	penguin180 = QImage("./Logic/ModuleDynamicPinguin/pinguin180.png");
	penguin270 = QImage("./Logic/ModuleDynamicPinguin/pinguin270.png");
}

void DynamicPinguin::ProcessSquares (const Square *recognizedSquares, int size)
{
  printf("[DynamicPinguin] ProcessSquares\n");
  
	Image *images = new Image [size];
	for (int i=0; i < size; i++)
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
	
	emit SquaresProcessed (images, size);
	delete [] images;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

DynamicPinguin::~DynamicPinguin () {}

Q_EXPORT_PLUGIN2(cubes_dynpinguin, DynamicPinguin)