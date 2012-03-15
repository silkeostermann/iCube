#include "icubes.h"
#include "configure.h"
#include <QTimer>
#include <cstdio>

iCubes::iCubes(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("iCubes");

    FrameProcessor m_videoStreamProcessor;

    BinaryMath m_objectProcessor;

		// Setup Color Palette
		// -------------------
		this->palette = new ColorPalette();
		// When user clicks the 'configure' button (temp solution), the demoSquares
		// method is called.
		QObject::connect(ui.buttonConfigure, SIGNAL(clicked()),
										 this, SLOT(demoSquares()));
		// When palette processes squares, we want to call the ShowObjects Slot of iCubes
		QObject::connect(this->palette, SIGNAL(SquaresProcessed(const Image**, int)),
										 this, SLOT(ShowObjects(const Image**, int)));

		QObject::connect(&m_videoStreamProcessor, SIGNAL (SquaresRecognized (const Square**, int)),
										 &m_objectProcessor, SLOT (ProcessSquares (const Square**, int)));

	//QObject::connect(ui.buttonConfigure, SIGNAL (clicked()),
	//					this, SLOT (ShowConfigureDialog()));



	int webCamId = 1;
	int fps = 30;
	m_videoStreamProcessor.BeginRead (webCamId, fps);

	////

	for (int i = 0; i < SIZE; i++) {
		QLabel *label = new QLabel(this);
		labels[i] = label;
	}


	QObject::connect(&m_objectProcessor, SIGNAL (SquaresProcessed (const Image**, int)),
						this, SLOT (ShowObjects (const Image**, int)));
}

void iCubes::demoSquares() {
	CvPoint p1 = cvPoint(30, 4);
	Square *sq1 = new Square(1, p1, 100, 6);

	CvPoint p2 = cvPoint(50, 4);
	Square *sq2 = new Square(2, p2, 50, 6);

	CvPoint p3 = cvPoint(100, 4);
	Square *sq3 = new Square(3, p3, 100, 6);

	Square *squares[3] = {sq1, sq2, sq3};

	this->palette->ProcessSquares((const Square **)squares, 3);

}

void iCubes::updatePos() {

	QImage *myImage = new QImage();
		myImage->load("/home/user/Desktop/qt-logo.png");
		QImage img2 = myImage->scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);

		const Image *imgArray[SIZE];
		imgArray[0] = new Image(img2, QPoint(10, 50));
		imgArray[1] = new Image(img2, QPoint(10, 80));
		ShowObjects(imgArray, SIZE);
}

//---------------------------------------------------------------
// Gets processed objects which to draw.
// Expects pointer on valid processed objects array.
//---------------------------------------------------------------
void iCubes::ShowObjects (const Image** processedSquares, int count)
{
	// NOTE: Find out if it is safe to change GUI elements from invoked signal.
	// NOTE: It might be required to use InvokeMethod ()

	for (int i = 0; i < count; i++) {
		const Image * img = processedSquares[i];
		int xpos = img->imageRelativeCoordinates.x() * ui.groupBox->width()
				/ 100.0;
		int ypos = img->imageRelativeCoordinates.y()
				* ui.groupBox->height() / 100.0;
		labels[i]->move(xpos, ypos);
		labels[i]->resize(img->image.width(), img->image.height());
		labels[i]->setPixmap(QPixmap::fromImage(img->image));
		labels[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		labels[i]->setAlignment(Qt::AlignCenter);
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
	m_videoStreamProcessor.EndRead ();
}
