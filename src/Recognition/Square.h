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
		Square (int contoursCount, const CvPoint& centerCoordinates, int width, int height);
		Square (int contoursCount, const CvPoint &centerCoordinates, int width, int height, float angle);

		int GetContoursCount() const;
		CvPoint GetCenterCoordinates() const;
		int GetWidth () const;
		int GetHeight () const;
		float GetAngle () const;

		~Square ();
	private:
		int contoursCount;
		CvPoint centerCoordinates;
		int width;
		int height;
		float angle;
};


#endif
