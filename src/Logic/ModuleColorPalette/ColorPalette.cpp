#include "ColorPalette.h"

#include <QList>
#include <QStringList>

//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

ColorPalette::ColorPalette() {
	printf ("Constructing color palette.\n");

	this->moduleConfig = new ModuleConfig("ColorPalette");

	m_interface = new QImage(QSize(345, 760), QImage::Format_RGB16);
	m_gloss     = new QImage(QSize(521, 110), QImage::Format_RGB16);
	m_ball      = new QImage(QSize(52, 54),   QImage::Format_RGB16);
	m_redBar    = new QImage(QSize(300, 20),  QImage::Format_RGB16);
	m_greenBar  = new QImage(QSize(300, 20),  QImage::Format_RGB16);
	m_blueBar   = new QImage(QSize(300, 20),  QImage::Format_RGB16);

	m_ball->load ("Logic/ModuleColorPalette/ball.png");
	m_interface->load("Logic/ModuleColorPalette/interface.jpg");
	m_gloss->load("Logic/ModuleColorPalette/gloss.png");
	m_redBar->load("Logic/ModuleColorPalette/Bar_Red.png");
	m_blueBar->load ("Logic/ModuleColorPalette/Bar_Blue");
	m_greenBar->load ("Logic/ModuleColorPalette/Bar_Green");
}

//---------------------------------------------------------------

void ColorPalette::ProcessSquares (const Square *recognizedSquares, int size)
{
  printf("[ColorPalette] ProcessSquares\n");

	const Square* blue = NULL;
	const Square* red = NULL;
	const Square* green = NULL;

	for (int i=0; i < size; i++)
	{
		Square *square = (Square *) &(recognizedSquares[i]);
		QString objectName = this->moduleConfig->objectForSquare(square);

		if (objectName == "red") 		red = square;
		if (objectName == "green") 	green = square;
		if (objectName == "blue") 	blue = square;
	}

  CvPoint bluePoint   = this->pointFromSquareOrDefault(blue,  "blue");
  CvPoint redPoint    = this->pointFromSquareOrDefault(red,   "red");
  CvPoint greenPoint  = this->pointFromSquareOrDefault(green, "green");
	
	printf ("Coordinates of RGB: %d %d %d\n", redPoint.x, greenPoint.x, bluePoint.x);

  int leftMargin = 119;
  int topMargin = 34;
  int barDistance = 52;


	int redAmount 	= (255 * ((float)redPoint.x-10)/ 83);
	int greenAmount	= (255 * ((float)greenPoint.x-10 )/ 83);
	int blueAmount	= (255 * ((float)bluePoint.x -10 )/ 83);


	if (redAmount>255) redAmount=255;
	if (greenAmount>255) greenAmount=255;
	if (blueAmount>255) blueAmount=255;

	if (redAmount<0) redAmount=0;
	if (greenAmount<0) greenAmount=0;
	if (blueAmount<0) blueAmount=0;

	int redWidth = redAmount * 492 / 255;
	int greenWidth = greenAmount * 492 / 255;
	int blueWidth = blueAmount * 492 / 255;

	QPoint redbarposition   = QPoint(leftMargin, topMargin);
	QPoint greenbarposition = QPoint(leftMargin, topMargin+barDistance);
	QPoint bluebarposition  = QPoint(leftMargin, topMargin+barDistance*2);

	QPoint redbarslider = QPoint (redWidth + leftMargin, topMargin-4);
	QPoint greenbarslider = QPoint (greenWidth + leftMargin, topMargin+barDistance-4);
	QPoint bluebarslider = QPoint (blueWidth + leftMargin, topMargin+barDistance*2-4);

	// Compose the color
	QColor color(redAmount, greenAmount, blueAmount, 255);
	printf("Composing the color: [%d, %d, %d] => %lu\n", redAmount, greenAmount, blueAmount, color.rgba());

  // User Interface
  
  Image interfaceImage(*m_interface, QPoint(0, 0));
  
	QImage rgbcolor (521, 110, QImage::Format_RGB32);
	rgbcolor.fill(color.rgba());
	
	Image rgbimage (rgbcolor, QPoint(leftMargin+1, topMargin+169));
  Image glossImage(*m_gloss, QPoint(leftMargin+1, topMargin+169));

	QImage redBarCopy = m_redBar->copy(QRect(0, 0, redWidth+10, 20));
	Image redbarimg (redBarCopy, redbarposition);

	QImage greenBarCopy = m_greenBar->copy(QRect(0, 0, greenWidth+10, 20));
	Image greenbarimg (greenBarCopy, greenbarposition);

	QImage blueBarCopy = m_blueBar->copy(QRect(0, 0, blueWidth+10, 20));
	Image bluebarimg (blueBarCopy, bluebarposition);

	Image sliderimgred (*m_ball, redbarslider);
	Image sliderimggreen (*m_ball, greenbarslider);
	Image sliderimgblue (*m_ball, bluebarslider);

	// TODO: Remove variables which are copied into "images" array, so performance will increase

  Image images [9];
  images[0] = interfaceImage;
  images[1] = redbarimg;
  images[2] = bluebarimg;
  images[3] = greenbarimg;
  images[4] = sliderimgred;
  images[5] = sliderimggreen;
  images[6] = sliderimgblue;
  images[7] = rgbimage;
  images[8] = glossImage;

  emit SquaresProcessed(images, 9);

	// TODO: Deallocate the QImages created with copy -- how?
}


CvPoint ColorPalette::pointFromSquareOrDefault(const Square *square, QString name) {
  if (square != NULL){
    CvPoint coords = square->GetCenterCoordinates();
    this->lastPoints[name] = coords;
    return coords;
  } else if (this->lastPoints.contains(name)) {
    return this->lastPoints[name];
  } else {
    return cvPoint(0, 0);
  }
}

//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

ColorPalette::~ColorPalette ()
{
	delete m_interface;
	delete m_ball;
	delete m_redBar;
	delete m_greenBar;
	delete m_blueBar;
	delete m_gloss;
	delete this->moduleConfig;
}
