#include <QDir>
#include <QPluginLoader>

#include "icubes.h"
#include "Logic/ModuleBinaryMath/BinaryMath.h"
#include "Logic/ModuleColorPalette/ColorPalette.h"
#include "Logic/ModulePinguinFlight/PinguinFlight.h"

#define SELECT_MODULE_STRING ""


iCubes::iCubes(QWidget *parent)
	: QMainWindow(parent)
{
  this->configureInterface();
  this->setupModules();
  
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
  // 01 Load the static modules
  ModuleInterface *binaryMath     = new BinaryMath();
  ModuleInterface *colorPalette   = new ColorPalette();
  ModuleInterface *pinguinFlight  = new PinguinFlight(); 

  this->registerModule(binaryMath);
  this->registerModule(colorPalette);
  this->registerModule(pinguinFlight);
  
  // 02 Load the dynamic modules

}

void iCubes::registerModule(ModuleInterface *module) {
  QString name = module->moduleName();
  printf("Registering module %s\n", qPrintable(name));
  this->modules[name] = module;
  this->updateModulesCombo();
}

void iCubes::updateModulesCombo() {
  ui.moduleCombo->clear();
  ui.moduleCombo->addItem(SELECT_MODULE_STRING);
  
  QList<QString> moduleNames = this->modules.keys();
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

void iCubes::connectModule(QObject *module) {
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
  
  this->connectModule(this->currentModule);
  
  printf("Changed module to %s\n", qPrintable(moduleName));
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
	Configure *configurator = new Configure(this, ui.moduleCombo->currentText());
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
