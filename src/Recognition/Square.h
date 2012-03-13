#ifndef SQUARE_H
#define SQUARE_H

#include "opencv/highgui.h"

//---------------------------------------------------------------
// Represents physical quadrilateral and its properties.
//---------------------------------------------------------------

class Square
{
	public:
		Square (int id, const CvPoint& centerCoordinates, int width, int height);

		int GetId () const;
		CvPoint GetCenterCoordinates () const;
		int GetWidth () const;
		int GetHeight () const;

		~Square ();
};


#endif
