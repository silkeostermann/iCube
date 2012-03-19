#ifndef SQUARE_H
#define SQUARE_H

#include "opencv/highgui.h"

//---------------------------------------------------------------
// Represents physical quadrilateral and its properties.
//---------------------------------------------------------------

class Square
{
	public:
		Square ();
		Square (int id, const CvPoint& centerCoordinates, int width, int height);
		Square (int id, const CvPoint &centerCoordinates, int width, int height, float angle);

		int GetId () const;
		CvPoint GetCenterCoordinates () const;
		int GetWidth () const;
		int GetHeight () const;
		float GetAngle () const;

		~Square ();
	private:
		int id;
		CvPoint centerCoordinates;
		int width;
		int height;
		float angle;
};


#endif
