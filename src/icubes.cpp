#include "icubes.h"


iCubes::iCubes(QWidget *parent)
	: QMainWindow(parent)
{
  this->configureInterface();
  this->setupModules();
  
	m_configurator = NULL;
	m_frameProcessor.BeginRead (0, 10);
}

void iCubes::configureInterface() {
  ui.setupUi (this);

	setWindowTitle("iCubes");
	for (int i = 0; i < SIZE; i++)
		m_labels [i] = new QLabel (this);

	QObject::connect (ui.buttonConfigure, SIGNAL (clicked()),
						        this, SLOT (ShowConfigureDialog()));
	
  QObject::connect(ui.moduleCombo, SIGNAL(currentIndexChanged(const QString &)),
                   this, SLOT(changeModule(const QString &)));
}

void iCubes::setupModules() {
  this->modules["Binary Math"]    = &(this->m_binMath);
  this->modules["Color Palette"]  = &(this->m_colorPalette);
  this->modules["Pinguin Flight"] = &(this->m_pinguinFlight);

  this->currentModule = NULL;

  QList<QString> moduleNames = this->modules.keys();
  ui.moduleCombo->addItem(""); // Empty item to let user select module
  for (int i = 0; i < moduleNames.size(); i++) {
    ui.moduleCombo->addItem(moduleNames.at(i));
  }
}

//---------------------------------------------------------------
// Connects module's "SquaresProcessed" signal to iCubes' "ShowObjects" slot
//---------------------------------------------------------------

void iCubes::disconnectModule(QObject *module) {
  printf("Disconnecting module! [TODO]\n");
  QObject::disconnect(&m_frameProcessor, SIGNAL(SquaresRecognized(const Square*, int)),
                      module, 0);
  QObject::disconnect(module, SIGNAL(SquaresProcessed(const Image*, int)),
                      this, 0);
}

void iCubes::setupModule(QObject *module) {
	QObject::connect(module, SIGNAL(SquaresProcessed(const Image*, int)),
									 this, SLOT(ShowObjects(const Image*, int)));

	QObject::connect(&m_frameProcessor, SIGNAL(SquaresRecognized(const Square*, int)),
                   module, SLOT(ProcessSquares(const Square*, int)));
}

void iCubes::changeModule(const QString &moduleName) {
  if (moduleName == "") return;

  if (this->currentModule != NULL) {
    this->disconnectModule(this->currentModule);
  }
  
  this->currentModule = this->modules[moduleName];
  
  this->setupModule(this->currentModule);
  
  printf("Changed module to %s\n", qPrintable(moduleName));
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
	QPoint point_canvas = ui.groupBox->pos();

	for (int i = 0; i < count && i < SIZE; i++)
	{
		const Image *img = &(processedSquares[i]);
		int xpos = img->imageRelativeCoordinates.x();
		int ypos = img->imageRelativeCoordinates.y();

		m_labels [i]->move(xpos + point_canvas.x(), ypos + point_canvas.y());
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
	Configure *configurator = new Configure(this, ui.comboboxModule->currentText());
	configurator->setModal (true);
	configurator->show ();
}

//---------------------------------------------------------------

iCubes::~iCubes()
{
	for (int i = 0; i < SIZE; i++)
		delete m_labels [i];

	m_frameProcessor.EndRead();

}
