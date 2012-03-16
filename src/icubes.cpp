#include "icubes.h"
#include "configure.h"
#include <QTimer>
#include <cstdio>

iCubes::iCubes(QWidget *parent)
	: QMainWindow(parent)
{
  // UI Initialization
	ui.setupUi(this);
	setWindowTitle("iCubes");
	for (int i = 0; i < SIZE; i++) {
		QLabel *label = new QLabel(this);
		labels[i] = label;
	}
	QObject::connect(ui.buttonConfigure, SIGNAL (clicked()),
						this, SLOT (ShowConfigureDialog()));

	// Setup Color Palette
	this->palette = new ColorPalette();
	this->setupModule(this->palette);
  
  // Setup Penguin Flight
  this->pinguinFlight = new PinguinFlight();
  this->setupModule(this->pinguinFlight);

  // Frame processor  
	int webCamId = 1;
	int fps = 30;
	m_videoStreamProcessor.BeginRead(webCamId, fps);
}

// Sets up module:
// - connects module's `SquaresProcessed` signal to iCubes' `ShowObjects` slot
void iCubes::setupModule(QObject *module) {
	QObject::connect(module, SIGNAL(SquaresProcessed(const Image*, int)),
									 this, SLOT(ShowObjects(const Image*, int)));
  QObject::connect(&m_videoStreamProcessor, SIGNAL(SquaresRecognized(const Square*, int)),
                   module, SLOT(ProcessSquares(const Square*, int)));
}

void iCubes::demoSquares() {
	CvPoint p1 = cvPoint(30, 4);
	Square *sq1 = new Square(1, p1, 100, 6);

	CvPoint p2 = cvPoint(50, 4);
	Square *sq2 = new Square(2, p2, 50, 6);

	CvPoint p3 = cvPoint(100, 4);
	Square *sq3 = new Square(3, p3, 100, 6);

	Square *squares[3] = {sq1, sq2, sq3};

	// this->palette->ProcessSquares((const Square *)squares, 3);
	this->pinguinFlight->ProcessSquares((const Square *)squares, 3);
}

//---------------------------------------------------------------
// Gets processed objects which to draw.
// Expects pointer on valid processed objects array.
//---------------------------------------------------------------
void iCubes::ShowObjects(const Image* processedSquares, int count)
{
	// NOTE: Find out if it is safe to change GUI elements from invoked signal.
	// NOTE: It might be required to use InvokeMethod ()

	printf("Showing %d objects.\n", count);

  for (int i = 0; i < count && i < SIZE; i++) {
  	const Image *img = &(processedSquares[i]);
  	int xpos = img->imageRelativeCoordinates.x();
  	int ypos = img->imageRelativeCoordinates.y();

  	printf("Moving object to [%d, %d]\n", xpos, ypos);
  	labels[i]->move(xpos, ypos);
  	labels[i]->resize(img->image.width(), img->image.height());
  	printf("Image size: %dx%d\n", img->image.width(), img->image.height());
  	labels[i]->setPixmap(QPixmap::fromImage(img->image));
  	labels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  	labels[i]->setAlignment(Qt::AlignCenter);
	}
	for(int i = count; i < SIZE; i++)
	{
		labels[i]->hide();
	}
}

//---------------------------------------------------------------
void iCubes::ShowConfigureDialog ()
{
	Configure *configure = new Configure(this);
	configure->show();
}

//---------------------------------------------------------------
iCubes::~iCubes()
{
	m_videoStreamProcessor.EndRead();
}
