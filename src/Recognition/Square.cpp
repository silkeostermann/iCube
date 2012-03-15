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
}

//---------------------------------------------------------------

int Square::GetId () const
{
	return this->id;
}

//---------------------------------------------------------------

CvPoint Square::GetCenterCoordinates () const
{
	return this->centerCoordinates;
}

//---------------------------------------------------------------

int Square::GetWidth () const
{
	return this->width;
}

//---------------------------------------------------------------

int Square::GetHeight () const
{
	return this->height;
}


//---------------------------------------------------------------
// Destructor.
// Releases used resources.
//---------------------------------------------------------------

Square::~Square ()
{
}
