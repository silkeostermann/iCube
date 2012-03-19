#include "icubes.h"


iCubes::iCubes(QWidget *parent)
	: QMainWindow(parent)
{
	// UI Initialization
	ui.setupUi (this);

	setWindowTitle("iCubes");
	for (int i = 0; i < SIZE; i++)
		m_labels [i] = new QLabel (this);

	m_configurator = NULL;

	QObject::connect (ui.buttonConfigure, SIGNAL (clicked()),
						this, SLOT (ShowConfigureDialog()));

	// Setup Color Palette
  	//setupModule (&m_colorPalette);
  

	// Setup Penguin Flight
	setupModule (&m_pinguinFlight);
	/**/

	m_frameProcessor.BeginRead (0, 10);
}


//---------------------------------------------------------------
// Connects module's "SquaresProcessed" signal to iCubes' "ShowObjects" slot
//---------------------------------------------------------------

void iCubes::setupModule(QObject *module) {
	QObject::connect(module, SIGNAL(SquaresProcessed(const Image*, int)),
									 this, SLOT(ShowObjects(const Image*, int)));

	QObject::connect(&m_frameProcessor, SIGNAL(SquaresRecognized(const Square*, int)),
                   module, SLOT(ProcessSquares(const Square*, int)));
}

//---------------------------------------------------------------

void iCubes::demoSquares() {
	CvPoint p1 = cvPoint (30, 4);
	Square sq1 (1, p1, 100, 6);

	CvPoint p2 = cvPoint (50, 4);
	Square sq2 (2, p2, 50, 6);

	CvPoint p3 = cvPoint (100, 4);
	Square sq3 (3, p3, 100, 6);

	Square squares [3] = {sq1, sq2, sq3};

	m_colorPalette.ProcessSquares (squares, 3);
	// m_pinguinFlight->ProcessSquares (squares, 3);
}

//---------------------------------------------------------------
// Gets processed objects which to draw.
// Expects pointer on valid processed objects array.
//---------------------------------------------------------------
void iCubes::ShowObjects(const Image* processedSquares, int count)
{
	for (int i = 0; i < count && i < SIZE; i++)
	{
		const Image *img = &(processedSquares[i]);
		int xpos = img->imageRelativeCoordinates.x();
		int ypos = img->imageRelativeCoordinates.y();

		m_labels [i]->move(xpos, ypos);
		m_labels [i]->resize (img->image.width (), img->image.height());

		m_labels [i]->setPixmap (QPixmap::fromImage(img->image));
		m_labels [i]->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_labels [i]->setAlignment (Qt::AlignCenter);
		m_labels [i]->show();
	}

	for(int i = count; i < SIZE; i++)
		m_labels [i]->hide();
}

//---------------------------------------------------------------

void iCubes::ShowConfigureDialog ()
{
	if (m_configurator == NULL)
		m_configurator = new Configure (this);

	m_configurator->setModal (true);
	m_configurator->show ();
}

//---------------------------------------------------------------

iCubes::~iCubes()
{
	delete m_configurator;

	for (int i = 0; i < SIZE; i++)
		delete m_labels [i];

	m_frameProcessor.EndRead();

}
