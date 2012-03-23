#include "icubes.h"

iCubes::iCubes (QWidget *parent): QMainWindow (parent) 
{
	ConfigureInterface ();
	SetupModules ();
}

//--------------------------------------------------------------

void iCubes::ConfigureInterface ()
{
	// Initialize window
	m_ui.setupUi (this);
	setFixedSize (SCREEN_WIDTH, SCREEN_HEIGHT);
	setWindowTitle ("iCubes");

	// Initialize virtual object images containers
	for (int i = 0; i < MAX_VIRTUAL_OBJECT_COUNT; i++)
		m_labels [i] = new QLabel (this);

	QObject::connect (m_ui.buttonConfigure, SIGNAL (clicked ()),
		        this, SLOT (ShowConfigureDialog ()));
	
	QObject::connect (m_ui.moduleCombo, SIGNAL (currentIndexChanged (const QString&)),
                   	this, SLOT (ChangeModule (const QString&)));

	QObject::connect (m_ui.StartstopButton, SIGNAL (clicked ()),
			this, SLOT (StartStop ()));

}

//--------------------------------------------------------------

void iCubes::StartStop ()
{
	if (QString::compare (m_ui.StartstopButton->text (), new QString ("Start")) == 0)
	{
		m_frameProcessor.BeginRead (0, 25);
		m_ui.StartstopButton->setText (QString ("Stop"));	
	}
	else 
	{
		m_frameProcessor.EndRead ();
		m_ui.StartstopButton->setText (QString ("Start"));	
	}	
}

//------------------------------------------------------------

void iCubes::SetupModules ()
{
  m_modules ["BinaryMath"] = &(m_binMath);
  m_modules ["ColorPalette"] = &(m_colorPalette);
  m_modules ["PinguinFlight"] = &(m_pinguinFlight);
  m_modules ["Pong"] = &(m_pong);

  m_currentModule = NULL;
  QList <QString> moduleNames = m_modules.keys ();
  m_ui.moduleCombo->addItem ("");

  for (int i = 0; i < moduleNames.size (); i++)
  	m_ui.moduleCombo->addItem (moduleNames.at (i));
}

//---------------------------------------------------------------

void iCubes::DisconnectModule (QObject* module)
{
  printf ("Disconnecting module!\n");

  QObject::disconnect (&m_frameProcessor, SIGNAL (SquaresRecognized (const Square*, int)),
                      module, 0);

  QObject::disconnect (module, SIGNAL (SquaresProcessed (const Image*, int)),
                      this, 0);
}

//---------------------------------------------------------------------------

void iCubes::SetupModule (QObject* module)
{
	QObject::connect (module, SIGNAL (SquaresProcessed (const Image*, int)),
					 this, SLOT(ShowObjects(const Image*, int)));

	QObject::connect (&m_frameProcessor, SIGNAL (SquaresRecognized (const Square*, int)),
                   module, SLOT (ProcessSquares (const Square*, int)));
}

//---------------------------------------------------------------------------

void iCubes::ChangeModule (const QString& moduleName)
{
	if (moduleName == "")
		return;

  	if (m_currentModule != NULL)
    		DisconnectModule (m_currentModule);
  
  	m_currentModule = m_modules [moduleName];
  
  	SetupModule (m_currentModule);
  
  	printf ("Changed module to %s\n", qPrintable (moduleName));
}

//---------------------------------------------------------------

void iCubes::ShowObjects (const Image* processedSquares, int count)
{
	QPoint point_canvas = m_ui.groupBox->pos ();

	int i = 0;
	while ((i < count) && (i < MAX_VIRTUAL_OBJECT_COUNT))
	{
		const Image* img = &(processedSquares [i]);
		int xpos = img->imageRelativeCoordinates.x ();
		int ypos = img->imageRelativeCoordinates.y ();

		m_labels [i]->move (xpos + point_canvas.x (), ypos + point_canvas.y ());
		m_labels [i]->resize (img->image.width (), img->image.height ());

		m_labels [i]->setPixmap (QPixmap::fromImage (img->image));
		m_labels [i]->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_labels [i]->setAlignment (Qt::AlignCenter);
		m_labels [i]->show ();

		printf ("[iCubes] ShowObjects () %d th object processed\n", i);	

		++i;
	}

	for (int i = count; i < MAX_VIRTUAL_OBJECT_COUNT; i++)
		m_labels [i]->hide ();
}

//---------------------------------------------------------------

void iCubes::ShowConfigureDialog ()
{
	Configure* configurator = new Configure (this, m_ui.moduleCombo->currentText ());
	configurator->setModal (true);
	configurator->show ();
}

//--------------------------------------------------------------

void iCubes::closeEvent (QCloseEvent* event)
{
	m_frameProcessor.EndRead ();

	event->accept();
	printf ("Close event accepted\n");
}

//---------------------------------------------------------------

iCubes::~iCubes ()
{
	for (int i = 0; i < MAX_VIRTUAL_OBJECT_COUNT; i++)
		delete m_labels [i];
}

