#ifndef BINARY_MATH_H
#define BINARY_MATH_H

#include "../../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>

class BlankLogic : public QObject
{
	Q_OBJECT

	public:
	BlankLogic();
		~BlankLogic();

	public slots:
		void ProcessSquares(const Square* squares, int size);

	signals:
		void SquaresProcessed(const Image *image, int size);

};

#endif
