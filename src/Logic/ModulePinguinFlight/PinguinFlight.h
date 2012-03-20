#ifndef PINGUIN_FLIGHT_H
#define PINGUIN_FLIGHT_H

#include <QtGui/QImage>
#include <qobject.h>

#include "../ModuleInterface.h"
#include "../../Recognition/Square.h"
#include "../Image.h"

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class PinguinFlight : public ModuleInterface
{
	Q_OBJECT

  	private:
    		QImage penguin0, penguin90, penguin180, penguin270;

	public:
		PinguinFlight();
		~PinguinFlight();
    QString moduleName();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);

};

#endif
