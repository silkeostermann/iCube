#ifndef SQUARE_H
#define SQUARE_H

#include "opencv/highgui.h"
#include <qobject.h>

//---------------------------------------------------------------
// Represents physical quadrilateral and its properties.
//---------------------------------------------------------------

class Square : public QObject
{
	Q_OBJECT

	public:
		Square (int id, const CvPoint& centerCoordinates, int width, int height);

		CvPoint centerCoordinates;

		int GetId () const;
		int GetWidth () const;
		int GetHeight () const;

		~Square ();
};


#endif
