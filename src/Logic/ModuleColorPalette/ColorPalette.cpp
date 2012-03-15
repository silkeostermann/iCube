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

void ColorPalette::ProcessSquares (const Square **recognizedSquares, size_t size)
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


	CvPoint bluepoint	= blue->GetCenterCoordinates();
	CvPoint redpoint	= red->GetCenterCoordinates();
	CvPoint greenpoint	= green->GetCenterCoordinates();

	printf("xs of rgb: %d %d %d\n", redpoint.x, greenpoint.x, bluepoint.x);

	int redAmount		= 255 * ((float)redpoint.x/100);
	int greenAmount	= 255 * ((float)greenpoint.x/100);
	int blueAmount	= 255 * ((float)bluepoint.x/100);

	int redWidth = redAmount*492/255;
	int greenWidth = greenAmount*492/255;
	int blueWidth = blueAmount*492/255;

	// Compose the color
	QColor *color = new QColor(redAmount, greenAmount, blueAmount, 255);
	printf("Composing the color: [%d, %d, %d] => %lu\n", redAmount, greenAmount, blueAmount, color->rgb());

	// Prepare the image and painter
	QImage *image = new QImage(*this->interface);
	QPainter *painter = new QPainter(image);

	//Draw the section of a bar we need for each color
	painter->drawImage(60, 185, (this->redbar->copy(0, 0, redWidth+10, 20)));
	painter->drawImage(60, 267, (this->greenbar->copy(0, 0, greenWidth+10, 20)));
	painter->drawImage(60, 347, (this->bluebar->copy(0, 0, blueWidth+10, 20)));

	// Draw ball for each color
	painter->drawImage(redWidth+60, 180, *this->ball);
	painter->drawImage(greenWidth+60, 262, *this->ball);
	painter->drawImage(blueWidth+60, 342, *this->ball);

	// Draw the chosen color
	painter->fillRect(62, 445, 517, 106, color->rgb());

	// Save the image
	image->save("test.png");

	const Image *images[1];
	images[0] = new Image(*image, QPoint(10, 10));
	SquaresProcessed(images, 1);
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

ColorPalette::~ColorPalette ()
{

}

//void GetColor()
