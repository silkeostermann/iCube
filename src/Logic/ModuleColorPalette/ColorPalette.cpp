#include "ColorPalette.h"

#include <QList>
#include <QStringList>

//---------------------------------------------------------------
// Slot to subscribe for event.
// Expects to receive array of pointers on quadrilaterals instances which were recognized
//---------------------------------------------------------------

ColorPalette::ColorPalette() {
	printf ("Constructing color palette.\n");

	QList<QStringList> list;
	QList<QStringList> list2;
	list=this->config->ReadConfiguration("ColorPallete.logic");

	list2=this->config->ReadConfiguration("ColorPallete.recognition");

	// Prepare the UI images

	m_interface = new QImage (QSize (640, 640), QImage::Format_RGB16);
	m_ball = new QImage (QSize (52, 54), QImage::Format_RGB16);
	m_redBar = new QImage (QSize (300, 20), QImage::Format_RGB16);
	m_greenBar = new QImage (QSize (300, 20), QImage::Format_RGB16);
	m_blueBar = new QImage (QSize (300, 20), QImage::Format_RGB16);

	m_ball->load ("Logic/ModuleColorPalette/ball.png");
	m_interface->load("Logic/ModuleColorPalette/interface.jpg");
	m_redBar->load("Logic/ModuleColorPalette/Bar_Red.png");
	m_blueBar->load ("Logic/ModuleColorPalette/Bar_Blue");
	m_greenBar->load ("Logic/ModuleColorPalette/Bar_Green");

	for (int i=0; i < list.size()-1; i++){
		if (list.at(i).at(1)=="red") {

			idRed=list.at(i).at(0).toInt();
		}
		if (list.at(i).at(1)=="blue") {

			idBlue=list.at(i).at(0).toInt();
		}
		if (list.at(i).at(1)=="green") {

			idGreen=list.at(i).at(0).toInt();
		}

	}

	printf("idRed is %d\n",idRed);
	printf("idGreen is %d\n",idGreen);
	printf("idBlue is %d\n",idBlue);



	for (int i=0; i < list2.size()-1; i++){
		if (list2.at(i).at(1).toInt()==idRed) {
			idRed=list2.at(i).at(0).toInt();
		}
		if (list2.at(i).at(1).toInt()==idGreen) {
			idGreen=list2.at(i).at(0).toInt();
		}
		if (list2.at(i).at(1).toInt()==idBlue) {
			idBlue=list2.at(i).at(0).toInt();
		}

	}
		printf("idRed is %d\n",idRed);
		printf("idGreen is %d\n",idGreen);
		printf("idBlue is %d\n",idBlue);

}

//---------------------------------------------------------------

void ColorPalette::ProcessSquares (const Square *recognizedSquares, int size)
{
	printf("Processing %d squares.\n", (int)size);

	const Square* blue = NULL;
	const Square* red = NULL;
	const Square* green = NULL;
	QList<QStringList> list;
	list=this->config->ReadConfiguration("ColorPallete.recognition");

	
	
	// TODO: Load ID from file and store as table (array)
	for (int i=0; i < size; i++)
	{
		//if (recognizedSquares [i].GetId () == IDforObject("red")
		//			red = &recognizedSquares [i];

		if (recognizedSquares [i].GetId () == idRed)
			red = &recognizedSquares [i];

		if (recognizedSquares [i].GetId () == idGreen)
			green = &recognizedSquares [i];

		if (recognizedSquares [i].GetId () == idBlue)
			blue = &recognizedSquares[i];
	}

	// NOTE: Careful here, control repeated cubes, control not present cubes (defaulting?)

	CvPoint bluePoint = blue ? blue->GetCenterCoordinates() : cvPoint(0, 0);
	CvPoint redPoint = red ? red->GetCenterCoordinates()  : cvPoint(0, 0);
	CvPoint greenPoint = green ? green->GetCenterCoordinates() : cvPoint(0, 0);

	printf ("'X' coordinate of RGB: %d %d %d\n", redPoint.x, greenPoint.x, bluePoint.x);

	int redAmount = 255 * (redPoint.x / 100);
	int greenAmount	= 255 * (greenPoint.x / 100);
	int blueAmount	= 255 * (bluePoint.x / 100);

	int redWidth = redAmount * 492 / 255;
	int greenWidth = greenAmount * 492 / 255;
	int blueWidth = blueAmount * 492 / 255;

	QPoint redbarposition = QPoint (20,100);
	QPoint greenbarposition = QPoint (20,150);
	QPoint bluebarposition = QPoint (20,200);

	QPoint redbarslider = QPoint (redWidth + 10, 96);
	QPoint greenbarslider = QPoint (greenWidth + 10, 146);
	QPoint bluebarslider = QPoint (blueWidth + 10, 196);

	// Compose the color
	QColor color (redAmount, greenAmount, blueAmount, 255);
	printf("Composing the color: [%d, %d, %d] => %lu\n", redAmount, greenAmount, blueAmount, color.rgb());

	QImage rgbcolor (100, 100, QImage::Format_RGB16);
	rgbcolor.fill (color.rgb ());

	Image rgbimage (rgbcolor, QPoint(270, 250));

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

	Image images [7];
	images [0] = redbarimg;
	images [1] = bluebarimg;
	images [2] = greenbarimg;
	images [3] = sliderimgred;
	images [4] = sliderimggreen;
	images [5] = sliderimgblue;
	images [6] = rgbimage;

	SquaresProcessed (images, 7);

	// TODO: Deallocate the QImages created with copy -- how?
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
}
