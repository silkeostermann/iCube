#include "ColorPalette.h"
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

ColorPalette::ColorPalette() {
	printf("Constructing color palette.\n");

	// Prepare the UI images
	this->interface = new QImage(QSize(640, 640), QImage::Format_RGB16);
	this->interface->load("interface.jpg");
	this->ball = new QImage(QSize(52, 54), QImage::Format_RGB16);
	this->ball->load("ball.png");

	// Prepare the bar images
	this->redbar = new QImage(QSize(300, 20), QImage::Format_RGB16);
	this->redbar->load("Bar_Red.png");

	this->greenbar = new QImage(QSize(300, 20), QImage::Format_RGB16);
	this->greenbar->load("Bar_Green.png");

	this->bluebar = new QImage(QSize(300, 20), QImage::Format_RGB16);
	this->bluebar->load("Bar_Blue.png");
}

void ColorPalette::ProcessSquares (const Square **recognizedSquares, int size)
{
	printf("Processing %d squares.\n", (int)size);

	const Square *blue = 0;
	const Square *red = 0;
	const Square *green = 0;

	for (int i=0;i<size;i++) {
		if (recognizedSquares[i]->GetId()==1) {
			red = recognizedSquares[i];
		}
		if (recognizedSquares[i]->GetId()==2) {
			green = recognizedSquares[i];
		}
		if (recognizedSquares[i]->GetId()==3) {
			blue = recognizedSquares[i];
		}
	}
//careful here: control repeated cubes, control not present cubes (defaulting?)

	CvPoint bluepoint	  = blue  ? blue->GetCenterCoordinates()  : cvPoint(0, 0);
	CvPoint redpoint	  = red   ? red->GetCenterCoordinates()   : cvPoint(0, 0);
  CvPoint greenpoint  = green ? green->GetCenterCoordinates() : cvPoint(0, 0);

	printf("xs of rgb: %d %d %d\n", redpoint.x, greenpoint.x, bluepoint.x);

	int redAmount		= 255 * ((float)redpoint.x/100);
	int greenAmount	= 255 * ((float)greenpoint.x/100);
	int blueAmount	= 255 * ((float)bluepoint.x/100);

	int redWidth = redAmount*492/255;
	int greenWidth = greenAmount*492/255;
	int blueWidth = blueAmount*492/255;


	QPoint redbarposition		= QPoint(20,100);
	QPoint greenbarposition		=QPoint(20,150);
	QPoint bluebarposition		= QPoint(20,200);

	QPoint redbarslider		= QPoint(redWidth+10, 96);
	QPoint greenbarslider	= QPoint(greenWidth+10, 146);
	QPoint bluebarslider	= QPoint(blueWidth+10, 196);

	// Compose the color
	QColor *color = new QColor(redAmount, greenAmount, blueAmount, 255);
	printf("Composing the color: [%d, %d, %d] => %lu\n", redAmount, greenAmount, blueAmount, color->rgb());

	QImage *rgbcolor = new QImage(100,100,QImage::Format_RGB16);
	rgbcolor->fill(color->rgb());
	Image *rgbimage = new Image(rgbcolor, QPoint(270,250));
	delete color;

	QImage redBarCopy = this->redbar->copy(QRect(0, 0, redWidth+10, 20));
	Image *redbarimg = new Image(&redBarCopy, redbarposition);
	QImage greenBarCopy = this->greenbar->copy(QRect(0, 0, greenWidth+10, 20));
	Image *greenbarimg = new Image(&greenBarCopy, greenbarposition);
	QImage blueBarCopy = this->bluebar->copy(QRect(0, 0, blueWidth+10, 20));
	Image *bluebarimg = new Image(&blueBarCopy, bluebarposition);

	Image *sliderimgred = new Image(this->ball, redbarslider);
	Image *sliderimggreen = new Image(this->ball, greenbarslider);
	Image *sliderimgblue = new Image(this->ball, bluebarslider);



	const Image *images[7];
	images[0] = redbarimg;
	images[1] = bluebarimg;
	images[2] = greenbarimg;
	images[3] = sliderimgred;
	images[4] = sliderimggreen;
	images[5] = sliderimgblue;
	images[6] = rgbimage;

	SquaresProcessed(images, 7);

	delete rgbcolor;
	delete rgbimage;
	delete redbarimg;
	delete greenbarimg;
	delete bluebarimg;
	delete sliderimgred;
	delete sliderimggreen;
	delete sliderimgblue;

	// TODO: Deallocate the QImages created with copy -- how?
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

ColorPalette::~ColorPalette ()
{

}

//void GetColor()
