#ifndef BLANK_LOGIC_H
#define BLANK_LOGIC_H

#include <QObject>

#include "Logic/ModuleInterface.h"
#include "Logic/Image.h"
#include "Recognition/Square.h"
#include <qobject.h>

class BlankLogic : public QObject, public ModuleInterface
{
	Q_OBJECT
	Q_INTERFACES(ModuleInterface)

  public:
	  BlankLogic();
		~BlankLogic();
    QString moduleName();

  

  // public slots:
    // void ProcessSquares(const Square* squares, int size);

  // signals:
    // void SquaresProcessed(const Image *image, int size);

};

#endif
