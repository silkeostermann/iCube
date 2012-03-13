#ifndef BINARY_MATH_H
#define BINARY_MATH_H

#include "../Recognition/Square.h"
#include "../Image.h"
#include <qobject.h>
#include <vector>
using namespace std;

//---------------------------------------------------------------
// Represents logic implementation, such strange name because no concrete logic chosen yet
//---------------------------------------------------------------

class BinaryMath : public QObject
{
	Q_OBJECT

	public:
		~BinaryMath ();

	public slots:
		void ProcessSquares (const vector*<Square*> recognizedSquares);

	signals:
		void SquaresProcessed (const vector*<Image*> processedSquares);

};

#endif
