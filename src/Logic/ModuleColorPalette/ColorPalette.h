#ifndef OBJECT_PROCESSOR_H
#define OBJECT_PROCESSOR_H

#include <QtGui/QImage>
#include "../../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class ColorPalette : public QObject
{
	Q_OBJECT

	private:
		QImage *interface;
		QImage *ball;
		QImage *redbar;
		QImage *greenbar;
		QImage *bluebar;

	public:
		ColorPalette();
		~ColorPalette();

	public slots:
		void ProcessSquares (const Square**, size_t size);

	signals:
		void SquaresProcessed (const Image**, int size);

};

#endif
