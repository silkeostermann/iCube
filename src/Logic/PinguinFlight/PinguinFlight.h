#ifndef PINGUIN_FLIGHT_H
#define PINGUIN_FLIGHT_H

#include <QtGui/QImage>
#include "../../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class PinguinFlight : public QObject
{
	Q_OBJECT

  	private:
    		QImage penguin0, penguin90, penguin180, penguin270;

	public:
		PinguinFlight();
		~PinguinFlight();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);

};

#endif
