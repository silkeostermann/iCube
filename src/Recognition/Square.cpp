#include "Square.h"


// Here goes member definition

//---------------------------------------------------------------
// Constructor.
// Expects to receive valid unique identifier, quadrilateral center coordinates and size.
// Initializes members.
//---------------------------------------------------------------
Square::Square (int id, const CvPoint& centerCoordinates, int width, int height)
{
	this->id = id;
	this->centerCoordinates = centerCoordinates;
	this->width = width;
	this->height = height;
	this->angle = 0;
}

//---------------------------------------------------------------
// Constructor.
// Expects to receive valid unique identifier, quadrilateral center coordinates and size.
// Initializes members.
//---------------------------------------------------------------
Square::Square (int id, const CvPoint& centerCoordinates, int width, int height, float angle)
{
	this->id = id;
	this->centerCoordinates = centerCoordinates;
	this->width = width;
	this->height = height;
	this->angle = angle;
}

//---------------------------------------------------------------

Square::Square ()
{
	this->id = 0;
	CvPoint centerCoordinates;
	this->width = 0;
	this->height = 0;
	this->angle = 0;
}

//---------------------------------------------------------------

int Square::GetId () const
{
	return id;
}

//---------------------------------------------------------------

CvPoint Square::GetCenterCoordinates () const
{
	return centerCoordinates;
}

//---------------------------------------------------------------

int Square::GetWidth () const
{
	return width;
}

//---------------------------------------------------------------

int Square::GetHeight () const
{
	return height;
}

//---------------------------------------------------------------

float Square::GetAngle () const
{
	return angle;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

Square::~Square ()
{
	
}
