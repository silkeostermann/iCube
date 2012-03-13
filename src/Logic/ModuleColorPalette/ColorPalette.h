#ifndef OBJECT_PROCESSOR_H
#define OBJECT_PROCESSOR_H

#include "../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class ColorPalette : public QObject
{
	Q_OBJECT

	public:
		~ColorPalette ();

	public slots:
		void ProcessSquares (const Square** recognizedSquares);

	signals:
		void SquaresProcessed (const Image** processedSquares);

};

#endif
